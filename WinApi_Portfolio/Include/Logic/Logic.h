#pragma once
#include "../Game.h"

class CLogic
{
	DECLARE_SINGLE(CLogic)

private:
	HWND		m_hWnd;
	HINSTANCE	m_hInst;
	HDC			m_hDC;
	static bool	m_bLoop;
	wstring		m_strWindowName;
	SCREENSIZE  m_tClientRS;

public:
	HWND	GetWindowHandle()	const
	{
		return m_hWnd;
	}

	HINSTANCE	GetInstaceHandle()	const
	{
		return m_hInst;
	}

	SCREENSIZE	GetClientRS()	const
	{
		return m_tClientRS;
	}

private:
	ATOM MyRegisterClass();
	BOOL InitInstance();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	int Run();
	void Logic();

public:
	bool Init(HINSTANCE hInst);
	int	 Update(float fDeltaTime);
	void Collision(float fDeltaTime);
	int  LateUpdate(float fDeltaTime);
	void Render(float fDeltaTime);
};

