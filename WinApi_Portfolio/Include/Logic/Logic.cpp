#include "Logic.h"

DEFINITION_SINGLE(CLogic);

bool CLogic::m_bLoop;

CLogic::CLogic()
{

}

CLogic::~CLogic()
{

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

    RECT rc = { 0, 0, m_tRS.iWidth, m_tRS.iHeight };
    
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
        // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
        EndPaint(hWnd, &ps);
    }
    break;
    // �����츦 �����ų�� ������ �޼����̴�.
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
}

bool CLogic::Init(HINSTANCE hInst)
{
    m_hInst = hInst;
    m_tRS = {1200, 800};
    m_bLoop = true;
    m_strWindowName = L"Game";

    MyRegisterClass();
    InitInstance();

    m_hDC = GetDC(m_hWnd);

    return true;
}

int CLogic::Update()
{
    return 0;
}

void CLogic::Collision()
{
}

int CLogic::LateUpdate()
{
    return 0;
}

void CLogic::Render()
{
}