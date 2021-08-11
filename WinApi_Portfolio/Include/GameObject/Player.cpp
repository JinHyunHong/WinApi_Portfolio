#include "Player.h"
#include "../Logic/InputManager.h"
#include "../Collider/ColliderRect.h"
#include "../Animation/Animation.h"
#include "../Logic/Logic.h"
#include "../Logic/ResourcesManager.h"
#include "../Collider/ColliderSphere.h"

CPlayer::CPlayer() :
	m_fHP(0.f),
	m_bSit(false),
	m_bAttack(false)
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
	pRC->AddFunction(CS_ENTER, CPlayer::Hurt);

	CColliderSphere* pSR = AddCollider<CColliderSphere>("AttackColl");

	m_pAnimation = GET_SINGLE(CResourcesManager)->GetAnimation(RT_BENIMARU)->Clone();
	m_pAnimation->SetObj(this);
	m_pAnimation->SetCurrentClip("LeftIdle");


	return true;
}

void CPlayer::Input(float fDeltaTime)
{
	CMoveObj::Input(fDeltaTime);

	CColliderSphere* pSR = (CColliderSphere*)GetCollider("AttackColl");
	pSR->SetEnable(true);

	POSITION tPos = m_tPos - m_tSize * m_tPivot;

	if (tPos.x >= WORLDWIDTH - m_tSize.x - 20)
	{
		m_eCharacterDir = CD_RIGHT;
	}

	else if (tPos.x <= 20)
	{
		m_eCharacterDir = CD_LEFT;
	}
	
	
	if (!m_bAttack)
	{
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


			if (KEYDOWN("MovingLeft") && !(tPos.x <= 0))
			{
				m_eDir = DIR_BACK;

				if (m_eCharacterDir == CD_RIGHT)
				{
					MoveToXSpeed(fDeltaTime);
					m_pAnimation->SetDefaultClip("RightIdle");
				}

				else if (m_eCharacterDir == CD_LEFT)
				{
					MoveToX(-50.f);
					m_pAnimation->ChangeClip("LeftMovingBack");
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



			if (KEYDOWN("MovingRight") && !(tPos.x >= WORLDWIDTH - m_tSize.x))
			{
				m_eDir = DIR_FRONT;

				if (m_eCharacterDir == CD_RIGHT)
				{
					MoveToX(50.f);
					m_pAnimation->ChangeClip("RightMovingBack");
					m_pAnimation->SetDefaultClip("RightIdle");
				}

				else if (m_eCharacterDir == CD_LEFT)
				{
					MoveToXSpeed(fDeltaTime);
					m_pAnimation->SetDefaultClip("LeftIdle");
				}
			}

		}


		if (KEYDOWN("Attack1"))
		{
			m_bAttack = true;
			if (m_eCharacterDir == CD_RIGHT)
			{
				m_pAnimation->ChangeClip("RightAttack1");
				pSR->SetInfo(20.f, POSITION(-80, -80));
				m_pAnimation->SetDefaultClip("RightIdle");
			}

			else if (m_eCharacterDir == CD_LEFT)
			{
				m_pAnimation->ChangeClip("LeftAttack1");
				pSR->SetInfo(20.f, POSITION(80, -80));
				m_pAnimation->SetDefaultClip("LeftIdle");
			}
		}


		if (KEYDOWN("Attack2"))
		{
			m_bAttack = true;
			if (m_eCharacterDir == CD_RIGHT)
			{
				m_pAnimation->ChangeClip("RightAttack2");
				pSR->SetInfo(20.f, POSITION(-120, -80));
				m_pAnimation->SetDefaultClip("RightIdle");
			}

			else if (m_eCharacterDir == CD_LEFT)
			{
				m_pAnimation->ChangeClip("LeftAttack2");
				pSR->SetInfo(20.f, POSITION(120, -80));
				m_pAnimation->SetDefaultClip("LeftIdle");
			}
		}



		if (KEYDOWN("Attack3"))
		{
			m_bAttack = true;
			if (m_eCharacterDir == CD_RIGHT)
			{
				m_pAnimation->ChangeClip("RightAttack3");
				m_pAnimation->SetDefaultClip("RightIdle");
			}

			else if (m_eCharacterDir == CD_LEFT)
			{
				m_pAnimation->ChangeClip("LeftAttack3");
				m_pAnimation->SetDefaultClip("LeftIdle");
			}
		}



		if (KEYDOWN("Attack4"))
		{
			m_bAttack = true;
			if (m_eCharacterDir == CD_RIGHT)
			{
				m_pAnimation->ChangeClip("RightAttack4");
				m_pAnimation->SetDefaultClip("RightIdle");
			}

			else if (m_eCharacterDir == CD_LEFT)
			{
				m_pAnimation->ChangeClip("LeftAttack4");
				m_pAnimation->SetDefaultClip("LeftIdle");
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

		if (KEYDOWN("SitAttack1"))
		{
			m_bSit = true;
			m_bAttack = true;

			if (m_eCharacterDir == CD_RIGHT)
			{
				m_pAnimation->ChangeClip("RightSitAttack1");
			}
			else if (m_eCharacterDir == CD_LEFT)
			{
				m_pAnimation->ChangeClip("LeftSitAttack1");
			}
		}



		if (KEYDOWN("SitAttack2"))
		{
			m_bSit = true;
			m_bAttack = true;

			if (m_eCharacterDir == CD_RIGHT)
			{
				m_pAnimation->ChangeClip("RightSitAttack2");
			}
			else if (m_eCharacterDir == CD_LEFT)
			{
				m_pAnimation->ChangeClip("LeftSitAttack2");
			}
		}
	}

	if (KEYUP("Attack1"))
	{
		pSR->SetEnable(false);
		if (m_pAnimation->GetMotionEnd())
			m_bAttack = false;
	}

	if (KEYUP("Attack2"))
	{
		pSR->SetEnable(false);
		if (m_pAnimation->GetMotionEnd())
			m_bAttack = false;
	}

	if (KEYUP("Attack3"))
	{
		if (m_pAnimation->GetMotionEnd())
			m_bAttack = false;
	}

	if (KEYUP("Attack4"))
	{
		if (m_pAnimation->GetMotionEnd())
			m_bAttack = false;
	}

	if (KEYUP("SitAttack1"))
	{
		if (m_pAnimation->GetMotionEnd())
			m_bAttack = false;
	}

	if (KEYUP("SitAttack2"))
	{
		if (m_pAnimation->GetMotionEnd())
			m_bAttack = false;
	}

	if (KEYUP("Sit"))
	{
		m_bSit = false;

		if (m_eCharacterDir == CD_RIGHT)
		{
			m_pAnimation->SetDefaultClip("RightIdle");
		}
		else if (m_eCharacterDir == CD_LEFT)
		{
			m_pAnimation->SetDefaultClip("LeftIdle");
		}
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

void CPlayer::Hurt(CCollider* pCollSrc, CCollider* pCollDest, float fDeltaTime)
{
	CPlayer* pPlayer = (CPlayer*)pCollSrc->GetObj();

	if (pPlayer)
	{
		if (pPlayer->GetSit())
		{
			if (pPlayer->GetCharacterDir() == CD_RIGHT)
			{
				pPlayer->GetAnimation()->ChangeClip("RightSitHurt");
			}
			else if (pPlayer->GetCharacterDir() == CD_LEFT)
			{
				pPlayer->GetAnimation()->ChangeClip("LeftSitHurt");
			}
		}

		else
		{
			if (pPlayer->GetCharacterDir() == CD_RIGHT)
			{
				pPlayer->GetAnimation()->ChangeClip("RightUpHurt");
			}
			else if (pPlayer->GetCharacterDir() == CD_LEFT)
			{
				pPlayer->GetAnimation()->ChangeClip("LeftUpHurt");
			}
		}

	}



}
