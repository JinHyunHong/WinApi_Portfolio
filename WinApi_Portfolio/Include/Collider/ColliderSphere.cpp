#include "ColliderSphere.h"
#include "../Logic/Math.h"
#include "../GameObject/GraphicObj.h"
#include "ColliderPoint.h"
#include "ColliderPixel.h"
#include "ColliderRect.h"
#include "../Logic/Camera.h"


CColliderSphere::CColliderSphere()
{
}

CColliderSphere::CColliderSphere(const CColliderSphere& sphere)	:
	CCollider(sphere)
{
}

CColliderSphere::~CColliderSphere()
{
}

bool CColliderSphere::Init()
{
	m_eType = CT_SPHERE;

	if (m_pObj)
	{
		POSITION tPos = m_pObj->GetPos();
		m_tWorldInfo.tCenter = tPos + m_tInfo.tCenter;
		m_tWorldInfo.fRadius = m_tInfo.fRadius;
	}


	return true;
}

void CColliderSphere::Input(float fDeltaTime)
{
	CCollider::Input(fDeltaTime);
}

int CColliderSphere::Update(float fDeltaTime)
{
	CCollider::Update(fDeltaTime);

	POSITION tPos = m_pObj->GetPos();
	m_tWorldInfo.tCenter = tPos + m_tInfo.tCenter;
	m_tWorldInfo.fRadius = m_tInfo.fRadius;


	return 0;
}

bool CColliderSphere::Collision(CCollider* pDest)
{
	switch (pDest->GetColliderType())
	{
	case CT_POINT:
		return CMath::SphereToPoint(m_tWorldInfo, ((CColliderPoint*)pDest)->GetPos());
	case CT_SPHERE:
		return CMath::SphereToSphere(m_tWorldInfo, ((CColliderSphere*)pDest)->GetWorldInfo());
	case CT_RECT:
		return CMath::RectToSphere(((CColliderRect*)pDest)->GetWorldInfo(), m_tWorldInfo);
	}

	return false;
}

int CColliderSphere::LateUpdate(float fDeltaTime)
{
	CCollider::LateUpdate(fDeltaTime);

	return 0;
}

void CColliderSphere::Render(HDC hDC, float fDeltaTime)
{
#ifdef _DEBUG
	CCollider::Render(hDC, fDeltaTime);

	POSITION tPos = GET_SINGLE(CCamera)->GetPos();

	SPHERE tSR = m_tWorldInfo;

	tSR.tCenter -= tPos;

	SelectObject(hDC, GetStockObject(WHITE_PEN));
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Ellipse(hDC, tSR.tCenter.x - tSR.fRadius, tSR.tCenter.y - tSR.fRadius,
		tSR.tCenter.x + tSR.fRadius, tSR.tCenter.y + tSR.fRadius);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

#endif
}
