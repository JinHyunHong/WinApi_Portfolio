#include "ResourcesManager.h"
#include "../Texture/Texture.h"
#include "FileManager.h"
#include "../Animation/Animation.h"

DEFINITION_SINGLE(CResourcesManager);

CResourcesManager::CResourcesManager()	:
	m_pBackBuffer(NULL),
	m_hInst(NULL),
	m_hDC(NULL)
{

}

CResourcesManager::~CResourcesManager()
{
	SAFE_RELEASE(m_pBackBuffer);
	Safe_Release_Map(m_mapTex);

	for (int i = 0; i < RT_END; ++i)
	{
		if (m_AnimationList[i])
		{
			SAFE_RELEASE(m_AnimationList[i]);
		}
	}
}


bool CResourcesManager::Init(HINSTANCE hInst, HDC hDC)
{
	m_hInst = hInst;
	m_hDC = hDC;

	m_pBackBuffer = LoadTexture("BackBuffer", L"BackBuffer.bmp");


	//===================================================
	// 폰트 리소스 추가하기
	string strPath = GET_SINGLE(CFileManager)->FindPathMultiByte(FONT_PATH);
	strPath += "Kemco Pixel Bold.ttf";
	AddFontResourceA(strPath.c_str());

	AddFont("KOFMainFont17", 15, 17, 0, 0, 0, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, "Kemco Pixel");
	AddFont("KOFMainFont23", 21, 23, 0, 0, 0, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, "Kemco Pixel");

	//===================================================
	// 캐릭터 애니메이션 리소스 추가하기
	CreateAnimation(RT_EFFECT);
	CreateAnimation(RT_BENIMARU);
	CreateAnimation(RT_KYO);

	//===================================================
	// EFFECT
	vector<wstring> vecFileName;

	for (int i = 0; i <= 10; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Small\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_EFFECT, "SmallHurtEffect", AT_FRAME, AO_ONCE_RETURN, 0.8f, 11, 1, 0, 0, 11, 1, 0.f, "SmallHurtEffect", vecFileName, EFFECT_PATH);
	SetAniamtionColorKey(RT_EFFECT, "SmallHurtEffect", 255, 255, 255);

	vecFileName.clear();

	for (int i = 0; i <= 9; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Medium\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_EFFECT, "MediumHurtEffect", AT_FRAME, AO_ONCE_RETURN, 0.5f, 10, 1, 0, 0, 10, 1, 0.f, "MediumHurtEffect", vecFileName, EFFECT_PATH);
	SetAniamtionColorKey(RT_EFFECT, "MediumHurtEffect", 255, 255, 255);
	
	vecFileName.clear();

	for (int i = 0; i <= 14; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Big\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_EFFECT, "BigHurtEffect", AT_FRAME, AO_ONCE_RETURN, 0.5f, 15, 1, 0, 0, 15, 1, 0.f, "BigHurtEffect", vecFileName, EFFECT_PATH);
	SetAniamtionColorKey(RT_EFFECT, "BigHurtEffect", 255, 255, 255);

	vecFileName.clear();

	//===================================================
	// BENIMARU LEFT

	for (int i = 0; i <= 5; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Left\\Idle\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_BENIMARU, "LeftIdle", AT_FRAME, AO_LOOP, 1.2f, 6, 1, 0, 0, 6, 1, 0.f, "PlayerLeftIdle", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "LeftIdle", 8, 16, 33);

	vecFileName.clear();

	for (int i = 0; i <= 1; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Left\\Jump\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_BENIMARU, "LeftJump", AT_FRAME, AO_LOOP, 1.f, 2, 1, 0, 0, 2, 1, 0.f, "PlayerLeftJump", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "LeftJump", 8, 16, 33);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Left\\Jump\\Moving\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_BENIMARU, "LeftMovingJump", AT_FRAME, AO_LOOP, 1.f, 4, 1, 0, 0, 4, 1, 0.f, "PlayerLeftMovingJump", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "LeftMovingJump", 8, 16, 33);

	vecFileName.clear();

	for (int i = 1; i <= 5; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Left\\Walk\\Front\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_BENIMARU, "LeftWalkFront", AT_FRAME, AO_ONCE_RETURN, 0.6f, 5, 1, 0, 0, 5, 1, 0.f, "PlayerLeftWalkFront", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "LeftWalkFront", 8, 16, 33);

	vecFileName.clear();

	for (int i = 0; i <= 5; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Left\\Walk\\Back\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_BENIMARU, "LeftWalkBack", AT_FRAME, AO_ONCE_RETURN, 0.6f, 6, 1, 0, 0, 6, 1, 0.f, "PlayerLeftWalkBack", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "LeftWalkBack", 8, 16, 33);

	vecFileName.clear();

	wchar_t strFileName[MAX_PATH] = {};
	wsprintf(strFileName, L"Left\\Sit\\%d.bmp", 0);
	vecFileName.push_back(strFileName);

	AddAnimationClip(RT_BENIMARU, "LeftSit", AT_FRAME, AO_ONCE_RETURN, 0.05f, 1, 1, 0, 0, 1, 1, 0.f, "PlayerLeftSit", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "LeftSit", 8, 16, 33);

	vecFileName.clear();

	memset(strFileName, 0, sizeof(wchar_t)* MAX_PATH);
	wsprintf(strFileName, L"Left\\Moving\\Back\\%d.bmp", 0);
	vecFileName.push_back(strFileName);

	AddAnimationClip(RT_BENIMARU, "LeftMovingBack", AT_FRAME, AO_ONCE_RETURN, 0.05f, 1, 1, 0, 0, 1, 1, 0.f, "PlayerLeftMovingBack", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "LeftMovingBack", 8, 16, 33);

	vecFileName.clear();

	for (int i = 0; i <= 1; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Left\\Attack\\Punch\\Punch\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_BENIMARU, "LeftAttack1", AT_FRAME, AO_ONCE_RETURN, 0.3f, 2, 1, 0, 0, 2, 1, 0.f, "PlayerLeftAttack1", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "LeftAttack1", 8, 16, 33);


	vecFileName.clear();

	for (int i = 0; i <= 1; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Left\\Attack\\Kick\\NearKick\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_BENIMARU, "LeftAttack2", AT_FRAME, AO_ONCE_RETURN, 0.3f, 2, 1, 0, 0, 2, 1, 0.f, "PlayerLeftAttack2", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "LeftAttack2", 8, 16, 33);

	vecFileName.clear();

	for (int i = 0; i <= 2; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Left\\Attack\\Punch\\PowerPunch\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_BENIMARU, "LeftAttack3", AT_FRAME, AO_ONCE_RETURN, 0.4f, 3, 1, 0, 0, 3, 1, 0.f, "PlayerLeftAttack3", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "LeftAttack3", 8, 16, 33);

	vecFileName.clear();

	for (int i = 0; i <= 2; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Left\\Attack\\Kick\\Kick\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_BENIMARU, "LeftAttack4", AT_FRAME, AO_ONCE_RETURN, 0.3f, 3, 1, 0, 0, 3, 1, 0.f, "PlayerLeftAttack4", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "LeftAttack4", 8, 16, 33);

	vecFileName.clear();

	for (int i = 0; i <= 2; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Left\\Attack\\Kick\\SitKick\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_BENIMARU, "LeftSitAttack1", AT_FRAME, AO_ONCE_RETURN, 0.3f, 3, 1, 0, 0, 3, 1, 0.f, "PlayeLeftSitAttack1", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "LeftSitAttack1", 8, 16, 33);

	vecFileName.clear();

	for (int i = 0; i <= 2; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Left\\Attack\\Punch\\SitPunch\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_BENIMARU, "LeftSitAttack2", AT_FRAME, AO_ONCE_RETURN, 0.4f, 3, 1, 0, 0, 3, 1, 0.f, "PlayeLeftSitAttack2", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "LeftSitAttack2", 8, 16, 33);

	vecFileName.clear();

	for (int i = 0; i <= 4; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Left\\Hurt\\UpHurt\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_BENIMARU, "LeftUpHurt", AT_FRAME, AO_ONCE_RETURN, 0.4f, 5, 1, 0, 0, 5, 1, 0.f, "PlayeLeftUpHurt", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "LeftUpHurt", 8, 16, 33);


	vecFileName.clear();

	for (int i = 0; i <= 2; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Left\\Hurt\\SitHurt\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_BENIMARU, "LeftSitHurt", AT_FRAME, AO_ONCE_RETURN, 0.2f, 3, 1, 0, 0, 3, 1, 0.f, "PlayeLeftSitHurt", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "LeftSitHurt", 8, 16, 33);


	vecFileName.clear();


	//===================================================
	// BENIMARU RIGHT

	for (int i = 0; i <= 5; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Right\\Idle\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_BENIMARU, "RightIdle", AT_FRAME, AO_LOOP, 1.2f, 6, 1, 0, 0, 6, 1, 0.f, "PlayerRightIdle", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "RightIdle", 8, 16, 33);

	vecFileName.clear();

	for (int i = 0; i <= 1; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Right\\Jump\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_BENIMARU, "RightJump", AT_FRAME, AO_LOOP, 1.f, 2, 1, 0, 0, 2, 1, 0.f, "PlayerJump", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "RightJump", 8, 16, 33);


	vecFileName.clear();

	for (int i = 1; i <= 5; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Right\\Walk\\Front\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_BENIMARU, "RightWalkFront", AT_FRAME, AO_ONCE_RETURN, 0.6f, 5, 1, 0, 0, 5, 1, 0.f, "PlayerRightWalkFront", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "RightWalkFront", 8, 16, 33);

	vecFileName.clear();

	for (int i = 0; i <= 5; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Right\\Walk\\Back\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_BENIMARU, "RightWalkBack", AT_FRAME, AO_ONCE_RETURN, 0.6f, 6, 1, 0, 0, 6, 1, 0.f, "PlayerRightWalkBack", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "RightWalkBack", 8, 16, 33);

	vecFileName.clear();

	memset(strFileName, 0, sizeof(wchar_t) * MAX_PATH);
	wsprintf(strFileName, L"Right\\Moving\\Back\\%d.bmp", 0);
	vecFileName.push_back(strFileName);

	AddAnimationClip(RT_BENIMARU, "RightMovingBack", AT_FRAME, AO_ONCE_RETURN, 0.05f, 1, 1, 0, 0, 1, 1, 0.f, "PlayerRightMovingBack", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "RightMovingBack", 8, 16, 33);

	vecFileName.clear();

	memset(strFileName, 0, sizeof(wchar_t) * MAX_PATH);
	wsprintf(strFileName, L"Right\\Sit\\%d.bmp", 0);
	vecFileName.push_back(strFileName);

	AddAnimationClip(RT_BENIMARU, "RightSit", AT_FRAME, AO_ONCE_RETURN, 0.05f, 1, 1, 0, 0, 1, 1, 0.f, "PlayerRightSit", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "RightSit", 8, 16, 33);

	vecFileName.clear();

	for (int i = 0; i <= 1; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Right\\Attack\\Punch\\Punch\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_BENIMARU, "RightAttack1", AT_FRAME, AO_ONCE_RETURN, 0.3f, 2, 1, 0, 0, 2, 1, 0.f, "PlayerRightAttack1", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "RightAttack1", 8, 16, 33);

	vecFileName.clear();

	for (int i = 0; i <= 1; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Right\\Attack\\Kick\\NearKick\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_BENIMARU, "RightAttack2", AT_FRAME, AO_ONCE_RETURN, 0.3f, 2, 1, 0, 0, 2, 1, 0.f, "PlayerRightAttack2", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "RightAttack2", 8, 16, 33);

	vecFileName.clear();

	for (int i = 0; i <= 2; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Right\\Attack\\Punch\\PowerPunch\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_BENIMARU, "RightAttack3", AT_FRAME, AO_ONCE_RETURN, 0.4f, 3, 1, 0, 0, 3, 1, 0.f, "PlayerRightAttack3", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "RightAttack3", 8, 16, 33);

	vecFileName.clear();

	for (int i = 0; i <= 2; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Right\\Attack\\Kick\\Kick\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_BENIMARU, "RightAttack4", AT_FRAME, AO_ONCE_RETURN, 0.3f, 3, 1, 0, 0, 3, 1, 0.f, "PlayeRightAttack4", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "RightAttack4", 8, 16, 33);

	vecFileName.clear();

	for (int i = 0; i <= 2; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Right\\Attack\\Kick\\SitKick\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_BENIMARU, "RightSitAttack1", AT_FRAME, AO_ONCE_RETURN, 0.3f, 3, 1, 0, 0, 3, 1, 0.f, "PlayeRightSitAttack1", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "RightSitAttack1", 8, 16, 33);

	vecFileName.clear();

	for (int i = 0; i <= 2; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Right\\Attack\\Punch\\SitPunch\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_BENIMARU, "RightSitAttack2", AT_FRAME, AO_ONCE_RETURN, 0.4f, 3, 1, 0, 0, 3, 1, 0.f, "PlayeRightSitAttack2", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "RightSitAttack2", 8, 16, 33);

	vecFileName.clear();

	for (int i = 0; i <= 4; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Right\\Hurt\\UpHurt\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_BENIMARU, "RightUpHurt", AT_FRAME, AO_ONCE_RETURN, 0.4f, 5, 1, 0, 0, 5, 1, 0.f, "PlayeRightUpHurt", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "RightUpHurt", 8, 16, 33);


	vecFileName.clear();

	for (int i = 0; i <= 2; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Right\\Hurt\\SitHurt\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_BENIMARU, "RightSitHurt", AT_FRAME, AO_ONCE_RETURN, 0.2f, 3, 1, 0, 0, 3, 1, 0.f, "PlayeRightSitHurt", vecFileName, BENIMARU_PATH);
	SetAniamtionColorKey(RT_BENIMARU, "RightSitHurt", 8, 16, 33);


	vecFileName.clear();





	//===================================================
	// KYO

	for (int i = 0; i <= 5; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Right\\Idle\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_KYO, "RightIdle", AT_FRAME, AO_LOOP, 1.2f, 6, 1, 0, 0, 6, 1, 0.f, "EnemyRightIdle", vecFileName, KYO_PATH);
	SetAniamtionColorKey(RT_KYO, "RightIdle", 8, 8, 66);

	vecFileName.clear();

	for (int i = 0; i <= 2; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Right\\Walk\\Front\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_KYO, "RightWalkFront", AT_FRAME, AO_ONCE_RETURN, 0.3f, 3, 1, 0, 0, 3, 1, 0.f, "EnemyRightWalkFront", vecFileName, KYO_PATH);
	SetAniamtionColorKey(RT_KYO, "RightWalkFront", 8, 8, 66);

	vecFileName.clear();

	for (int i = 0; i <= 2; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Right\\Hurt\\UpHurt\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_KYO, "RightUpHurt", AT_FRAME, AO_ONCE_RETURN, 0.3f, 3, 1, 0, 0, 3, 1, 0.f, "EnemyRightUpHurt", vecFileName, KYO_PATH);
	SetAniamtionColorKey(RT_KYO, "RightUpHurt", 8, 8, 66);

	vecFileName.clear();

	for (int i = 0; i <= 2; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Right\\Hurt\\SitHurt\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_KYO, "RightSitHurt", AT_FRAME, AO_ONCE_RETURN, 0.3f, 3, 1, 0, 0, 3, 1, 0.f, "EnemyRightSitHurt", vecFileName, KYO_PATH);
	SetAniamtionColorKey(RT_KYO, "RightSitHurt", 8, 8, 66);

	vecFileName.clear();

	for (int i = 0; i <= 5; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Left\\Idle\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_KYO, "LeftIdle", AT_FRAME, AO_LOOP, 1.2f, 6, 1, 0, 0, 6, 1, 0.f, "EnemyLeftIdle", vecFileName, KYO_PATH);
	SetAniamtionColorKey(RT_KYO, "LeftIdle", 8, 8, 66);

	vecFileName.clear();

	for (int i = 0; i <= 2; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Left\\Walk\\Front\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_KYO, "LeftWalkFront", AT_FRAME, AO_ONCE_RETURN, 0.3f, 3, 1, 0, 0, 3, 1, 0.f, "EnemyLeftWalkFront", vecFileName, KYO_PATH);
	SetAniamtionColorKey(RT_KYO, "LeftWalkFront", 8, 8, 66);

	vecFileName.clear();

	for (int i = 0; i <= 2; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Left\\Hurt\\UpHurt\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_KYO, "LeftUpHurt", AT_FRAME, AO_ONCE_RETURN, 0.3f, 3, 1, 0, 0, 3, 1, 0.f, "EnemyLeftUpHurt", vecFileName, KYO_PATH);
	SetAniamtionColorKey(RT_KYO, "LeftUpHurt", 8, 8, 66);

	vecFileName.clear();

	for (int i = 0; i <= 2; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Left\\Hurt\\SitHurt\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip(RT_KYO, "LeftSitHurt", AT_FRAME, AO_ONCE_RETURN, 0.3f, 3, 1, 0, 0, 3, 1, 0.f, "EnemyLeftSitHurt", vecFileName, KYO_PATH);
	SetAniamtionColorKey(RT_KYO, "LeftSitHurt", 8, 8, 66);

	vecFileName.clear();

	return true;
}

