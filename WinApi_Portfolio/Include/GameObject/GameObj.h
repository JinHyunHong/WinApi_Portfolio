#pragma once

#include "../Game.h"

class CGameObj
{
	DECLARE_REFERENCE_COUNT();

protected:
	CGameObj();
	CGameObj(const CGameObj& GameObj);
	virtual ~CGameObj() = 0;

protected:
	string					m_strTag;
	POSITION				m_tPos;
	POSITION				m_tPivot;
	_SIZE					m_tSize;

public:
	string GetTag()		const
	{
		return m_strTag;
	}

	void SetTag(const string& strTag)
	{
		m_strTag = strTag;
	}

	POSITION GetPos()		const
	{
		return m_tPos;
	}

	void SetPos(const POSITION& tPos)
	{
		m_tPos = tPos;
	}

	void SetPos(float x, float y)
	{
		m_tPos.x = x;
		m_tPos.y = y;
	}

	POSITION GetPivot()		const
	{
		return m_tPivot;
	}

	void SetPivot(const POSITION& tPivot)
	{
		m_tPivot = tPivot;
	}

	void SetPivot(float x, float y)
	{
		m_tPivot.x = x;
		m_tPivot.y = y;
	}

	_SIZE GetSize()		const
	{
		return m_tSize;
	}

	void SetSize(const _SIZE& tSize)
	{
		m_tSize = tSize;
	}

	void SetSize(float x, float y)
	{
		m_tSize.x = x;
		m_tSize.y = y;
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
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);

};

