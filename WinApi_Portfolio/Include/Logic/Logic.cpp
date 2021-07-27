#include "Logic.h"
#include "Timer.h"
#include "FileManager.h"

DEFINITION_SINGLE(CLogic);

bool CLogic::m_bLoop;

CLogic::CLogic()
{

}

CLogic::~CLogic()
{
    DESTROY_SINGLE(CTimer);
    DESTROY_SINGLE(CFileManager);
}

ATOM  CLogic::MyRegisterClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = CLogic::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInst;
    wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL; 
    wcex.lpszClassName = m_strWindowName.c_str();
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&wcex);
}

BOOL CLogic::InitInstance()
{
    m_hWnd = CreateWindowW(m_strWindowName.c_str(), m_strWindowName.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

    if (!m_hWnd)
    {
        return FALSE;
    }

    RECT rc = { 0, 0, m_tClientRS.iWidth, m_tClientRS.iHeight };
    
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left,
        rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);

    return TRUE;
}

LRESULT CLogic::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    // 윈도우를 종료시킬때 들어오는 메세지이다.
    case WM_DESTROY:
        m_bLoop = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int CLogic::Run()
{
    MSG msg;

    while (m_bLoop)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        else
        {
            Logic();
        }

    }

    return (int)msg.wParam;
}

void CLogic::Logic()
{
    GET_SINGLE(CTimer)->Update();
    float fDeltaTime = GET_SINGLE(CTimer)->GetDeltaTime();

    Update(fDeltaTime);
    Collision(fDeltaTime);
    LateUpdate(fDeltaTime);
    Render(fDeltaTime);
}

bool CLogic::Init(HINSTANCE hInst)
{
    m_hInst = hInst;
    m_tClientRS = {1200, 800};
    m_bLoop = true;
    m_strWindowName = L"Game";

    MyRegisterClass();
    InitInstance();

    m_hDC = GetDC(m_hWnd);

    if (!GET_SINGLE(CTimer)->Init(m_hWnd))
        return false;

    if (!GET_SINGLE(CFileManager)->Init())
        return false;

    return true;
}

int CLogic::Update(float fDeltaTime)
{
    return 0;
}

void CLogic::Collision(float fDeltaTime)
{
}

int CLogic::LateUpdate(float fDeltaTime)
{
    return 0;
}

void CLogic::Render(float fDeltaTime)
{
}
