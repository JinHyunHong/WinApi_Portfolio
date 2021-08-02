#pragma once

#include "../Game.h"

class CLayer
{
private:
	friend class CScene;

private:
	CLayer();
	CLayer(const CLayer& layer);

// 전역 매크로를 사용하기 위해
public:
	~CLayer();

private:
	string							 m_strTag;
	int								 m_iZOrder;
	class CScene*					 m_pScene;
	list<class CGraphicObj*>		 m_ObjList;
	bool							 m_bLife;

public:
	void AddObj(class CGraphicObj* pGrapicObj);
	void EraseObj(const string& strTag);
	void EraseObj();

public:
	void SetTag(const string& strTag)
	{
		m_strTag = strTag;
	}

	void SetZOrder(int iZOrder)
	{
		m_iZOrder = iZOrder;
	}

	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
	}

	int GetZOrder() const
	{
		return m_iZOrder;
	}

	string GetTag()	const
	{
		return m_strTag;
	}

	CScene* GetScene()	const
	{
		return m_pScene;
	}

	bool GetLife()	const
	{
		return m_bLife;
	}

	void Die(bool bLife)
	{
		m_bLife = bLife;
	}

public:
	bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

