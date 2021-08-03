#include "Scene.h"
#include "Layer.h"

CScene::CScene()
{
}

CScene::~CScene()
{
	Safe_Delete_VecList(m_LayerList);
}

CLayer* CScene::FindLayer(const string& strTag) 
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
		{
			return *iter;
		}
	}

	return NULL;
}

bool CScene::LayerSort(const CLayer* pLayerSrc, const CLayer* pLayerDest)
{
	return pLayerSrc->GetZOrder() < pLayerDest->GetZOrder();
}

bool CScene::Init()
{
	CreateLayer("UI", INT_MAX);	
	CreateLayer("GameObject", INT_MAX - 1);
	CreateLayer("BackGround", INT_MAX - 2);

    return true;
}

void CScene::Input(float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetLife())
		{
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
			continue;
		}

		(*iter)->Input(fDeltaTime);
	}
}

int CScene::Update(float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetLife())
		{
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
			continue;
		}

		(*iter)->Update(fDeltaTime);
	}
    return 0;
}

int CScene::LateUpdate(float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetLife())
		{
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
			continue;
		}

		(*iter)->LateUpdate(fDeltaTime);
	}
    return 0;
}

void CScene::Collision(float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetLife())
		{
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
			continue;
		}

		(*iter)->Collision(fDeltaTime);
	}
}

void CScene::Render(HDC hDC, float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetLife())
		{
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
			continue;
		}

		(*iter)->Render(hDC, fDeltaTime);
	}
}
