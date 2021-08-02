#include "ColliderPoint.h"

CColliderPoint::CColliderPoint()
{
}

CColliderPoint::CColliderPoint(const CColliderPoint& point)	:
	CCollider(point)
{
}

CColliderPoint::~CColliderPoint()
{
}

bool CColliderPoint::Init()
{
	m_eType = CT_POINT;

	return true;
}

void CColliderPoint::Input(float fDeltaTime)
{
	CCollider::Input(fDeltaTime);
}

int CColliderPoint::Update(float fDeltaTime)
{
	CCollider::Update(fDeltaTime);
	return 0;
}

void CColliderPoint::Collision(CCollider* pDest)
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

int CColliderPoint::LateUpdate(float fDeltaTime)
{
	CCollider::LateUpdate(fDeltaTime);

	POSITION tPos = m_pObj->GetPos();
	m_tPos.x = tPos.x + m_tDist.x;
	m_tPos.y = tPos.y + m_tDist.y;

	return 0;
}

void CColliderPoint::Render(HDC hDC, float fDeltaTime)
{
	CCollider::Render(hDC, fDeltaTime);
}
