#include "GameScene.h"
#include "../GameObject/GameObj.h"
#include "../GameObject/Player.h"
#include "../UI/UI.h"
#include "../UI/UIPanel.h"
#include "../Logic/Camera.h"
#include "../Logic/Logic.h"

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

	CUIPanel* pUIPanel = CUI::CreateUIObj<CUIPanel>("StageTest", pLayer);
	
	vector<wstring> vecFileName;

	for (int i = 0; i <= 7; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Stage\\Stage1\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	pUIPanel->SetStageBack(true);
	pUIPanel->CreateAnimation("Stage");
	pUIPanel->AddAnimationClip("Stage1", AT_FRAME, AO_LOOP, 1.f, 8, 1, 0, 0, 8, 1, 0.f, "GameStage1", vecFileName);

	CUIPanel* pPlyaerBackPanelBlue = CUI::CreateUIObj<CUIPanel>("PlyaerBackPanelBlue", pLayer);
	pPlyaerBackPanelBlue->SetTexture("PlyaerBackPanelBlue", L"BlueTeam.bmp", UI_PATH);
	pPlyaerBackPanelBlue->SetColorKey(0, 0, 0);
	pPlyaerBackPanelBlue->SetPos(0.f, 0.f);
	pPlyaerBackPanelBlue->SetSize(160.f, 120.f);

	CUIPanel* pPlyaerBackPanelRed = CUI::CreateUIObj<CUIPanel>("PlyaerBackPanelRed", pLayer);
	pPlyaerBackPanelRed->SetTexture("PlyaerBackPanelRed", L"RedTeam.bmp", UI_PATH);
	pPlyaerBackPanelRed->SetColorKey(0, 0, 0);
	pPlyaerBackPanelRed->SetSize(160.f, 120.f);
	pPlyaerBackPanelRed->SetPos(WINDOWWIDTH - pPlyaerBackPanelRed->GetSize().x, 0.f);

	CUIPanel* pPlyaerBlueHPBack = CUI::CreateUIObj<CUIPanel>("PlyaerBlueHPBack", pLayer);
	pPlyaerBlueHPBack->SetTexture("PlyaerHPBack", L"HPBack.bmp", UI_PATH);
	pPlyaerBlueHPBack->SetColorKey(0, 0, 0);
	pPlyaerBlueHPBack->SetSize(483.f, 36.f);
	pPlyaerBlueHPBack->SetPos(104.f, 37.f);

	CUIPanel* pPlyaerBlueHP = CUI::CreateUIObj<CUIPanel>("PlyaerBlueHP", pLayer);
	pPlyaerBlueHP->SetTexture("PlyaerHP", L"HP.bmp", UI_PATH);
	pPlyaerBlueHP->SetColorKey(0, 0, 0);
	pPlyaerBlueHP->SetSize(483.f, 36.f);
	pPlyaerBlueHP->SetPos(103.f, 37.f);

	CUIPanel* pPlyaerRedHPBack = CUI::CreateUIObj<CUIPanel>("PlyaerRedHPBack", pLayer);
	pPlyaerRedHPBack->SetTexture("PlyaerHPBack", L"HPBack.bmp", UI_PATH);
	pPlyaerRedHPBack->SetColorKey(0, 0, 0);
	pPlyaerRedHPBack->SetSize(483.f, 36.f);
	pPlyaerRedHPBack->SetPos(WINDOWWIDTH - 60.f - pPlyaerRedHPBack->GetSize().x, 37.f);

	CUIPanel* pPlyaerRedHP = CUI::CreateUIObj<CUIPanel>("PlyaerRedHP", pLayer);
	pPlyaerRedHP->SetTexture("PlyaerHP", L"HP.bmp", UI_PATH);
	pPlyaerRedHP->SetColorKey(0, 0, 0);
	pPlyaerRedHP->SetSize(483.f, 36.f);
	pPlyaerRedHP->SetPos(WINDOWWIDTH - 60.f - pPlyaerRedHP->GetSize().x, 37.f);

	CUIPanel* pPlyaerBlueFace = CUI::CreateUIObj<CUIPanel>("PlyaerBlueFace", pLayer);
	pPlyaerBlueFace->SetTexture("PlyaerImage", L"PlayerImage.bmp", UI_PATH);
	pPlyaerBlueFace->SetImageOffset(123.f, 189.f);
	pPlyaerBlueFace->SetColorKey(89, 125, 216);
	pPlyaerBlueFace->SetSize(90.f, 90.f);
	pPlyaerBlueFace->SetPos(35, 10);

	CUIPanel* pPlyaerRedFace = CUI::CreateUIObj<CUIPanel>("PlyaerRedFace", pLayer);
	pPlyaerRedFace->SetTexture("PlyaerImage", L"PlayerImage.bmp", UI_PATH);
	pPlyaerRedFace->SetImageOffset(24.f, 192.f);
	pPlyaerRedFace->SetColorKey(89, 125, 216);
	pPlyaerRedFace->SetSize(90.f, 90.f);
	pPlyaerRedFace->SetPos(WINDOWWIDTH - 120, 13);

	return true;
}
