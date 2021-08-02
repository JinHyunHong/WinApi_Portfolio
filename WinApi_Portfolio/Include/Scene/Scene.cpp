#include "Scene.h"
#include "Layer.h"
#include "../GameObject/GameObj.h"
#include "../GameObject/Player.h"
#include "../UI/UI.h"
#include "../UI/UIPanel.h"
#include "../Logic/Camera.h"
#include "../Collider/ColliderRect.h"

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
	CLayer* pLayer = CreateLayer("GameObject", INT_MAX - 1);
	CreateLayer("BackGround", INT_MAX - 2);

	CPlayer* pObj = CGameObj::CreateGameObj<CPlayer>("ObjectTest", pLayer);
	pObj->SetTexture("ObjTest", L"HOS.bmp");
	pObj->SetColorKey(255, 255, 255);
	pObj->SetPos(100.f, 100.f);
	pObj->SetSize(100.f, 100.f);
	pObj->SetPivot(0.5f, 0.5f);
	GET_SINGLE(CCamera)->SetTarget(pObj);

	CColliderRect* pRC = pObj->AddCollider<CColliderRect>("Hong");
	pRC->SetInfo(-35.f, -35.f, 35.f, 35.f);


	pLayer = FindLayer("UI");
	CreateLayer("BackGround", INT_MAX - 2);
	CUIPanel* pUIPanel = CUI::CreateUIObj<CUIPanel>("StageTest", pLayer);
	pUIPanel->SetTexture("StageTestImage", L"Stage\\Stage1\\Frame0.bmp");
	pUIPanel->SetColorKey(255, 255, 255);
	pUIPanel->SetPos(0.f, 0.f);
	pUIPanel->SetSize(2418.f, 720.f);
	// pUIPanel->SetPivot(0.5f, 0.5f);

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
