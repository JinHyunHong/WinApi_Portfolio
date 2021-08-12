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
	class CMoveObj* m_pObj;
	int				m_iCount;
	int				m_iLimitCount;
	EFFECT_TYPE		m_eType;
	string			m_strClipName;

public:
	void SetObj(CMoveObj* pObj)
	{
		m_pObj = pObj;
	}

	void SetType(EFFECT_TYPE eType);


	void SetLimitCount(int iLimitCount)
	{
		m_iLimitCount = iLimitCount;
	}

	void AddCount(int iCount)
	{
		m_iCount += iCount;
	}

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

