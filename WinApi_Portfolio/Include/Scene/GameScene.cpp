#include "GameScene.h"
#include "../GameObject/GameObj.h"
#include "../GameObject/Player.h"
#include "../GameObject/Enemy.h"
#include "../UI/UI.h"
#include "../UI/UIPanel.h"
#include "../Logic/Camera.h"
#include "../Logic/Logic.h"
#include "../Collider/ColliderRect.h"

CGameScene::CGameScene()	:
	m_iSecondLimit(60),
	m_iSecond(0),
	m_fDeltaSumTime(0.f),
	m_pPlayer(NULL),
	m_pEnemy(NULL),
	m_pPlayerBlueHP(NULL),
	m_pPlayerRedHP(NULL)
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
	m_pPlayer = CGameObj::CreateGameObj<CPlayer>("PlayerObj", pLayer);
	GET_SINGLE(CCamera)->SetTarget(m_pPlayer);

	m_pEnemy = CGameObj::CreateGameObj<CEnemy>("EnemyObj", pLayer);

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
	CColliderRect* pRC = pUIPanel->AddCollider<CColliderRect>("Stage");
	pRC->SetInfo(0, 620, WORLDWIDTH, 690);

	CUIPanel* pPlayerBackPanelBlue = CUI::CreateUIObj<CUIPanel>("PlyaerBackPanelBlue", pLayer);
	pPlayerBackPanelBlue->SetTexture("PlyaerBackPanelBlue", L"BlueTeam.bmp", UI_PATH);
	pPlayerBackPanelBlue->SetColorKey(0, 0, 0);
	pPlayerBackPanelBlue->SetPos(0.f, 0.f);
	pPlayerBackPanelBlue->SetSize(160.f, 120.f);

	CUIPanel* pPlayerBackPanelRed = CUI::CreateUIObj<CUIPanel>("PlyaerBackPanelRed", pLayer);
	pPlayerBackPanelRed->SetTexture("PlyaerBackPanelRed", L"RedTeam.bmp", UI_PATH);
	pPlayerBackPanelRed->SetColorKey(0, 0, 0);
	pPlayerBackPanelRed->SetSize(160.f, 120.f);
	pPlayerBackPanelRed->SetPos(WINDOWWIDTH - pPlayerBackPanelRed->GetSize().x, 0.f);

	CUIPanel* pPlyaerBlueHPBack = CUI::CreateUIObj<CUIPanel>("PlyaerBlueHPBack", pLayer);
	pPlyaerBlueHPBack->SetTexture("PlyaerHPBack", L"HPBack.bmp", UI_PATH);
	pPlyaerBlueHPBack->SetColorKey(0, 0, 0);
	pPlyaerBlueHPBack->SetSize(401.f, 36.f);
	pPlyaerBlueHPBack->SetPos(104.f, 37.f);
	pPlyaerBlueHPBack->AddUIText("CHALLENGER !", 0.f, -15.f, "KOFMainFont23", 43, 74, 225);
	pPlyaerBlueHPBack->AddUIText("BENIMARU N.", 30.f, 30.f, "KOFMainFont17", 43, 74, 225, TRANSPARENT, DT_LEFT);

	m_pPlayerBlueHP = CUI::CreateUIObj<CUIPanel>("PlyaerBlueHP", pLayer);
	m_pPlayerBlueHP->SetTexture("PlyaerHP", L"HP.bmp", UI_PATH);
	m_pPlayerBlueHP->SetColorKey(0, 0, 0);
	m_pPlayerBlueHP->SetSize(369.f, 15.f);
	m_pPlayerBlueHP->SetPos(120.f, 45.f);

	CUIPanel* pPlayerRedHPBack = CUI::CreateUIObj<CUIPanel>("PlyaerRedHPBack", pLayer);
	pPlayerRedHPBack->SetTexture("PlyaerHPBack", L"HPBack.bmp", UI_PATH);
	pPlayerRedHPBack->SetColorKey(0, 0, 0);
	pPlayerRedHPBack->SetSize(401.f, 36.f);
	pPlayerRedHPBack->SetPos(WINDOWWIDTH - pPlayerRedHPBack->GetSize().x - 90.f, 37.f);
	pPlayerRedHPBack->AddUIText("CHALLENGER !", 0.f, -15.f, "KOFMainFont23", 209, 27, 58);
	pPlayerRedHPBack->AddUIText("KYO", -30.f, 30.f, "KOFMainFont17", 209, 27, 58, TRANSPARENT, DT_RIGHT);

	m_pPlayerRedHP = CUI::CreateUIObj<CUIPanel>("PlyaerRedHP", pLayer);
	m_pPlayerRedHP->SetTexture("PlyaerHP", L"HP.bmp", UI_PATH);
	m_pPlayerRedHP->SetColorKey(0, 0, 0);
	m_pPlayerRedHP->SetSize(369.f, 15.f);
	m_pPlayerRedHP->SetPos(WINDOWWIDTH - m_pPlayerRedHP->GetSize().x - 105.f, 45.f);

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
			// 시간초가 다 될 경우
			m_pTimerPanel[0]->SetImageOffset(13.f, 49.f);
			m_pTimerPanel[1]->SetImageOffset(13.f, 49.f);

			if (m_pPlayer->GetHP() > m_pEnemy->GetHP())
			{
				MessageBoxA(WINDOWHANDLE, "YOU WIN!", "YOU WIN!", MB_OK);
				GAMEEND;
			}

			else if (m_pPlayer->GetHP() == m_pEnemy->GetHP())
			{
				MessageBoxA(WINDOWHANDLE, "DRAW!", "DRAW!", MB_OK);
				GAMEEND;
			}

			else
			{
				MessageBoxA(WINDOWHANDLE, "YOU LOSE!", "YOU LOSE!", MB_OK);
				GAMEEND;
			}
		}
	}


	if (m_pPlayer)
	{
		float fPlayerHP = m_pPlayer->GetHP();

		if (m_pPlayerBlueHP)
		{
			_SIZE tSize = { 369.f, 15.f };

			float fPer = tSize.x / 100.f;

			m_pPlayerBlueHP->SetSize(fPer * fPlayerHP, tSize.y);
		}
	}


	if (m_pEnemy)
	{
		float fEnemyHP = m_pEnemy->GetHP();

		if (m_pPlayerRedHP)
		{
			_SIZE tOriginSize = { 369.f, 15.f };

			POSITION tOriginPos = { WINDOWWIDTH - 459.f, 45.f };
			float fPer = tOriginSize.x / 100.f;

			float f = fPer * fEnemyHP;

			float fOffsetX = tOriginPos.x + tOriginSize.x - f - 15.f;

			m_pPlayerRedHP->SetSize(f, tOriginSize.y);
			m_pPlayerRedHP->SetPos(fOffsetX, tOriginPos.y);

		}
	}

	if (m_pPlayer && m_pEnemy)
	{
		float fPlayerHP = m_pPlayer->GetHP();
		float fEnemyHP = m_pEnemy->GetHP();

		if (fPlayerHP == 0 && fEnemyHP == 0)
		{
			MessageBoxA(WINDOWHANDLE, "DRAW!", "DRAW!", MB_OK);
			GAMEEND;
		}

		else if (fPlayerHP == 0)
		{
			MessageBoxA(WINDOWHANDLE, "YOU LOSE!", "YOU LOSE!", MB_OK);
			GAMEEND;
		}

		else if (fEnemyHP == 0)
		{
			MessageBoxA(WINDOWHANDLE, "YOU WIN!", "YOU WIN!", MB_OK);
			GAMEEND;
		}
	}



	return 0;
}
