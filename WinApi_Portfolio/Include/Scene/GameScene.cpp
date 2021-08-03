#include "GameScene.h"
#include "../GameObject/GameObj.h"
#include "../GameObject/Player.h"
#include "../UI/UI.h"
#include "../UI/UIPanel.h"
#include "../Logic/Camera.h"
#include "../Collider/ColliderRect.h"

CGameScene::CGameScene()
{
}

CGameScene::~CGameScene()
{
}

bool CGameScene::Init()
{
	CLayer* pLayer = FindLayer("GameObject");
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
