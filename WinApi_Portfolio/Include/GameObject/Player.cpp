#include "Player.h"
#include "../Logic/InputManager.h"
#include "../Collider/ColliderRect.h"
#include "../Animation/Animation.h"
#include "../Logic/Logic.h"
#include "../Logic/ResourcesManager.h"

CPlayer::CPlayer() :
	m_fHP(0.f),
	m_bSit(false)
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
	SetPos(50.f, 480.f);
	SetSpeed(400.f);
	SetSize(166.f, 291.f);
	SetPivot(0.5f, 0.5f);
	SetImageOffset(0.f, 0.f);

	m_eDir = DIR_FRONT;
	m_eCharacterDir = CD_RIGHT;

	CColliderRect* pRC = AddCollider<CColliderRect>("PlayerBody");
	pRC->SetInfo(-m_tSize.x / 2, -m_tSize.y / 2, m_tSize.x / 2, m_tSize.y / 2);

	m_pAnimation = GET_SINGLE(CResourcesManager)->GetAnimation(WCT_BENIMARU)->Clone();
	m_pAnimation->SetObj(this);
	m_pAnimation->SetCurrentClip("LeftIdle");



	return true;
}

void CPlayer::Input(float fDeltaTime)
{
	CMoveObj::Input(fDeltaTime);

	POSITION tPos = m_tPos - m_tSize * m_tPivot;

	if (tPos.x >= WORLDWIDTH - m_tSize.x - 20)
	{
		m_eCharacterDir = CD_RIGHT;
	}

	else if (tPos.x <= 20)
	{
		m_eCharacterDir = CD_LEFT;
	}

	if (!m_bSit)
	{
		if (KEYPRESS("MoveLeft") && !(tPos.x <= 0))
		{
			m_eDir = DIR_BACK;

			if (m_eCharacterDir == CD_RIGHT)
			{
				MoveToXSpeed(fDeltaTime);
				m_pAnimation->ChangeClip("RightWalkBack");
				m_pAnimation->SetDefaultClip("RightIdle");
			}

			else if (m_eCharacterDir == CD_LEFT)
			{
				MoveToXSpeed(fDeltaTime);
				m_pAnimation->ChangeClip("LeftWalkBack");
				m_pAnimation->SetDefaultClip("LeftIdle");
			}

		}

		if (KEYUP("MoveLeft"))
		{
			if (m_eCharacterDir == CD_RIGHT)
			{
				m_pAnimation->SetDefaultClip("RightIdle");
			}
			else if (m_eCharacterDir == CD_LEFT)
			{
				m_pAnimation->SetDefaultClip("LeftIdle");
			}
		}



		if (KEYPRESS("MoveRight") && !(tPos.x >= WORLDWIDTH - m_tSize.x))
		{
			m_eDir = DIR_FRONT;

			if (m_eCharacterDir == CD_RIGHT)
			{
				MoveToXSpeed(fDeltaTime);
				m_pAnimation->ChangeClip("RightWalkFront");
				m_pAnimation->SetDefaultClip("RightIdle");
			}

			else if (m_eCharacterDir == CD_LEFT)
			{
				MoveToXSpeed(fDeltaTime);
				m_pAnimation->ChangeClip("LeftWalkFront");
				m_pAnimation->SetDefaultClip("LeftIdle");
			}
		}

		if (KEYUP("MoveRight"))
		{
			if (m_eCharacterDir == CD_RIGHT)
			{
				m_pAnimation->SetDefaultClip("RightIdle");
			}
			else if (m_eCharacterDir == CD_LEFT)
			{
				m_pAnimation->SetDefaultClip("LeftIdle");
			}
		}

		if (KEYDOWN("Attack1"))
		{
			if (m_eCharacterDir == CD_RIGHT)
			{
				MoveToXSpeed(fDeltaTime);
				m_pAnimation->ChangeClip("RightAttack1");
				m_pAnimation->SetDefaultClip("RightIdle");
			}

			else if (m_eCharacterDir == CD_LEFT)
			{
				MoveToXSpeed(fDeltaTime);
				m_pAnimation->ChangeClip("LeftAttack1");
				m_pAnimation->SetDefaultClip("LeftIdle");
			}
		}

		if (KEYDOWN("Attack2"))
		{
			if (m_eCharacterDir == CD_RIGHT)
			{
				MoveToXSpeed(fDeltaTime);
				m_pAnimation->ChangeClip("RightAttack2");
				m_pAnimation->SetDefaultClip("RightIdle");
			}

			else if (m_eCharacterDir == CD_LEFT)
			{
				MoveToXSpeed(fDeltaTime);
				m_pAnimation->ChangeClip("LeftAttack2");
				m_pAnimation->SetDefaultClip("LeftIdle");
			}
		}

		if (KEYDOWN("Attack3"))
		{
			if (m_eCharacterDir == CD_RIGHT)
			{
				MoveToXSpeed(fDeltaTime);
				m_pAnimation->ChangeClip("RightAttack3");
				m_pAnimation->SetDefaultClip("RightIdle");
			}

			else if (m_eCharacterDir == CD_LEFT)
			{
				MoveToXSpeed(fDeltaTime);
				m_pAnimation->ChangeClip("LeftAttack3");
				m_pAnimation->SetDefaultClip("LeftIdle");
			}
		}

		if (KEYDOWN("Attack4"))
		{
			if (m_eCharacterDir == CD_RIGHT)
			{
				MoveToXSpeed(fDeltaTime);
				m_pAnimation->ChangeClip("RightAttack4");
				m_pAnimation->SetDefaultClip("RightIdle");
			}

			else if (m_eCharacterDir == CD_LEFT)
			{
				MoveToXSpeed(fDeltaTime);
				m_pAnimation->ChangeClip("LeftAttack4");
				m_pAnimation->SetDefaultClip("LeftIdle");
			}
		}
	}

	if (KEYDOWN("SitAttack2"))
	{
		m_bSit = true;

		if (m_eCharacterDir == CD_RIGHT)
		{
			m_pAnimation->ChangeClip("RightSitAttack2");
			m_pAnimation->SetDefaultClip("RightSit");
		}
		else if (m_eCharacterDir == CD_LEFT)
		{
			m_pAnimation->ChangeClip("LeftSitAttack2");
			m_pAnimation->SetDefaultClip("LeftSit");
		}
	}


	if (KEYPRESS("Sit"))
	{
		m_bSit = true;
		if (m_eCharacterDir == CD_RIGHT)
		{
			m_pAnimation->ChangeClip("RightSit");
			m_pAnimation->SetDefaultClip("RightSit");
		}
		else if (m_eCharacterDir == CD_LEFT)
		{
			m_pAnimation->ChangeClip("LeftSit");
			m_pAnimation->SetDefaultClip("LeftSit");
		}
	}




	if (KEYUP("Sit"))
	{
		m_bSit = false;
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
