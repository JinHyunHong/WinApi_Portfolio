#pragma once

#include "../Game.h"

class CCamera
{
	DECLARE_SINGLE(CCamera);

private:
	POSITION		m_tPos;
	POSITION		m_tPivot;
	SCREENSIZE		m_tWorldRS;
	SCREENSIZE		m_tClientRS;
	class CGameObj* m_pTargetObj;

public:
	bool Init(SCREENSIZE tClientRS,
		SCREENSIZE tWorldRS);
	void Scroll(float x, float y);
	void Update();

public:
	POSITION GetPos()		const
	{
		return m_tPos;
	}

	void SetTarget(CGameObj* pTargetObj)	
	{
		m_pTargetObj = pTargetObj;
	}
};

