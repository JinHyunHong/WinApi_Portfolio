#include "Player.h"
#include "../Logic/InputManager.h"
#include "../Collider/ColliderRect.h"
#include "../Animation/Animation.h"
#include "../Logic/Logic.h"
#include "../Logic/ResourcesManager.h"
#include "../Collider/ColliderSphere.h"
#include "Effect.h"
#include "Enemy.h"

CPlayer::CPlayer()
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
	SetPhysics(true);
	SetForce(700.f);

	m_eDir = DIR_FRONT;
	m_eCharacterDir = CD_RIGHT;

	CColliderRect* pRC = AddCollider<CColliderRect>("PlayerBody");
	pRC->SetInfo(-m_tSize.x / 2, -m_tSize.y / 2, m_tSize.x / 2, m_tSize.y / 2);
	pRC->AddFunction(CS_ENTER, this, &CPlayer::Coll);


	CColliderRect* pFloorRC = AddCollider<CColliderRect>("PlayerFloor");
	pFloorRC->SetInfo(-m_tSize.x / 2, 130, m_tSize.x / 2, m_tSize.y / 2);
	pFloorRC->AddFunction(CS_STAY, this, &CPlayer::FloorColl);

	CColliderSphere* pSR = AddCollider<CColliderSphere>("AttackColl");
	pSR->AddFunction(CS_ENTER, this, &CPlayer::Attack);
	pSR->SetEnable(false);

	m_pAnimation = GET_SINGLE(CResourcesManager)->GetAnimation(RT_BENIMARU)->Clone();
	m_pAnimation->SetObj(this);
	m_pAnimation->SetCurrentClip("LeftIdle");

	return true;
}

void CPlayer::Input(float fDeltaTime)
{
	CMoveObj::Input(fDeltaTime);

	CColliderSphere* pSR = (CColliderSphere*)GetCollider("AttackColl");

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

			else if (KEYPRESS("MoveLeft") && !(tPos.x <= 0))
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

			if (KEYDOWN("Jump"))
			{
				if (m_eCharacterDir == CD_RIGHT)
				{
					m_pAnimation->ChangeClip("RightJump");
					m_pAnimation->SetDefaultClip("RightJump");
				}

				else if (m_eCharacterDir == CD_LEFT)
				{
					m_pAnimation->ChangeClip("LeftJump");
					m_pAnimation->SetDefaultClip("LeftJump");
				}

				m_tPos.y -= m_fJumpOffset;

				Jump();
			}

			if (KEYDOWN("Attack1"))
			{
				m_bAttack = true;

				if (m_eCharacterDir == CD_RIGHT)
				{
					pSR->SetInfo(20.f, POSITION(-80, -80));
					m_pAnimation->ChangeClip("RightAttack1");
					m_pAnimation->SetDefaultClip("RightIdle");
				}

				else if (m_eCharacterDir == CD_LEFT)
				{
					pSR->SetInfo(20.f, POSITION(80, -80));
					m_pAnimation->ChangeClip("LeftAttack1");
					m_pAnimation->SetDefaultClip("LeftIdle");
				}


				pSR->SetEnable(true);
			}


			if (KEYDOWN("Attack2"))
			{
				m_bAttack = true;

				if (m_eCharacterDir == CD_RIGHT)
				{
					pSR->SetInfo(20.f, POSITION(-120, -80));
					m_pAnimation->ChangeClip("RightAttack2");
					m_pAnimation->SetDefaultClip("RightIdle");
				}

				else if (m_eCharacterDir == CD_LEFT)
				{
					pSR->SetInfo(20.f, POSITION(120, -80));
					m_pAnimation->ChangeClip("LeftAttack2");
					m_pAnimation->SetDefaultClip("LeftIdle");
				}


				pSR->SetEnable(true);
			}



			if (KEYDOWN("Attack3"))
			{
				m_bAttack = true;

				if (m_eCharacterDir == CD_RIGHT)
				{
					pSR->SetInfo(20.f, POSITION(-80, -80));
					m_pAnimation->ChangeClip("RightAttack3");
					m_pAnimation->SetDefaultClip("RightIdle");
				}

				else if (m_eCharacterDir == CD_LEFT)
				{
					pSR->SetInfo(20.f, POSITION(80, -80));
					m_pAnimation->ChangeClip("LeftAttack3");
					m_pAnimation->SetDefaultClip("LeftIdle");
				}


				pSR->SetEnable(true);
			}



			if (KEYDOWN("Attack4"))
			{
				m_bAttack = true;

				if (m_eCharacterDir == CD_RIGHT)
				{
					pSR->SetInfo(20.f, POSITION(-110, -80));
					m_pAnimation->ChangeClip("RightAttack4");
					m_pAnimation->SetDefaultClip("RightIdle");
				}

				else if (m_eCharacterDir == CD_LEFT)
				{
					pSR->SetInfo(20.f, POSITION(110, -80));
					m_pAnimation->ChangeClip("LeftAttack4");
					m_pAnimation->SetDefaultClip("LeftIdle");
				}

				pSR->SetEnable(true);
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
				pSR->SetInfo(20.f, POSITION(-90, 120));
			}
			else if (m_eCharacterDir == CD_LEFT)
			{
				m_pAnimation->ChangeClip("LeftSitAttack1");
				pSR->SetInfo(20.f, POSITION(90, 120));
			}


			pSR->SetEnable(true);
		}



		if (KEYDOWN("SitAttack2"))
		{
			m_bSit = true;
			m_bAttack = true;

			if (m_eCharacterDir == CD_RIGHT)
			{
				m_pAnimation->ChangeClip("RightSitAttack2");
				pSR->SetInfo(20.f, POSITION(-75, 0));
			}
			else if (m_eCharacterDir == CD_LEFT)
			{
				m_pAnimation->ChangeClip("LeftSitAttack2");
				pSR->SetInfo(20.f, POSITION(75, 0));
			}


			pSR->SetEnable(true);
		}
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

	CColliderSphere* pSR = (CColliderSphere*)GetCollider("AttackColl");

	if (m_pAnimation->GetMotionEnd())
	{
		m_pAnimation->ReturnClip();
	}

	if (m_pAnimation->GetMotionEnd() && m_bAttack)
	{
		pSR->SetEnable(false);
		m_bAttack = false;
	}


	return 0;
}

