#include "GameScene.h"
#include "../GameObject/GameObj.h"
#include "../GameObject/Player.h"
#include "../GameObject/Enemy.h"
#include "../UI/UI.h"
#include "../UI/UIPanel.h"
#include "../Logic/Camera.h"
#include "../Logic/Logic.h"

CGameScene::CGameScene()	:
	m_iSecondLimit(60),
	m_iSecond(0),
	m_fDeltaSumTime(0.f)
{
}

CGameScene::~CGameScene()
{
}

bool CGameScene::Init()
{
	CScene::Init();

	m_iSecond = m_iSecondLimit;

	CLayer* pLayer = FindLayer("GameObject");
	CPlayer* pObj = CGameObj::CreateGameObj<CPlayer>("PlayerObj", pLayer);
	GET_SINGLE(CCamera)->SetTarget(pObj);

	CEnemy* pEnemy = CGameObj::CreateGameObj<CEnemy>("EnemyObj", pLayer);

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
	pPlyaerBlueHPBack->AddUIText("CHALLENGER !", -30.f, -15.f, "KOFMainFont23", 43, 74, 225);
	pPlyaerBlueHPBack->AddUIText("BENIMARU N.", 30.f, 30.f, "KOFMainFont17", 43, 74, 225, TRANSPARENT, DT_LEFT);

	CUIPanel* pPlyaerBlueHP = CUI::CreateUIObj<CUIPanel>("PlyaerBlueHP", pLayer);
	pPlyaerBlueHP->SetTexture("PlyaerHP", L"HP.bmp", UI_PATH);
	pPlyaerBlueHP->SetColorKey(0, 0, 0);
	pPlyaerBlueHP->SetSize(483.f, 36.f);
	pPlyaerBlueHP->SetPos(103.f, 37.f);

	CUIPanel* pPlyaerRedHPBack = CUI::CreateUIObj<CUIPanel>("PlyaerRedHPBack", pLayer);
	pPlyaerRedHPBack->SetTexture("PlyaerHPBack", L"HPBack.bmp", UI_PATH);
	pPlyaerRedHPBack->SetColorKey(0, 0, 0);
	pPlyaerRedHPBack->SetSize(483.f, 36.f);
	pPlyaerRedHPBack->SetPos(WINDOWWIDTH - 20.f - pPlyaerRedHPBack->GetSize().x, 37.f);
	pPlyaerRedHPBack->AddUIText("CHALLENGER !", -30.f, -15.f, "KOFMainFont23", 209, 27, 58);
	pPlyaerRedHPBack->AddUIText("KYO", -110.f, 30.f, "KOFMainFont17", 209, 27, 58, TRANSPARENT, DT_RIGHT);

	CUIPanel* pPlyaerRedHP = CUI::CreateUIObj<CUIPanel>("PlyaerRedHP", pLayer);
	pPlyaerRedHP->SetTexture("PlyaerHP", L"HP.bmp", UI_PATH);
	pPlyaerRedHP->SetColorKey(0, 0, 0);
	pPlyaerRedHP->SetSize(483.f, 36.f);
	pPlyaerRedHP->SetPos(WINDOWWIDTH - 20.f - pPlyaerRedHP->GetSize().x, 37.f);

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

	CUIPanel* pPlyaerGuageBackBar = CUI::CreateUIObj<CUIPanel>("PlyaerGuageBackBar", pLayer);
	pPlyaerGuageBackBar->SetTexture("PlyaerGuageBackBar", L"PlayerGuageBackBar.bmp", UI_PATH);
	pPlyaerGuageBackBar->SetSize(247.f, 30.f);
	pPlyaerGuageBackBar->SetPos(30.f, WINDOWHEIGHT - pPlyaerGuageBackBar->GetSize().y - 20);

	CUIPanel* pEnemyGuageBackBar = CUI::CreateUIObj<CUIPanel>("EnemyGuageBackBar", pLayer);
	pEnemyGuageBackBar->SetTexture("EnemyGuageBackBar", L"EnemyGuageBackBar.bmp", UI_PATH);
	pEnemyGuageBackBar->SetSize(266.f, 34.f);
	pEnemyGuageBackBar->SetPos(WINDOWWIDTH - pEnemyGuageBackBar->GetSize().x - 30, 
		WINDOWHEIGHT - pPlyaerGuageBackBar->GetSize().y - 20);

	m_pTimerPanel[0] = CUI::CreateUIObj<CUIPanel>("TimerLeft", pLayer);
	m_pTimerPanel[0]->SetTexture("Timer", L"Timer.bmp", UI_PATH);
	m_pTimerPanel[0]->SetImageOffset(251.f, 49.f);
	m_pTimerPanel[0]->SetColorKey(200, 191, 231);
	m_pTimerPanel[0]->SetSize(39.f, 65.f);
	m_pTimerPanel[0]->SetPos(WINDOWWIDTH / 2 - 30, 23);

	m_pTimerPanel[1] = CUI::CreateUIObj<CUIPanel>("TimerRight", pLayer);
	m_pTimerPanel[1]->SetTexture("Timer", L"Timer.bmp", UI_PATH);
	m_pTimerPanel[1]->SetImageOffset(13.f, 49.f);
	m_pTimerPanel[1]->SetColorKey(200, 191, 231);
	m_pTimerPanel[1]->SetSize(39.f, 65.f);
	m_pTimerPanel[1]->SetPos(WINDOWWIDTH / 2 + 10, 23);

	return true;
}

int CGameScene::Update(float fDeltaTime)
{
	CScene::Update(fDeltaTime);

	m_fDeltaSumTime += fDeltaTime;


	if (m_fDeltaSumTime >= 1)
	{
		m_fDeltaSumTime -= 1;

		if (!m_iSecond == 0)
		{
			--m_iSecond;

			int iShare = m_iSecond / 10;
			int iRemain = m_iSecond % 10;


			m_pTimerPanel[0]->SetImageOffset(13.f + m_pTimerPanel[0]->GetSize().x * iShare, 49.f);
			m_pTimerPanel[1]->SetImageOffset(13.f + m_pTimerPanel[1]->GetSize().x * iRemain, 49.f);
		}

		else
		{
			m_pTimerPanel[0]->SetImageOffset(13.f, 49.f);
			m_pTimerPanel[1]->SetImageOffset(13.f, 49.f);
		}
	}



	return 0;
}