CTexture* CResourcesManager::GetBackBuffer() const
{
	m_pBackBuffer->AddRef();

	return m_pBackBuffer;
}

CTexture* CResourcesManager::LoadTexture(const string& strKey, const wchar_t* pFileName, const string& strPathKey)
{
	CTexture* pTex = FindTexture(strKey);

	if (!pTex)
	{
		pTex = new CTexture;
		if (!pTex->LoadTexture(m_hInst, m_hDC, pFileName, strPathKey))
		{
			SAFE_RELEASE(pTex);
			return NULL;
		}
		m_mapTex.insert(make_pair(strKey, pTex));
	}
	
	pTex->AddRef();

	return pTex;
}

CTexture* CResourcesManager::FindTexture(const string& strKey)
{
	unordered_map<string, CTexture*>::iterator iter = m_mapTex.find(strKey);

	if (iter == m_mapTex.end())
		return NULL;

	iter->second->AddRef();

	return iter->second;
}

bool CResourcesManager::EraseTexture(const string& strKey)
{
	CTexture* pTex = FindTexture(strKey);

	if (pTex)
	{
		SAFE_RELEASE(pTex);
		return true;
	}

	return false;

}

CAnimation* CResourcesManager::CreateAnimation(RESOURCES_TYPE eAnimationType)
{
	m_AnimationList[eAnimationType] = new CAnimation;

	if (!m_AnimationList[eAnimationType]->Init())
	{
		SAFE_RELEASE(m_AnimationList[eAnimationType]);
		return NULL;
	}

	return m_AnimationList[eAnimationType];
}

