#include "Layer.h"
#include "../GameObject/GraphicObj.h"
#include "../Collider/ColliderManager.h"

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


void CLayer::AddObj(CGraphicObj* pObj)
{
	if (pObj)
	{
		pObj->AddRef();
		m_ObjList.push_back(pObj);
	}
}

void CLayer::EraseObj(const string& strTag)
{
	list<class CGraphicObj*>::iterator iter;
	list<class CGraphicObj*>::iterator iterEnd = m_ObjList.end();

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
	list<class CGraphicObj*>::iterator iter;
	list<class CGraphicObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetLife())
		{
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();

			if (iter == iterEnd)
				return;
		}

		if (!(*iter)->GetEnable())
		{
			continue;
		}

		(*iter)->Input(fDeltaTime);
	}
}

int CLayer::Update(float fDeltaTime)
{
	list<class CGraphicObj*>::iterator iter;
	list<class CGraphicObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetLife())
		{
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();

			if (iter == iterEnd)
				return 0;
		}

		if (!(*iter)->GetEnable())
		{
			continue;
		}

		(*iter)->Update(fDeltaTime);
	}

	return 0;
}

int CLayer::LateUpdate(float fDeltaTime)
{
	list<class CGraphicObj*>::iterator iter;
	list<class CGraphicObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetLife())
		{
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();

			if (iter == iterEnd)
				return 0;
		}

		if (!(*iter)->GetEnable())
		{
			continue;
		}

		(*iter)->LateUpdate(fDeltaTime);
	}
	return 0;
}

void CLayer::Collision(float fDeltaTime)
{
	list<class CGraphicObj*>::iterator iter;
	list<class CGraphicObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetLife())
		{
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			
			if (iter == iterEnd)
				return;
		}

		if (!(*iter)->GetEnable())
		{
			continue;
		}

		else
			GET_SINGLE(CColliderManager)->AddObj(*iter);
	}
}

void CLayer::Render(HDC hDC, float fDeltaTime)
{
	list<class CGraphicObj*>::iterator iter;
	list<class CGraphicObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetLife())
		{
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();

			if (iter == iterEnd)
				return;
		}

		if (!(*iter)->GetEnable())
		{
			continue;
		}

		(*iter)->Render(hDC, fDeltaTime);
	}
}
