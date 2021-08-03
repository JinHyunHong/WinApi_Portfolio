#pragma once
#include "UI.h"
class CMouse :
    public CUI
{
private:
	friend class CScene;
	friend class CUI;

private:
	CMouse();
	CMouse(const CMouse& mouse);
	virtual ~CMouse();

private:
	POSITION m_tMove;
	POSITION m_tWorldPos;

public:
	POSITION GetMove()	const
	{
		return m_tMove;
	}

	POSITION GetWorldPos()	const
	{
		return m_tWorldPos;
	}

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

