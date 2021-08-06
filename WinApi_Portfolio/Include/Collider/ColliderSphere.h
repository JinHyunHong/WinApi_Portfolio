#pragma once
#include "Collider.h"
class CColliderSphere :
    public CCollider
{
private:
	friend class CGraphicObj;
	friend class CColliderManager;

private:
	CColliderSphere();
	CColliderSphere(const CColliderSphere& sphere);
	virtual ~CColliderSphere();

private:
	SPHERE	m_tInfo;
	SPHERE	m_tWorldInfo;

public:
	SPHERE GetWorldInfo()	const
	{
		return m_tWorldInfo;
	}

	SPHERE GetInfo()	const
	{
		return m_tInfo;
	}

	void SetInfo(const SPHERE& tInfo)
	{
		m_tInfo = tInfo;
	}

	void SetInfo(float fRadius, const POSITION& tCenter)
	{
		m_tInfo.fRadius = fRadius;
		m_tInfo.tCenter = tCenter;
	}

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual bool Collision(CCollider* pDest);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

