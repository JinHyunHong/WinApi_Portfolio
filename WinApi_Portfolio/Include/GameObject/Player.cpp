#include "Player.h"
#include "../Logic/InputManager.h"
#include "../Collider/ColliderRect.h"
#include "../Animation/Animation.h"

CPlayer::CPlayer()	:
	fHP(100.f)
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
	pRC->SetInfo(-35.f, -35.f, 35.f, 35.f);

	CreateAnimation("Player");

	vector<wstring> vecFileName;

	for (int i = 0; i <= 5; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Benimaru_Nikaido\\Player\\Idle\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip("Idle", AT_FRAME, AO_LOOP, 1.2f, 6, 1, 0, 0, 6, 1, 0.f, "PlayerIdle", vecFileName, CHARACTER_PATH);
	SetAnimationClipColorKey("Idle", 8, 16, 33);

	vecFileName.clear();

	for (int i = 1; i <= 5; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Benimaru_Nikaido\\Player\\Walk\\Front\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip("WalkFront", AT_FRAME, AO_ONCE_RETURN, 0.6f, 5, 1, 0, 0, 5, 1, 0.f, "PlayerWalkFront", vecFileName, CHARACTER_PATH);
	SetAnimationClipColorKey("WalkFront", 8, 16, 33);

	vecFileName.clear();

	for (int i = 0; i <= 5; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Benimaru_Nikaido\\Player\\Walk\\Back\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip("WalkBack", AT_FRAME, AO_ONCE_RETURN, 0.6f, 6, 1, 0, 0, 6, 1, 0.f, "PlayerWalkBack", vecFileName, CHARACTER_PATH);
	SetAnimationClipColorKey("WalkBack", 8, 16, 33);


	return true;
}

void CPlayer::Input(float fDeltaTime)
{
	CMoveObj::Input(fDeltaTime);

	if (KEYPRESS("MoveLeft"))
	{
		m_eDir = DIR_BACK;
		MoveToXSpeed(fDeltaTime);
		m_pAnimation->ChangeClip("WalkBack");
		m_pAnimation->SetDefaultClip("Idle");
	}


	if (KEYPRESS("MoveRight"))
	{
		m_eDir = DIR_FRONT;
		MoveToXSpeed(fDeltaTime);
		m_pAnimation->ChangeClip("WalkFront");
		m_pAnimation->SetDefaultClip("Idle");
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
