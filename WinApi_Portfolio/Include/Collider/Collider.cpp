#include "Collider.h"
#include "../GameObject/GraphicObj.h"

CCollider::CCollider() :
	m_eType(CT_NONE),
	m_pObj(NULL),
	m_bCollision(false)
{
}

CCollider::CCollider(const CCollider& collider)
{
	m_eType = collider.m_eType;
}

CCollider::~CCollider()
{
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->EraseCollider(this);
	}

	EraseCollider();
}

void CCollider::SetObj(CGraphicObj* pObj)
{
	m_pObj = pObj;
	pObj->AddRef();
}

void CCollider::AddCollider(CCollider* pColl)
{
	pColl->AddRef();
	m_ColliderList.push_back(pColl);
}

bool CCollider::CheckColliderList(CCollider* pColl)
{
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter) == pColl)
		{
			return true;
		}
	}
	return false;
}

CCollider* CCollider::CheckColliderList(const string& strTag)
{
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
		{
			return *iter;
		}
	}
	return NULL;
}

bool CCollider::EraseCollider(const string& strTag)
{
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
		{
			SAFE_RELEASE((*iter));
			m_ColliderList.erase(iter);
			return true;
		}
	}
	return false;
}

bool CCollider::EraseCollider(CCollider* pColl)
{
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter) == pColl)
		{
			SAFE_RELEASE((*iter));
			m_ColliderList.erase(iter);
			return true;
		}
	}
	return false;
}

void CCollider::EraseCollider()
{
	Safe_Release_VecList(m_ColliderList);
}

bool CCollider::Init()
{
	return true;
}

void CCollider::Input(float fDeltaTime)
{
}

int CCollider::Update(float fDeltaTime)
{
	return 0;
}

bool CCollider::Collision(CCollider* pDest)
{
	return false;
}

int CCollider::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CCollider::Render(HDC hDC, float fDeltaTime)
{
}
