#include "UIButton.h"
#include "../Collider/ColliderRect.h"
#include "../Logic/InputManager.h"

CUIButton::CUIButton() :
	m_bEnableCallBack(false),
	m_eState(BS_NONE)
{
}

CUIButton::CUIButton(const CUIButton& btn) :
	CUI(btn)
{
	m_bEnableCallBack = false;
	m_eState = BS_NONE;
}

CUIButton::~CUIButton()
{
}

bool CUIButton::Init()
{
	// 버튼 충돌체
	CColliderRect* pColl = AddCollider<CColliderRect>("ButtonBody");

	pColl->AddFunction(CS_ENTER, this,
		&CUIButton::MouseOn);
	pColl->AddFunction(CS_LEAVE, this,
		&CUIButton::MouseOut);

	SAFE_RELEASE(pColl);


	return true;
}

void CUIButton::Input(float fDeltaTime)
{
	CUI::Input(fDeltaTime);
}

int CUIButton::Update(float fDeltaTime)
{
	CUI::Update(fDeltaTime);
	return 0;
}

int CUIButton::LateUpdate(float fDeltaTime)
{
	CUI::LateUpdate(fDeltaTime);

	// LBUTTON CLICK을 했는지 아닌지 판단
	// NONE 상태가 아닐시만 판단 왜? 마우스가 올라가 있어야 판단하지
	if (m_eState != BS_NONE)
	{
		// 누르고 있을때도 클릭 상태가 되니까
		if (KEYPRESS("MouseLButton"))
		{
			m_eState = BS_CLICK;
			// 클릭일 시 두배만큼 오프셋을 잡아준다.
			SetImageOffset(m_tSize.x * 2.f, 0.f);
		}
	}

	// 클릭 상태이고 눌러서 뗴었을떄
	if (m_eState == BS_CLICK && KEYUP("MouseLButton"))
	{
		m_eState = BS_ON;
		SetImageOffset(m_tSize.x, 0.f);
		// 함수 포인터로 호출 : 각 버튼 마다 기능들이 
		// 다르기에 이렇게 처리(클래스를 여러개 만들 필요 없다.)
		if (m_bEnableCallBack)
			m_BtnCallBack(fDeltaTime);
	}
	return 0;
}

void CUIButton::Collision(float fDeltaTime)
{
	CUI::Collision(fDeltaTime);
}

void CUIButton::Render(HDC hDC, float fDeltaTime)
{
	CUI::Render(hDC, fDeltaTime);
}

void CUIButton::MouseOn(CCollider* pSrc, CCollider* pDest, float fDeltaTime)
{
	if (pDest->GetTag() == "Mouse")
	{
		m_eState = BS_ON;
		SetImageOffset(m_tSize.x, 0.f);
	}
}

// 마우스 빠져나갈때
void CUIButton::MouseOut(CCollider* pSrc, CCollider* pDest, float fDeltaTime)
{
	if (pDest->GetTag() == "Mouse")
	{
		m_eState = BS_NONE;
		SetImageOffset(0.f, 0.f);
	}
}
