#include "Mouse.h"
#include "../Collider/ColliderPoint.h"
#include "../Logic/Camera.h"
#include "../Logic/Logic.h"

CMouse::CMouse()
{
}

CMouse::CMouse(const CMouse& mouse) :
	CUI(mouse)
{
}

CMouse::~CMouse()
{
}

bool CMouse::Init()
{
	POINT pt;

	GetCursorPos(&pt);
	ScreenToClient(WINDOWHANDLE, &pt);

	ShowCursor(FALSE);

	m_tPos = pt;

	POSITION tCamPos = GET_SINGLE(CCamera)->GetPos();
	m_tWorldPos = m_tPos + tCamPos;

	CColliderPoint* pColl = AddCollider<CColliderPoint>("Mouse");
	return true;
}

void CMouse::Input(float fDeltaTime)
{
	CUI::Input(fDeltaTime);
}

int CMouse::Update(float fDeltaTime)
{
	CUI::Update(fDeltaTime);

	POINT pt;

	GetCursorPos(&pt);
	ScreenToClient(WINDOWHANDLE, &pt);

	m_tMove.x = pt.x - m_tPos.x;
	m_tMove.y = pt.y - m_tPos.y;

	m_tPos = pt;

	POSITION tCamPos = GET_SINGLE(CCamera)->GetPos();
	m_tWorldPos = m_tPos + tCamPos;

	return 0;
}

int CMouse::LateUpdate(float fDeltaTime)
{
	CUI::LateUpdate(fDeltaTime);
	return 0;
}

void CMouse::Collision(float fDeltaTime)
{
	CUI::Collision(fDeltaTime);
}

void CMouse::Render(HDC hDC, float fDeltaTime)
{
	CUI::Render(hDC, fDeltaTime);
}