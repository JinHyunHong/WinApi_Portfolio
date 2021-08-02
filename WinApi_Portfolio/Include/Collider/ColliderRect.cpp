#include "ColliderRect.h"
#include "../Logic/Camera.h"
#include "../Logic/Math.h"

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

	return true;
}

void CColliderRect::Input(float fDeltaTime)
{
	CCollider::Input(fDeltaTime);
}

int CColliderRect::Update(float fDeltaTime)
{
	CCollider::Update(fDeltaTime);
	return 0;
}

void CColliderRect::Collision(CCollider* pDest)
{
	switch (pDest->GetColliderType())
	{
	case CT_POINT:
		break;
	case CT_RECT:
		break;
	case CT_SPHERE:
		break;
	case CT_PIXEL:
		break;
	}
}

int CColliderRect::LateUpdate(float fDeltaTime)
{
	CCollider::LateUpdate(fDeltaTime);

	POSITION tPos = m_pObj->GetPos();
	m_tWorldInfo.l = tPos.x + m_tInfo.l;
	m_tWorldInfo.t = tPos.y + m_tInfo.t;
	m_tWorldInfo.r = tPos.x + m_tInfo.r;
	m_tWorldInfo.b = tPos.y + m_tInfo.b;

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

	MoveToEx(hDC, tRC.l, tRC.t, NULL);
	LineTo(hDC, tRC.l, tRC.b);	
	LineTo(hDC, tRC.r, tRC.b);	
	LineTo(hDC, tRC.r, tRC.t);	
	LineTo(hDC, tRC.l, tRC.t);

#endif
}