void CPlayer::Render(HDC hDC, float fDeltaTime)
{
	CMoveObj::Render(hDC, fDeltaTime);
}

void CPlayer::Coll(CCollider* pCollSrc, CCollider* pCollDest, float fDeltaTime)
{
	CEnemy* pEnemy = (CEnemy*)pCollDest->GetObj();

	if (pCollDest->GetTag() == "EnemyBody"&&
		m_bHit)
	{
		if (m_bSit)
		{
			if (m_eCharacterDir == CD_RIGHT)
			{
				m_pAnimation->ChangeClip("RightSitHurt");
			}
			else if (m_eCharacterDir == CD_LEFT)
			{
				m_pAnimation->ChangeClip("LeftSitHurt");
			}
		}

		else
		{
			if (m_eCharacterDir == CD_RIGHT)
			{
				m_pAnimation->ChangeClip("RightUpHurt");
			}
			else if (m_eCharacterDir == CD_LEFT)
			{
				m_pAnimation->ChangeClip("LeftUpHurt");
			}
		}

		m_bHit = false;
	}
}

void CPlayer::FloorColl(CCollider* pCollSrc, CCollider* pCollDest, float fDeltaTime)
{
	POSITION tPos = m_tPos - m_tSize * m_tPivot;
	CColliderRect* pRC = (CColliderRect*)pCollDest;

	if (pCollDest->GetTag() == "Stage")
	{
		if (!m_bMove)
		{
			m_tPos.y = pRC->GetWorldInfo().t - m_tPivot.y * m_tSize.y;
			m_fJumpOffset = 1.f;
		}

		else
			m_fJumpOffset = tPos.y + m_tSize.y - pRC->GetWorldInfo().t + 1.f;

		if (!m_bSit && m_bJump)
		{
			if (m_eCharacterDir == CD_RIGHT)
			{
				m_pAnimation->SetDefaultClip("RightIdle");
			}

			else if (m_eCharacterDir == CD_LEFT)
			{
				m_pAnimation->SetDefaultClip("LeftIdle");
			}

			m_pAnimation->ReturnClip();
		}



		ClearGravity();

		JumpEnd();
	}
}

void CPlayer::Attack(CCollider* pCollSrc, CCollider* pCollDest, float fDeltaTime)
{
	CColliderSphere* pSR = (CColliderSphere*)pCollSrc;

	if (pCollDest->GetTag() == "EnemyBody" && m_bAttack)
	{
		CEnemy* pEnemy = (CEnemy*)pCollDest->GetObj();

		if (pEnemy)
		{
			CEffect* pEffect = pEnemy->CreateEffect("Attack", ET_HURT_BIG);
			pEffect->SetPos(pSR->GetWorldInfo().tCenter.x - pSR->GetWorldInfo().fRadius, 
				pSR->GetWorldInfo().tCenter.y - pSR->GetWorldInfo().fRadius);
			AddGuage(10.f);
			pEnemy->AddHP(-10.f);
			pEnemy->SetHit(true);
			SetWindowTextA(WINDOWHANDLE, to_string(pEnemy->GetHP()).c_str());
		}

		pCollSrc->SetEnable(false);
		pCollSrc->EraseCollider(pCollDest);
		pCollDest->EraseCollider(pCollSrc);
	}

}
