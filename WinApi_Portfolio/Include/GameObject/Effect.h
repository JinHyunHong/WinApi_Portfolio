#pragma once
#include "StaticObj.h"
class CEffect :
    public CStaticObj
{
private:
	friend class CGameObj;
	friend class CScene;

private:
	CEffect();
	CEffect(const CEffect& effect);
	~CEffect();

private:
	class CMoveObj* m_pObj;

public:
	void SetObj(CMoveObj* pObj)
	{
		m_pObj = pObj;
	}

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

