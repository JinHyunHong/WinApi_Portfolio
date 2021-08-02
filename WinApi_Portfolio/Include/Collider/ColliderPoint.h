#pragma once
#include "Collider.h"
class CColliderPoint :
    public CCollider
{
private:
	friend class CGraphicObj;

private:
	CColliderPoint();
	CColliderPoint(const CColliderPoint& point);
	virtual ~CColliderPoint();

private:
	POSITION	m_tPos;
	POSITION	m_tDist;

public:
	POSITION GetPos()	const
	{
		return m_tPos;
	}

	void SetPos(const POSITION& tPos)
	{
		m_tPos = tPos;
	}

	POSITION GetDist()	const
	{
		return m_tDist;
	}

	void SetDist(const POSITION& tDist)
	{
		m_tDist = tDist;
	}

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual void Collision(CCollider* pDest);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

