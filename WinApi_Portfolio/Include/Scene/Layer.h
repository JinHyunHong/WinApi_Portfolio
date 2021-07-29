#pragma once

#include "../Game.h"

class CLayer
{
private:
	friend class CScene;

private:
	CLayer();
	~CLayer();

private:
	string					 m_strTag;
	int						 m_iZOrder;
	class CScene*			 m_pScene;
	list<class CGameObj*>	 m_ObjList;
	bool					 m_bLife;

public:
	void AddObj(class CGameObj* pGameObj);
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
	void Input(float fDeltaTime);
	int Update(float fDeltaTime);
	int LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(HDC hDC, float fDeltaTime);
};

