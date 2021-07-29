#include "Layer.h"
#include "../GameObject/GameObj.h"

CLayer::CLayer()	:
	m_iZOrder(0)
{
}

CLayer::~CLayer()
{
	Safe_Release_VecList(m_ObjList);
}

void CLayer::AddObj(CGameObj* pGameObj)
{
	pGameObj->AddRef();
	m_ObjList.push_back(pGameObj);
}

void CLayer::EraseObj(const string& strTag)
{
	list<class CGameObj*>::iterator iter;
	list<class CGameObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		if((*iter)->GetTag() == strTag)
			SAFE_RELEASE((*iter));
	}
}

void CLayer::EraseObj()
{
	Safe_Release_VecList(m_ObjList);
}

bool CLayer::Init()
{
	return true;
}

void CLayer::Input(float fDeltaTime)
{
}

int CLayer::Update(float fDeltaTime)
{
	list<CGameObj*>::iterator iter;
	list<CGameObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetLife() == false)
		{
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			continue;
		}

		(*iter)->Update(fDeltaTime);
	}

	return 0;
}

int CLayer::LateUpdate(float fDeltaTime)
{
	list<CGameObj*>::iterator iter;
	list<CGameObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetLife() == false)
		{
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			continue;
		}

		(*iter)->LateUpdate(fDeltaTime);
	}
	return 0;
}

void CLayer::Collision(float fDeltaTime)
{
	list<CGameObj*>::iterator iter;
	list<CGameObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetLife() == false)
		{
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			continue;
		}

		(*iter)->Collision(fDeltaTime);
	}
}

void CLayer::Render(HDC hDC, float fDeltaTime)
{
	list<CGameObj*>::iterator iter;
	list<CGameObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetLife() == false)
		{
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			continue;
		}

		(*iter)->Render(hDC, fDeltaTime);
	}
}