CAnimation* CResourcesManager::GetAnimation(RESOURCES_TYPE eAnimationType)
{
	if (!m_AnimationList[eAnimationType])
	{
		return NULL;
	}

	return m_AnimationList[eAnimationType];
}

bool CResourcesManager::AddAnimationClip(RESOURCES_TYPE eAnimationType, const string& strKey, ANIMATION_TYPE eType, 
	ANIMATION_OPTION eOption, float fAnimationLimitTime, int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY, 
	int iLengthX, int iLengthY, float fOptionLimitTime, const string& strTexKey, const wchar_t* pFileName, const string& strPathKey)
{
	if (!m_AnimationList[eAnimationType])
	{
		return false;
	}

	return m_AnimationList[eAnimationType]->AddClip(strKey, eType, eOption, fAnimationLimitTime, iFrameMaxX, iFrameMaxY, 
		iStartX, iStartY, iLengthX, iLengthY, fOptionLimitTime, strTexKey, pFileName, strPathKey);
}

bool CResourcesManager::AddAnimationClip(RESOURCES_TYPE eAnimationType, const string& strKey, ANIMATION_TYPE eType,
	ANIMATION_OPTION eOption, float fAnimationLimitTime, int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY, 
	int iLengthX, int iLengthY, float fOptionLimitTime, const string& strTexKey, const vector<wstring>& vecFileName, const string& strPathKey)
{
	if (!m_AnimationList[eType])
	{
		return false;
	}

	return m_AnimationList[eAnimationType]->AddClip(strKey, eType, eOption, fAnimationLimitTime, iFrameMaxX, iFrameMaxY,
		iStartX, iStartY, iLengthX, iLengthY, fOptionLimitTime, strTexKey, vecFileName, strPathKey);
}

