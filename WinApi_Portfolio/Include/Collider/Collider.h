#pragma once
#include "../Obj.h"
#include "../Game.h"
#include "../GameObject/GraphicObj.h"

class CCollider :
    public CObj
{
private:
	friend class CGraphicObj;

private:
	CCollider();
	CCollider(const CCollider& collider);
	virtual ~CCollider();

private:
	COLLIDER_TYPE		m_eType;
	class CGraphicObj*	m_pObj;
	// 나와 충돌하고 있는 콜라이더 목록
	list<CCollider*>	m_ColliderList;

public:
	void SetColliderType(COLLIDER_TYPE eType)
	{
		m_eType = eType;
	}

	COLLIDER_TYPE GetColliderType()
	{
		return m_eType;
	}

	void SetObj(CGraphicObj* pObj)
	{
		m_pObj = pObj;
		pObj->AddRef();
	}

	CGraphicObj* GetObj()	const
	{
		return m_pObj;
	}

public:
	void AddCollider(CCollider* pColl);
	CCollider* FindCollider(const string& strTag);
	bool EraseCollider(const string& strTag);
	void EraseCollider();


public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);

};

