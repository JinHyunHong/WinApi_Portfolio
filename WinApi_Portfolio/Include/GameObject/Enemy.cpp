#include "Enemy.h"
#include "../Collider/ColliderRect.h"
#include "../Animation/Animation.h"
#include "../Logic/Logic.h"
#include "../Logic/ResourcesManager.h"

CEnemy::CEnemy()	:
	m_fHP(0.f)
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
	SetSpeed(400.f);
	SetSize(200.f, 300.f);
	SetPos(WORLDWIDTH - m_tSize.x - 200, 500.f);
	SetPivot(0.5f, 0.5f);
	SetImageOffset(0.f, 0.f);
	m_eDir = DIR_FRONT;
	m_eCharacterDir = CD_LEFT;

	CColliderRect* pDefalutRC = AddCollider<CColliderRect>("Default");
	pDefalutRC->SetInfo(-m_tSize.x / 2, -m_tSize.y / 2, m_tSize.x / 2, m_tSize.y / 2);

	CColliderRect* pLeftRC = AddCollider<CColliderRect>("LeftSight");
	pLeftRC->SetInfo(pDefalutRC->GetInfo().l - m_tSize.x, pDefalutRC->GetInfo().t,
		pDefalutRC->GetInfo().l, pDefalutRC->GetInfo().b);

	CColliderRect* pRightRC = AddCollider<CColliderRect>("RightSight");
	pRightRC->SetInfo(pDefalutRC->GetInfo().r, pDefalutRC->GetInfo().t, 
		pDefalutRC->GetInfo().r + m_tSize.x, pDefalutRC->GetInfo().b);


	m_pAnimation = GET_SINGLE(CResourcesManager)->GetAnimation(WCT_KYO)->Clone();
	m_pAnimation->SetObj(this);
	m_pAnimation->SetCurrentClip("LeftIdle");


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
			bCollision = true;
		}
	}


	if (m_eCharacterDir == CD_LEFT)
	{
		m_pAnimation->SetDefaultClip("RightIdle");
	}

	else
	{
		m_pAnimation->SetDefaultClip("LeftIdle");
	}

	// 패트롤 상태
	if (!bCollision)
	{
		POSITION tPos = m_tPos - m_tSize * m_tPivot;


		if (tPos.x <= 0)
		{
			m_eCharacterDir = CD_RIGHT;
		}

		else if (tPos.x >= WORLDWIDTH - m_tSize.x)
		{
			m_eCharacterDir = CD_LEFT;
		}


		if (m_eCharacterDir == CD_RIGHT)
		{
			m_eDir = DIR_FRONT;
			MoveToXSpeed(fDeltaTime);
			m_pAnimation->ChangeClip("LeftWalkFront");

		}

		else
		{
			m_eDir = DIR_BACK;
			MoveToXSpeed(fDeltaTime);
			m_pAnimation->ChangeClip("RightWalkFront");

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
