#include "Layer.h"
#include "../Obj.h"

CLayer::CLayer()	:
	m_iZOrder(0),
	m_bLife(true),
	m_pScene(NULL)
{
}

CLayer::CLayer(const CLayer& layer)
{
}

CLayer::~CLayer()
{
	Safe_Release_VecList(m_ObjList);
}


void CLayer::AddObj(CObj* pObj)
{
	pObj->AddRef();
	m_ObjList.push_back(pObj);
}

void CLayer::EraseObj(const string& strTag)
{
	list<class CObj*>::iterator iter;
	list<class CObj*>::iterator iterEnd = m_ObjList.end();

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
	list<class CObj*>::iterator iter;
	list<class CObj*>::iterator iterEnd = m_ObjList.end();

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
	list<class CObj*>::iterator iter;
	list<class CObj*>::iterator iterEnd = m_ObjList.end();

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
	list<class CObj*>::iterator iter;
	list<class CObj*>::iterator iterEnd = m_ObjList.end();

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
	list<class CObj*>::iterator iter;
	list<class CObj*>::iterator iterEnd = m_ObjList.end();

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
