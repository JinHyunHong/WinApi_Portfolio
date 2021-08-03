#include "GameScene.h"
#include "../GameObject/GameObj.h"
#include "../GameObject/Player.h"
#include "../UI/UI.h"
#include "../UI/UIPanel.h"
#include "../Logic/Camera.h"

CGameScene::CGameScene()
{
}

CGameScene::~CGameScene()
{
}

bool CGameScene::Init()
{
	CScene::Init();

	CLayer* pLayer = FindLayer("GameObject");
	CPlayer* pObj = CGameObj::CreateGameObj<CPlayer>("ObjectTest", pLayer);
	GET_SINGLE(CCamera)->SetTarget(pObj);


	pLayer = FindLayer("UI");
	CreateLayer("BackGround", INT_MAX - 2);
	CUIPanel* pUIPanel = CUI::CreateUIObj<CUIPanel>("StageTest", pLayer);
	vector<wstring> vecFileName;

	for (int i = 0; i <= 7; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Stage\\Stage1\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}


	pUIPanel->CreateAnimation("Stage");
	pUIPanel->AddAnimationClip("Stage1", AT_FRAME, AO_LOOP, 1.f, 8, 1, 0, 0, 8, 1, 0.f, "GameStage1", vecFileName);
	
	return true;
}
