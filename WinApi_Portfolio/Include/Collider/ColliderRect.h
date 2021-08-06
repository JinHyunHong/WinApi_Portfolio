#pragma once
#include "Collider.h"
class CColliderRect :
    public CCollider
{
private:
	friend class CGraphicObj;
	friend class CColliderManager;

private:
	CColliderRect();
	CColliderRect(const CColliderRect& rect);
	virtual ~CColliderRect();

private:
	RECTANGLE	m_tInfo;
	RECTANGLE	m_tWorldInfo;

public:
	RECTANGLE GetWorldInfo()	const
	{
		return m_tWorldInfo;
	}
	
	RECTANGLE GetInfo()	const
	{
		return m_tInfo;
	}

	void SetInfo(const RECTANGLE& tInfo)
	{
		m_tInfo = tInfo;
	}

	void SetInfo(float l, float t, float r, float b)
	{
		m_tInfo.l = l;
		m_tInfo.t = t;
		m_tInfo.r = r;
		m_tInfo.b = b;
	}

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual bool Collision(CCollider* pDest);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

