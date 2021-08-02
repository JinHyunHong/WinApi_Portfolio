#include "ColliderSphere.h"

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

	return true;
}

void CColliderSphere::Input(float fDeltaTime)
{
	CCollider::Input(fDeltaTime);
}

int CColliderSphere::Update(float fDeltaTime)
{
	CCollider::Update(fDeltaTime);
	return 0;
}

void CColliderSphere::Collision(CCollider* pDest)
{
	switch (pDest->GetColliderType())
	{
	case CT_POINT:
		break;
	case CT_SPHERE:
		break;
	case CT_RECT:
		break;
	case CT_PIXEL:
		break;
	}
}

int CColliderSphere::LateUpdate(float fDeltaTime)
{
	CCollider::LateUpdate(fDeltaTime);

	POSITION tPos = m_pObj->GetPos();
	m_tWorldInfo.tCenter = tPos + m_tInfo.tCenter;
	m_tWorldInfo.fRadius = m_tInfo.fRadius;

	return 0;
}

void CColliderSphere::Render(HDC hDC, float fDeltaTime)
{
	CCollider::Render(hDC, fDeltaTime);
}
