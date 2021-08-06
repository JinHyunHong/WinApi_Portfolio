#include "Enemy.h"
#include "../Collider/ColliderRect.h"
#include "../Animation/Animation.h"
#include "../Logic/Logic.h"

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

	CColliderRect* pDefalutRC = AddCollider<CColliderRect>("Default");
	pDefalutRC->SetInfo(-m_tSize.x / 2, -m_tSize.y / 2, m_tSize.x / 2, m_tSize.y / 2);

	CColliderRect* pLeftRC = AddCollider<CColliderRect>("LeftSight");
	pLeftRC->SetInfo(pDefalutRC->GetInfo().l - m_tSize.x, pDefalutRC->GetInfo().t,
		pDefalutRC->GetInfo().l, pDefalutRC->GetInfo().b);

	CColliderRect* pRightRC = AddCollider<CColliderRect>("RightSight");
	pRightRC->SetInfo(pDefalutRC->GetInfo().r, pDefalutRC->GetInfo().t, 
		pDefalutRC->GetInfo().r + m_tSize.x, pDefalutRC->GetInfo().b);

	CreateAnimation("Enemy");

	vector<wstring> vecFileName;

	for (int i = 0; i <= 5; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Right\\Idle\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip("EnemyRightIdle", AT_FRAME, AO_LOOP, 1.2f, 6, 1, 0, 0, 6, 1, 0.f, "EnemyRightIdle", vecFileName, KYO_PATH);
	SetAnimationClipColorKey("EnemyRightIdle", 8, 8, 66);

	vecFileName.clear();

	for (int i = 0; i <= 2; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Right\\Walk\\Front\\%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip("EnemyRightWalkFront", AT_FRAME, AO_ONCE_RETURN, 0.3f, 3, 1, 0, 0, 3, 1, 0.f, "EnemyRightWalkFront", vecFileName, KYO_PATH);
	SetAnimationClipColorKey("EnemyRightWalkFront", 8, 8, 66);

	return true;
}

void CEnemy::Input(float fDeltaTime)
{
	CMoveObj::Input(fDeltaTime);
}

int CEnemy::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);


	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	int bCollision = false;
	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetCollision())
		{
			bCollision = true;
			m_pAnimation->SetDefaultClip("EnemyRightIdle");
		}
	}

	// 패트롤 상태
	if (!bCollision)
	{
		POSITION tPos = m_tPos + m_tSize * m_tPivot;

		if (tPos.x <= 0)
		{
			m_eDir = DIR_RIGHT;
			MoveToXSpeed(fDeltaTime);
			m_pAnimation->ChangeClip("EnemyRightWalkFront");

		}

		else if(tPos.x >= WORLDWIDTH)
		{
			m_eDir = DIR_LEFT;
			MoveToXSpeed(fDeltaTime);
			m_pAnimation->ChangeClip("EnemyRightWalkFront");
		}
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
