#include "Enemy.h"
#include "../Collider/ColliderRect.h"
#include "../Animation/Animation.h"
#include "../Logic/Logic.h"
#include "../Logic/ResourcesManager.h"
#include "Player.h"
#include "../Collider/ColliderPoint.h"
#include "../Logic/SoundManager.h"
#include "../Collider/ColliderSphere.h"
#include "Effect.h"

CEnemy::CEnemy()
{
}

CEnemy::CEnemy(const CEnemy& enemy)	:
	CMoveObj(enemy)
{
}

CEnemy::~CEnemy()
{
}

bool CEnemy::Init()
{
	SetInfo(CNT_KYO);

	CMoveObj::Init();

	SetSpeed(400.f);
	SetSize(150.f, 300.f);
	SetPos(WORLDWIDTH - m_tSize.x - 300, 450.f);
	SetPivot(0.5f, 0.5f);
	SetImageOffset(0.f, 0.f);
	m_eDir = DIR_FRONT;
	SetPhysics(true);
	SetForce(200.f);

	CColliderRect* pDefalutRC = AddCollider<CColliderRect>("EnemyBody");
	pDefalutRC->SetInfo(-m_tSize.x / 2, -m_tSize.y / 2, m_tSize.x / 2, m_tSize.y / 2);
	pDefalutRC->AddFunction(CS_ENTER, this, &CEnemy::Coll);

	CColliderPoint* pSmallBodyRC = AddCollider<CColliderPoint>("EnemyPhysicsBody");
	pSmallBodyRC->SetPos(POSITION(m_tPos.x / 2, m_tPos.y / 2));
	pSmallBodyRC->AddFunction(CS_STAY, this, &CEnemy::Physics);

	CColliderRect* pFloorRC = AddCollider<CColliderRect>("PlayerFloor");
	pFloorRC->SetInfo(-m_tSize.x / 2, 130, m_tSize.x / 2, m_tSize.y / 2);
	pFloorRC->AddFunction(CS_STAY, this, &CEnemy::FloorColl);

	CColliderRect* pLeftRC = AddCollider<CColliderRect>("LeftSight");
	pLeftRC->SetInfo(pDefalutRC->GetInfo().l - (m_tSize.x / 3), pDefalutRC->GetInfo().t,
		pDefalutRC->GetInfo().l, pDefalutRC->GetInfo().b);
	pLeftRC->AddFunction(CS_STAY, this, &CEnemy::Attack);

	CColliderRect* pRightRC = AddCollider<CColliderRect>("RightSight");
	pRightRC->SetInfo(pDefalutRC->GetInfo().r, pDefalutRC->GetInfo().t, 
		pDefalutRC->GetInfo().r + (m_tSize.x / 3), pDefalutRC->GetInfo().b);
	pRightRC->AddFunction(CS_STAY, this, &CEnemy::Attack);

	CColliderSphere* pSR = AddCollider<CColliderSphere>("EnemyAttackColl");
	pSR->AddFunction(CS_ENTER, this, &CEnemy::Hit);
	pSR->SetEnable(false);


	m_pAnimation = GET_SINGLE(CResourcesManager)->GetAnimation(RT_KYO)->Clone();
	m_pAnimation->SetObj(this);

	m_tInfo.tSoundCount.iDamage = GET_SINGLE(CSoundManager)->FindSoundCount("Damage", m_tInfo.eType);

	return true;
}

void CEnemy::Input(float fDeltaTime)
{
	CMoveObj::Input(fDeltaTime);

	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	int bCollision = false;
	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetCollision())
		{
			CCollider* pPlayerBody = (*iter)->CheckColliderList("PlayerBody");

			if (pPlayerBody)
			{
				bCollision = true;
				CMoveObj* pDestObj = (CMoveObj*)pPlayerBody->GetObj();

				if ((*iter)->GetTag() == "LeftSight")
				{
					m_eCharacterDir = CD_RIGHT;

					if (pDestObj)
					{
						m_pAnimation->SetDefaultClip("RightIdle");
						pDestObj->SetCharacterDir(CD_LEFT);
						break;
					}
				}

				else if ((*iter)->GetTag() == "RightSight")
				{
					m_eCharacterDir = CD_LEFT;

					if (pDestObj)
					{
						m_pAnimation->SetDefaultClip("LeftIdle");
						pDestObj->SetCharacterDir(CD_RIGHT);
						break;
					}
				}

			}
		}
	}

	// 패트롤 상태
	if (!bCollision)
	{
		if (m_eCharacterDir == CD_RIGHT)
		{
			m_eDir = DIR_BACK;
			MoveToXSpeed(fDeltaTime);
			m_pAnimation->ChangeClip("RightWalkFront");
			m_pAnimation->SetDefaultClip("RightIdle");
		}

		else
		{
			m_eDir = DIR_FRONT;
			MoveToXSpeed(fDeltaTime);
			m_pAnimation->ChangeClip("LeftWalkFront");
			m_pAnimation->SetDefaultClip("LeftIdle");

		}

	}

}

int CEnemy::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);

	POSITION tPos = m_tPos - m_tSize * m_tPivot;


	if (tPos.x <= 0)
	{
		m_eCharacterDir = CD_LEFT;
		m_tPos.x = m_tSize.x * m_tPivot.x;
	}

	else if (tPos.x >= WORLDWIDTH - m_tSize.x)
	{
		m_eCharacterDir = CD_RIGHT;
		m_tPos.x = WORLDWIDTH - m_tSize.x * m_tPivot.x;
	}

	return 0;
}

