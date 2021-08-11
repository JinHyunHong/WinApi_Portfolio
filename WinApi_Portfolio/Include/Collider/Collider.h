#pragma once
#include "../Obj.h"

class CCollider :
    public CObj
{
private:
	friend class CGraphicObj;
	friend class CColliderManager;

protected:
	CCollider();
	CCollider(const CCollider& collider);
	virtual ~CCollider() = 0;

protected:
	COLLIDER_TYPE										m_eType;
	class CGraphicObj*									m_pObj;
	// 나와 충돌하고 있는 콜라이더 목록
	list<CCollider*>									m_ColliderList;
	list<function<void(CCollider*, CCollider*, float)>> m_FunList[CS_END];
	bool												m_bCollision;

public:
	void AddFunction(COLLIDER_STATE eState,
		void(*pFunc)(CCollider*, CCollider*, float))
	{
		function<void(CCollider*, CCollider*, float)> func;

		func = bind(pFunc, placeholders::_1, placeholders::_2, placeholders::_3);

		m_FunList[eState].push_back(func);
	}

	template<typename T>
	void AddFunction(COLLIDER_STATE eState, T* pObj,
		void(T::*pFunc)(CCollider*, CCollider*, float))
	{
		function<void(CCollider*, CCollider*, float)> func;
		
		func = bind(pFunc, pObj, placeholders::_1, placeholders::_2, placeholders::_3);

		m_FunList[eState].push_back(func);
	}

	void CallFunction(COLLIDER_STATE eState,
		CCollider* pDest, float fDeltaTime)
	{
		list<function<void(CCollider*, CCollider*, float)>>::iterator iter;
		list<function<void(CCollider*, CCollider*, float)>>::iterator iterEnd = m_FunList[eState].end();

		for (iter = m_FunList[eState].begin(); iter != iterEnd; ++iter)
		{
			(*iter)(this, pDest, fDeltaTime);
		}
	}

public:
	void SetColliderType(COLLIDER_TYPE eType)
	{
		m_eType = eType;
	}

	COLLIDER_TYPE GetColliderType()
	{
		return m_eType;
	}

	void SetObj(CGraphicObj* pObj);

	CGraphicObj* GetObj()	const
	{
		return m_pObj;
	}

	bool GetCollision()	const
	{
		return m_bCollision;
	}



	list<CCollider*>* GetColliderList()
	{
		return &m_ColliderList;
	}



public:
	void AddCollider(CCollider* pColl);
	bool CheckColliderList(CCollider* pColl);
	CCollider* CheckColliderList(const string& strTag);
	bool EraseCollider(CCollider* pColl);
	bool EraseCollider(const string& strTag);
	void EraseCollider();


public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual bool Collision(CCollider* pDest);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);

};

