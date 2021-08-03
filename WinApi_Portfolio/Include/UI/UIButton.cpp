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
	// ��ư �浹ü
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

	// LBUTTON CLICK�� �ߴ��� �ƴ��� �Ǵ�
	// NONE ���°� �ƴҽø� �Ǵ� ��? ���콺�� �ö� �־�� �Ǵ�����
	if (m_eState != BS_NONE)
	{
		// ������ �������� Ŭ�� ���°� �Ǵϱ�
		if (KEYPRESS("MouseLButton"))
		{
			m_eState = BS_CLICK;
			// Ŭ���� �� �ι踸ŭ �������� ����ش�.
			SetImageOffset(m_tSize.x * 2.f, 0.f);
		}
	}

	// Ŭ�� �����̰� ������ �������
	if (m_eState == BS_CLICK && KEYUP("MouseLButton"))
	{
		m_eState = BS_ON;
		SetImageOffset(m_tSize.x, 0.f);
		// �Լ� �����ͷ� ȣ�� : �� ��ư ���� ��ɵ��� 
		// �ٸ��⿡ �̷��� ó��(Ŭ������ ������ ���� �ʿ� ����.)
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

// ���콺 ����������
void CUIButton::MouseOut(CCollider* pSrc, CCollider* pDest, float fDeltaTime)
{
	if (pDest->GetTag() == "Mouse")
	{
		m_eState = BS_NONE;
		SetImageOffset(0.f, 0.f);
	}
}
