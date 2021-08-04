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

private:
	// �������� ��׶���� ī�޶��� ������ �޾ƾ��Ѵ�.
	bool m_bStageBack;

public:
	bool GetStageBack()	const
	{
		return m_bStageBack;
	}

	void SetStageBack(bool bStageBack)
	{
		m_bStageBack = bStageBack;
	}

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

