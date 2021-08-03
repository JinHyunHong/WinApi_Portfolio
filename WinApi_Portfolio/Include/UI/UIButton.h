#pragma once
#include "UI.h"
class CUIButton :
    public CUI
{
private:
	friend class CScene;
	friend class CUI;

private:
	CUIButton();
	CUIButton(const CUIButton& btn);
	virtual ~CUIButton();

private:
	function<void(float fTime)> m_BtnCallBack;
	bool						m_bEnableCallBack;
	BUTTON_STATE				m_eState;

public:
	template<typename T>
	void SetBtnCallBack(T* pObj, void(T::* pFunc)(float))
	{
		m_BtnCallBack = bind(pFunc, pObj, placeholders::_1);
		m_bEnableCallBack = true;
	}

	void SetBtnCallBack(void(*pFunc)(float))
	{
		m_BtnCallBack = bind(pFunc, placeholders::_1);
		m_bEnableCallBack = true;
	}

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);

public:
	void MouseOn(class CCollider* pSrc, class CCollider* pDest, float fDeltaTime);
	void MouseOut(class CCollider* pSrc, class CCollider* pDest, float fDeltaTime);
};

