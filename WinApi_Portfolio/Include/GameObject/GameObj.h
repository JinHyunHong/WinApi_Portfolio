#pragma once

#include "../Game.h"
#include "../Scene/Layer.h"
#include "../Obj.h"

class CGameObj	:
	public CObj
{
protected:
	CGameObj();
	CGameObj(const CGameObj& GameObj);
	virtual ~CGameObj();

private:
	static list<CGameObj*> m_ObjList;

public:
	template<typename T>
	static T* CreateGameObj(const string& strTag, class CLayer* pLayer)
	{
		T* pGameObj = new T;

		if (!pGameObj->Init())
		{
			SAFE_RELEASE(pGameObj);
			return NULL;
		}

		pGameObj->SetTag(strTag);
		m_ObjList.push_back(pGameObj);
		pLayer->AddObj(pGameObj);
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
