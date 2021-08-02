#include "ColliderPoint.h"
#include "../Logic/Math.h"
#include "ColliderRect.h"
#include "ColliderPixel.h"
#include "ColliderSphere.h"

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

bool CColliderPoint::Collision(CCollider* pDest)
{
	switch (pDest->GetColliderType())
	{
	case CT_SPHERE:
		return CMath::SphereToPoint(((CColliderSphere*)pDest)->GetWorldInfo(), m_tPos);
	case CT_RECT:
		return CMath::RectToPoint(((CColliderRect*)pDest)->GetWorldInfo(), m_tPos);
	case CT_PIXEL:
		return CMath::PointToPixel(m_tPos, ((CColliderPixel*)pDest)->GetPixel(), ((CColliderPixel*)pDest)->GetWidth(),
			((CColliderPixel*)pDest)->GetHeight());
	}

	return false;
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
