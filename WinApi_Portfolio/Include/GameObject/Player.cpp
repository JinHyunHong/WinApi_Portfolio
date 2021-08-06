#include "Player.h"
#include "../Logic/InputManager.h"
#include "../Collider/ColliderRect.h"
#include "../Animation/Animation.h"

CPlayer::CPlayer() :
	m_fHP(0.f)
{
}

CPlayer::CPlayer(const CPlayer& player)	:
	CMoveObj(player)
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
	SetPos(50.f, 500.f);
	SetSpeed(400.f);
	SetSize(166.f, 291.f);
	SetPivot(0.5f, 0.5f);
	SetImageOffset(0.f, 0.f);

	CColliderRect* pRC = AddCollider<CColliderRect>("Default");
	pRC->SetInfo(-m_tSize.x / 2, -m_tSize.y / 2, m_tSize.x / 2, m_tSize.y / 2);

	CreateAnimation("Player");

	vector<wstring> vecFileName;

	for (int i = 0; i <= 5; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Left\\Idle\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip("LeftIdle", AT_FRAME, AO_LOOP, 1.2f, 6, 1, 0, 0, 6, 1, 0.f, "PlayerLeftIdle", vecFileName, BENIMARU_PATH);
	SetAnimationClipColorKey("LeftIdle", 8, 16, 33);

	vecFileName.clear();

	for (int i = 1; i <= 5; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Left\\Walk\\Front\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip("LeftWalkFront", AT_FRAME, AO_ONCE_RETURN, 0.6f, 5, 1, 0, 0, 5, 1, 0.f, "PlayerLeftWalkFront", vecFileName, BENIMARU_PATH);
	SetAnimationClipColorKey("LeftWalkFront", 8, 16, 33);

	vecFileName.clear();

	for (int i = 0; i <= 5; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Left\\Walk\\Back\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip("LeftWalkBack", AT_FRAME, AO_ONCE_RETURN, 0.6f, 6, 1, 0, 0, 6, 1, 0.f, "PlayerLeftWalkBack", vecFileName, BENIMARU_PATH);
	SetAnimationClipColorKey("LeftWalkBack", 8, 16, 33);


	return true;
}

void CPlayer::Input(float fDeltaTime)
{
	CMoveObj::Input(fDeltaTime);

	if (KEYPRESS("MoveLeft"))
	{
		m_eDir = DIR_LEFT;
		MoveToXSpeed(fDeltaTime);
		m_pAnimation->ChangeClip("LeftWalkBack");
		m_pAnimation->SetDefaultClip("LeftIdle");
	}

	if (KEYUP("MoveLeft"))
	{
		m_pAnimation->SetDefaultClip("LeftIdle");
	}


	if (KEYPRESS("MoveRight"))
	{
		m_eDir = DIR_RIGHT;
		MoveToXSpeed(fDeltaTime);
		m_pAnimation->ChangeClip("LeftWalkFront");
		m_pAnimation->SetDefaultClip("LeftIdle");
	}

	if (KEYUP("MoveRight"))
	{
		m_pAnimation->SetDefaultClip("LeftIdle");
	}
}

int CPlayer::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);
	return 0;
}

void CPlayer::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
}

int CPlayer::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;
}

void CPlayer::Render(HDC hDC, float fDeltaTime)
{
	CMoveObj::Render(hDC, fDeltaTime);
}
