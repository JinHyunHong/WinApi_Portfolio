#include "Collider.h"

CCollider::CCollider()	:
	m_eType(CT_NONE),
	m_pObj(NULL)
{
}

CCollider::CCollider(const CCollider& collider)
{
	m_eType = collider.m_eType;
}

CCollider::~CCollider()
{
	Safe_Release_VecList(m_ColliderList);
}

void CCollider::AddCollider(CCollider* pColl)
{
	pColl->AddRef();
	m_ColliderList.push_back(pColl);
}

CCollider* CCollider::FindCollider(const string& strTag)
{
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
		{
			(*iter)->AddRef();

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

void CCollider::Collision(float fDeltaTime)
{
}

int CCollider::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CCollider::Render(HDC hDC, float fDeltaTime)
{
}
