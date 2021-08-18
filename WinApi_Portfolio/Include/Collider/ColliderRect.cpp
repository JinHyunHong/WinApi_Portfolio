#include "ColliderRect.h"
#include "../Logic/Camera.h"
#include "../Logic/Math.h"
#include "../GameObject/GraphicObj.h"
#include "ColliderPoint.h"
#include "ColliderPixel.h"
#include "ColliderSphere.h"

CColliderRect::CColliderRect()
{
}

CColliderRect::CColliderRect(const CColliderRect& rect)	:
	CCollider(rect)
{
}

CColliderRect::~CColliderRect()
{
}

bool CColliderRect::Init()
{
	m_eType = CT_RECT;


	if (m_pObj)
	{
		POSITION tPos = m_pObj->GetPos();
		m_tWorldInfo.l = tPos.x + m_tInfo.l;
		m_tWorldInfo.t = tPos.y + m_tInfo.t;
		m_tWorldInfo.r = tPos.x + m_tInfo.r;
		m_tWorldInfo.b = tPos.y + m_tInfo.b;
	}

	return true;
}

void CColliderRect::Input(float fDeltaTime)
{
	CCollider::Input(fDeltaTime);
}

int CColliderRect::Update(float fDeltaTime)
{
	CCollider::Update(fDeltaTime);

	POSITION tPos = m_pObj->GetPos();
	m_tWorldInfo.l = tPos.x + m_tInfo.l;
	m_tWorldInfo.t = tPos.y + m_tInfo.t;
	m_tWorldInfo.r = tPos.x + m_tInfo.r;
	m_tWorldInfo.b = tPos.y + m_tInfo.b;

	return 0;
}

bool CColliderRect::Collision(CCollider* pDest)
{
	switch (pDest->GetColliderType())
	{
	case CT_POINT:
		return CMath::RectToPoint(m_tWorldInfo, ((CColliderPoint*)pDest)->GetPos());
	case CT_RECT:
		return CMath::RectToRect(m_tWorldInfo, ((CColliderRect*)pDest)->GetWorldInfo());
	case CT_SPHERE:
		return CMath::RectToSphere(m_tWorldInfo, ((CColliderSphere*)pDest)->GetWorldInfo());
	case CT_PIXEL:
		return CMath::RectToPixel(m_tWorldInfo, ((CColliderPixel*)pDest)->GetPixel(), ((CColliderPixel*)pDest)->GetWidth(),
			((CColliderPixel*)pDest)->GetHeight(), ((CColliderPixel*)pDest)->GetCollRGB().r, ((CColliderPixel*)pDest)->GetCollRGB().g,
			((CColliderPixel*)pDest)->GetCollRGB().b);
	}

	return false;
}

int CColliderRect::LateUpdate(float fDeltaTime)
{
	CCollider::LateUpdate(fDeltaTime);


	return 0;
}

void CColliderRect::Render(HDC hDC, float fDeltaTime)
{
	
#ifdef _DEBUG
	CCollider::Render(hDC, fDeltaTime);

	POSITION tPos = GET_SINGLE(CCamera)->GetPos();

	RECTANGLE tRC = m_tWorldInfo;

	tRC.l -= tPos.x;
	tRC.r -= tPos.x;
	tRC.t -= tPos.y;
	tRC.b -= tPos.y;

	SelectObject(hDC, GetStockObject(WHITE_PEN));

	MoveToEx(hDC, tRC.l, tRC.t, NULL);
	LineTo(hDC, tRC.l, tRC.b);	
	LineTo(hDC, tRC.r, tRC.b);	
	LineTo(hDC, tRC.r, tRC.t);	
	LineTo(hDC, tRC.l, tRC.t);

#endif
}