bool CResourcesManager::SetAniamtionColorKey(RESOURCES_TYPE eAnimationType, const string& strClip, unsigned char r, unsigned char g, unsigned char b)
{
	if (!m_AnimationList[eAnimationType])
	{
		return false;
	}

	m_AnimationList[eAnimationType]->SetClipColorKey(strClip, r, g, b);
	return true;
}


HFONT CResourcesManager::FindFont(const string& strKey)
{
	unordered_map<string, HFONT>::iterator iter = m_mapFont.find(strKey);

	if (iter == m_mapFont.end())
		return NULL;

	return iter->second;
}

HFONT CResourcesManager::AddFont(const string& strKey, int iHeight, int iWidth, int iEscapement, int iOrientation, int iWeight,
	DWORD bItalic, DWORD bUnderline, DWORD bStrikeOut, DWORD lCharSet, DWORD lOutPrecision, DWORD lClipPrecision, DWORD lQuality,
	DWORD lPitchAndFamily, LPCSTR strFaceName)
{
	HFONT hFindFont;
	hFindFont = FindFont(strKey);
	if (hFindFont)
		return hFindFont;

	HFONT pFont = new HFONT__;

	pFont = CreateFontA(iHeight, iWidth, iEscapement, iOrientation, iWeight,
		bItalic, bUnderline, bStrikeOut, lCharSet, lOutPrecision, lClipPrecision, lQuality,
		lPitchAndFamily, strFaceName);

	m_mapFont.insert(make_pair(strKey, pFont));

	return pFont;
}
