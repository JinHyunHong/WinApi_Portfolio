#include "Enemy.h"
#include "../Collider/ColliderRect.h"
#include "../Animation/Animation.h"
#include "../Logic/Logic.h"
#include "../Logic/ResourcesManager.h"
#include "Player.h"
#include "../Collider/ColliderPoint.h"
#include "../Logic/SoundManager.h"

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
	CMoveObj::Init();

	SetInfo(CNT_KYO);
	SetSpeed(400.f);
	SetSize(150.f, 300.f);
	SetPos(WORLDWIDTH - m_tSize.x - 200, 480.f);
	SetPivot(0.5f, 0.5f);
	SetImageOffset(0.f, 0.f);
	m_eDir = DIR_FRONT;
	m_eCharacterDir = CD_LEFT;
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
	CColliderRect* pRightRC = AddCollider<CColliderRect>("RightSight");
	pRightRC->SetInfo(pDefalutRC->GetInfo().r, pDefalutRC->GetInfo().t, 
		pDefalutRC->GetInfo().r + (m_tSize.x / 3), pDefalutRC->GetInfo().b);


	m_pAnimation = GET_SINGLE(CResourcesManager)->GetAnimation(RT_KYO)->Clone();
	m_pAnimation->SetObj(this);

	m_tInfo.tSoundCount.iDamage = GET_SINGLE(CSoundManager)->FindSoundCount("Damage", m_tInfo.eType);

	return true;
}

void CEnemy::Input(float fDeltaTime)
{
	CMoveObj::Input(fDeltaTime);


	POSITION tPos = m_tPos - m_tSize * m_tPivot;


	if (tPos.x <= 0)
	{
		m_eCharacterDir = CD_LEFT;
	}

	else if (tPos.x >= WORLDWIDTH - m_tSize.x)
	{
		m_eCharacterDir = CD_RIGHT;
	}

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
