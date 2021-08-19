#pragma once
#include "StaticObj.h"
class CEffect :
    public CStaticObj
{
private:
	friend class CMoveObj;

private:
	CEffect();
	CEffect(const CEffect& effect);
	~CEffect();

private:
	class CGraphicObj* m_pObj;
	EFFECT_TYPE		  m_eType;
	string			  m_strClipName;

public:
	void SetObj(CGraphicObj* pObj)
	{
		m_pObj = pObj;
	}

	void SetType(EFFECT_TYPE eType);

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

