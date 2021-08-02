#include "UIPanel.h"

CUIPanel::CUIPanel()
{
}

CUIPanel::CUIPanel(const CUIPanel& ui)	:
	CUI(ui)
{
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
	CUI::Render(hDC, fDeltaTime);
}
