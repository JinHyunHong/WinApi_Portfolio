#pragma once

#include "../Game.h"

class CTimer
{
	DECLARE_SINGLE(CTimer);

private:
	HWND		  m_hWnd;

private:
	float	      m_fFPS;
	float		  m_fFPSTime;
	float	      m_fDeltaTime;
	LARGE_INTEGER m_tSecond;
	int			  m_iFrame;
	LARGE_INTEGER m_tTime;

public:
	bool Init(HWND hWnd);
	void Update();

public:
	float GetDeltaTime()
	{
		return m_fDeltaTime;
	}

	float GetFPS()
	{
		return m_fFPS;
	}
};

