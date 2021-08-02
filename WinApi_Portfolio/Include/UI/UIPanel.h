#pragma once
#include "UI.h"
class CUIPanel :
    public CUI
{
private:
	friend class CScene;
	friend class CUI;

private:
	CUIPanel();
	CUIPanel(const CUIPanel& ui);
	virtual ~CUIPanel();

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

