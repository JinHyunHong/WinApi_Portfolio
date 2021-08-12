#include "UIPanel.h"
#include "../GameObject/Player.h"
#include "../GameObject/Enemy.h"
#include "../Collider/ColliderRect.h"

CUIPanel::CUIPanel() :
	m_bStageBack(false)
{
}

CUIPanel::CUIPanel(const CUIPanel& ui)	:
	CUI(ui)
{
	m_bStageBack = ui.m_bStageBack;
}

CUIPanel::~CUIPanel()
{
}

bool CUIPanel::Init()
{
	return true;
}

void CUIPanel::Input(float fDeltaTime)
{
	CUI::Input(fDeltaTime);
}

int CUIPanel::Update(float fDeltaTime)
{
	CUI::Update(fDeltaTime);
	return 0;
}

void CUIPanel::Collision(float fDeltaTime)
{
	CUI::Collision(fDeltaTime);
}

int CUIPanel::LateUpdate(float fDeltaTime)
{
	CUI::LateUpdate(fDeltaTime);
	return 0;
}

void CUIPanel::Render(HDC hDC, float fDeltaTime)
{
	if (!m_bStageBack)
	{
		CUI::Render(hDC, fDeltaTime);
	}

	else
	{
		CGraphicObj::Render(hDC, fDeltaTime);
	}
}
