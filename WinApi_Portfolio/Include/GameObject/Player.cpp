#include "Player.h"
#include "../Logic/InputManager.h"
#include "../Collider/ColliderRect.h"
#include "../Animation/Animation.h"
#include "../Logic/Logic.h"
#include "../Logic/ResourcesManager.h"
#include "../Collider/ColliderSphere.h"
#include "Effect.h"
#include "Enemy.h"
#include "../Collider/ColliderPoint.h"
#include "../Logic/SoundManager.h"

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
	SetInfo(CNT_BENIMARU);

	CMoveObj::Init();

	SetPos(500.f, 480.f);
	SetSpeed(400.f);
	SetSize(166.f, 291.f);
	SetPivot(0.5f, 0.5f);
	SetImageOffset(0.f, 0.f);
	SetPhysics(true);
	SetForce(700.f);

	m_eDir = DIR_FRONT;

	CColliderRect* pRC = AddCollider<CColliderRect>("PlayerBody");
	pRC->SetInfo(-m_tSize.x / 2, -m_tSize.y / 2, m_tSize.x / 2, m_tSize.y / 2);
	pRC->AddFunction(CS_ENTER, this, &CPlayer::Coll);

	CColliderPoint* pSmallBodyRC = AddCollider<CColliderPoint>("PlayerPhysicsBody");
	pSmallBodyRC->SetPos(POSITION(m_tPos.x / 2, m_tPos.y / 2));
	pSmallBodyRC->AddFunction(CS_STAY, this, &CPlayer::Physics);


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
	
	
	if (!m_bAttack)
	{
		if (!m_bSit)
		{
			if (KEYDOWN("MovingLeft"))
			{
				m_eDir = DIR_BACK;

				if (m_eCharacterDir == CD_RIGHT)
				{
					MoveToXSpeed(fDeltaTime);
					m_pAnimation->SetDefaultClip("RightIdle");
				}

				else if (m_eCharacterDir == CD_LEFT)
				{
					MoveToX(-200.f);
					m_pAnimation->ChangeClip("LeftMovingBack");
					m_pAnimation->SetDefaultClip("LeftIdle");
				}
			}

			else if (KEYPRESS("MoveLeft"))
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


			if (KEYPRESS("MoveRight"))
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



			if (KEYDOWN("MovingRight"))
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
				int iRand = (rand() % m_tInfo.tSoundCount.iHit) + 1;
				char strSoundName[20] = { 0, };
				sprintf_s(strSoundName, "Hit%d", iRand);
				GET_SINGLE(CSoundManager)->Play(strSoundName, GST_PLAYERBGM, m_tInfo.eType);

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
				int iRand = (rand() % m_tInfo.tSoundCount.iHit) + 1;
				char strSoundName[20] = { 0, };
				sprintf_s(strSoundName, "Hit%d", iRand);
				GET_SINGLE(CSoundManager)->Play(strSoundName, GST_PLAYERBGM, m_tInfo.eType);
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
				int iRand = (rand() % m_tInfo.tSoundCount.iHit) + 1;
				char strSoundName[20] = { 0, };
				sprintf_s(strSoundName, "Hit%d", iRand);
				GET_SINGLE(CSoundManager)->Play(strSoundName, GST_PLAYERBGM, m_tInfo.eType);
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
				int iRand = (rand() % m_tInfo.tSoundCount.iHit) + 1;
				char strSoundName[20] = { 0, };
				sprintf_s(strSoundName, "Hit%d", iRand);
				GET_SINGLE(CSoundManager)->Play(strSoundName, GST_PLAYERBGM, m_tInfo.eType);
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

			if (KEYDOWN("SpecialAttack1"))
			{
				if (GetGuage() >= 100.f)
				{
					m_bAttack = true;

					GET_SINGLE(CSoundManager)->Play("SpecialAttack1", GST_PLAYERBGM, m_tInfo.eType);


					CEffect* pEffect = CreateEffect("SpecialAttack1", ET_BENIMARU_SPECIAL1);
					CEffect* pEffect1 = CreateEffect("SpecialAttack1_1", ET_BENIMARU_SPECIAL1_1);

					if (m_eCharacterDir == CD_RIGHT)
					{
						m_pAnimation->ChangeClip("RightSpecialAttack1");
						pEffect->SetPos(m_tPos.x - 260.f, m_tPos.y - 110.f);
						pEffect1->SetPos(m_tPos.x + 20.f, m_tPos.y - 350.f);
						pSR->SetInfo(50.f, POSITION(-210, -80));
						m_pAnimation->SetDefaultClip("RightIdle");
					}

					else if (m_eCharacterDir == CD_LEFT)
					{
						m_pAnimation->ChangeClip("LeftSpecialAttack1");
						pEffect->SetPos(m_tPos.x + 130.f,  m_tPos.y - 110.f);
						pEffect1->SetPos(m_tPos.x - 90.f, m_tPos.y - 350.f);
						pSR->SetInfo(50.f, POSITION(180, -80));
						m_pAnimation->SetDefaultClip("LeftIdle");
					}

					pSR->SetEnable(true);

					AddGuage(-m_tInfo.fGuage);
				}
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
			int iRand = (rand() % m_tInfo.tSoundCount.iHit) + 1;
			char strSoundName[20] = { 0, };
			sprintf_s(strSoundName, "Hit%d", iRand);
			GET_SINGLE(CSoundManager)->Play(strSoundName, GST_PLAYERBGM, m_tInfo.eType);
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
			int iRand = (rand() % m_tInfo.tSoundCount.iHit) + 1;
			char strSoundName[20] = { 0, };
			sprintf_s(strSoundName, "Hit%d", iRand);
			GET_SINGLE(CSoundManager)->Play(strSoundName, GST_PLAYERBGM, m_tInfo.eType);
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

	POSITION tPos = m_tPos - m_tSize * m_tPivot;

	if (tPos.x >= WORLDWIDTH - m_tSize.x - 20.f)
	{
		m_eCharacterDir = CD_RIGHT;
		m_tPos.x = WORLDWIDTH - m_tSize.x * m_tPivot.x;
	}

	else if (tPos.x <= 20.f)
	{
		m_eCharacterDir = CD_LEFT;
		m_tPos.x = m_tSize.x * m_tPivot.x;
	}


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

	if (pCollDest->GetTag() == "EnemyAttackColl"&&
		m_bHit)
	{
		int iRand = (rand() % m_tInfo.tSoundCount.iDamage) + 1;
		char strSoundName[20] = { 0, };
		sprintf_s(strSoundName, "Damage%d", iRand);
		GET_SINGLE(CSoundManager)->Play(strSoundName, GST_PLAYERBGM, m_tInfo.eType);

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

void CPlayer::Physics(CCollider* pCollSrc, CCollider* pCollDest, float fDeltaTime)
{
	if (pCollDest->GetTag() == "EnemyBody")
	{
		if (m_eCharacterDir == CD_RIGHT)
		{
			MoveToX(3.f);
		}
		else if (m_eCharacterDir == CD_LEFT)
		{
			MoveToX(-3.f);
		}
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
			m_fJumpOffset = tPos.y + m_tSize.y - pRC->GetWorldInfo().t;

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
			CEffect* pEffect = pEnemy->CreateEffect("Attack", (EFFECT_TYPE)(rand() % (int)ET_EFFECT_END));
			pEffect->SetPos(pSR->GetWorldInfo().tCenter.x - pSR->GetWorldInfo().fRadius, 
				pSR->GetWorldInfo().tCenter.y - pSR->GetWorldInfo().fRadius);
			AddGuage(10.f);
			pEnemy->Damage(((rand() % (int)m_tInfo.fAttackMax) + (int)m_tInfo.fAttackMin) + (float(rand()) / float(RAND_MAX)));
			pEnemy->SetHit(true);
			SetWindowTextA(WINDOWHANDLE, to_string(pEnemy->GetHP()).c_str());
		}
	}

	pCollSrc->SetEnable(false);
	pCollSrc->EraseCollider(pCollDest);
	pCollDest->EraseCollider(pCollSrc);
}
