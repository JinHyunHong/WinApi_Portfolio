#pragma once

#include "../Game.h"

class CGameObj
{
	DECLARE_REFERENCE_COUNT();

private:
	CGameObj();
	virtual ~CGameObj() = 0;

private:
	string					m_strTag;
	POSITION				m_tPos;

public:
	string GetTag()		const
	{
		return m_strTag;
	}

	void SetTag(const string& strTag)
	{
		m_strTag = strTag;
	}

private:
	static list<CGameObj*> m_ObjList;

public:
	template<typename T>
	static T* CreateGameObj(const string& strTag)
	{
		T* pGameObj = new T;

		if (!pGameObj->Init())
		{
			SAFE_RELEASE(pGameObj);
			return NULL;
		}

		pGameObj->SetTag(strTag);
		m_ObjList.push_back(pGameObj);
		return pGameObj;
	}

	static CGameObj* FindGameObj(const string& strTag);
	static bool DeleteGameObj(const string& strTag);
	static void DeleteGameObj();

public:
	bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(float fDeltaTime);

};

