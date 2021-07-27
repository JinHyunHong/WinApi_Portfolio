#pragma once
#include "../Game.h"

class CLogic
{
	DECLARE_SINGLE(CLogic)

private:
	HWND		m_hWnd;
	HINSTANCE	m_hInst;
	HDC			m_hDC;
	static bool		m_bLoop;
	wstring		m_strWindowName;

private:
	ATOM MyRegisterClass();
	BOOL InitInstance();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	SCREENSIZE m_tRS;

public:
	int Run();
	void Logic();

public:
	bool Init(HINSTANCE hInst);
	int	 Update();
	void Collision();
	int  LateUpdate();
	void Render();
};