void CEnemy::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
}

int CEnemy::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);

	return 0;
}

void CEnemy::Render(HDC hDC, float fDeltaTime)
{
	CMoveObj::Render(hDC, fDeltaTime);
}

void CEnemy::Coll(CCollider* pCollSrc, CCollider* pCollDest, float fDeltaTime)
{
	if (pCollDest->GetTag() == "Stage")
	{
		ClearGravity();
		JumpEnd();
	}

	if (pCollDest->GetTag() == "AttackColl" && m_bHit)
	{
		int iRand = (rand() % m_tInfo.tSoundCount.iDamage) + 1;
		char strSoundName[20] = { 0, };
		sprintf_s(strSoundName, "Damage%d", iRand);
		GET_SINGLE(CSoundManager)->Play(strSoundName, GST_ENEMYBGM, m_tInfo.eType);

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
				MoveToX(10.f);
			}
			else if (m_eCharacterDir == CD_LEFT)
			{
				GetAnimation()->ChangeClip("LeftUpHurt");					
				MoveToX(-10.f);
			}
		}

		m_bHit = false;
	}
}

void CEnemy::Physics(CCollider* pCollSrc, CCollider* pCollDest, float fDeltaTime)
{
	if (pCollDest->GetTag() == "PlayerBody")
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

void CEnemy::FloorColl(CCollider* pCollSrc, CCollider* pCollDest, float fDeltaTime)
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

void CEnemy::Attack(CCollider* pCollSrc, CCollider* pCollDest, float fDeltaTime)
{
	if (m_pAnimation->GetMotionEnd() || m_bHit)
	{
		if (pCollDest->GetTag() == "PlayerBody")
		{
			CColliderSphere* pSR = (CColliderSphere*)GetCollider("EnemyAttackColl");

			int iRand = 0;
			char strName[20] = { 0, };
			if (m_eCharacterDir == CD_RIGHT)
			{
				iRand = (rand() % 4) + 1;
				sprintf_s(strName, "RightAttack%d", iRand);
				GetAnimation()->ChangeClip(strName);
				m_pAnimation->SetDefaultClip("RightIdle");

				iRand = (rand() % m_tInfo.tSoundCount.iHit) + 1;
				char strSoundName[20] = { 0, };
				sprintf_s(strSoundName, "Hit%d", iRand);
				GET_SINGLE(CSoundManager)->Play(strSoundName, GST_ENEMYBGM, m_tInfo.eType);

				if (strcmp(strName, "RightAttack1") == 0)
					pSR->SetInfo(30.f, POSITION(-90.f, -80.f));
				else if (strcmp(strName, "RightAttack2") == 0)
					pSR->SetInfo(35.f, POSITION(-90.f, 60.f));
				else if (strcmp(strName, "RightAttack3") == 0)
					pSR->SetInfo(30.f, POSITION(-90.f, -80.f));
				else if (strcmp(strName, "RightAttack4") == 0)
					pSR->SetInfo(30.f, POSITION(-90.f, -80.f));

				m_bAttack = true;
				pSR->SetEnable(true);
			}

			else if (m_eCharacterDir == CD_LEFT)
			{
				iRand = (rand() % 4) + 1;
				sprintf_s(strName, "LeftAttack%d", iRand);
				GetAnimation()->ChangeClip(strName);
				m_pAnimation->SetDefaultClip("LeftIdle");

				iRand = (rand() % m_tInfo.tSoundCount.iHit) + 1;
				char strSoundName[20] = { 0, };
				sprintf_s(strSoundName, "Hit%d", iRand);
				GET_SINGLE(CSoundManager)->Play(strSoundName, GST_ENEMYBGM, m_tInfo.eType);

				if (strcmp(strName, "LeftAttack1") == 0)
					pSR->SetInfo(30.f, POSITION(90.f, -80.f));
				else if (strcmp(strName, "LeftAttack2") == 0)
					pSR->SetInfo(35.f, POSITION(90.f, 60.f));
				else if (strcmp(strName, "LeftAttack3") == 0)
					pSR->SetInfo(30.f, POSITION(90.f, -80.f));
				else if (strcmp(strName, "LeftAttack4") == 0)
					pSR->SetInfo(30.f, POSITION(90.f, -80.f));

				m_bAttack = true;
				pSR->SetEnable(true);
			}
		}
	}
}

void CEnemy::Hit(CCollider* pCollSrc, CCollider* pCollDest, float fDeltaTime)
{
	CColliderSphere* pSR = (CColliderSphere*)pCollSrc;

	if (pCollDest->GetTag() == "PlayerBody" && m_bAttack)
	{
		CPlayer* pPlayer = (CPlayer*)pCollDest->GetObj(); 

		if (pPlayer)
		{
			CEffect* pEffect = pPlayer->CreateEffect("Attack", (EFFECT_TYPE)(rand() % (int)ET_EFFECT_END));
			pEffect->SetPos(pSR->GetWorldInfo().tCenter.x - pSR->GetWorldInfo().fRadius,
				pSR->GetWorldInfo().tCenter.y - pSR->GetWorldInfo().fRadius);
			AddGuage(10.f);
			pPlayer->Damage(((rand() % (int)m_tInfo.fAttackMax) + (int)m_tInfo.fAttackMin) + (float(rand()) / float(RAND_MAX)));
			pPlayer->SetHit(true);
		}
		m_bAttack = false;
	}

	pCollSrc->SetEnable(false);
	pCollSrc->EraseCollider(pCollDest);
	pCollDest->EraseCollider(pCollSrc);
}
