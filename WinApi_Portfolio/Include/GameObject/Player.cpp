#include "Player.h"
#include "../Logic/InputManager.h"

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
	SetSpeed(400.f);
	return true;
}

void CPlayer::Input(float fDeltaTime)
{
	CMoveObj::Input(fDeltaTime);

	if (KEYPRESS("MoveLeft"))
	{
		m_eDir = DIR_BACK;
		MoveToXSpeed(fDeltaTime);
	}

	if (KEYPRESS("MoveRight"))
	{
		m_eDir = DIR_FRONT;
		MoveToXSpeed(fDeltaTime);
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
