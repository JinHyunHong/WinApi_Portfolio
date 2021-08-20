#include "MoveObj.h"
#include "Effect.h"
#include "../Logic/SoundManager.h"

CMoveObj::CMoveObj()	:
	m_fSpeed(200.f),
	m_fForce(0.f),
	m_fForceOrigin(0.f),
	m_bJump(false),
	m_eDir(DIR_NONE),
	m_fAngle(0.f),
	m_fGravityTime(0.f),
	m_bPhysics(false),
	m_bSit(false),
	m_bAttack(false),
	m_bHit(false),
	m_bMove(false),
	m_fJumpOffset(0.f)
{
}

CMoveObj::CMoveObj(const CMoveObj& Obj) :
	CGameObj(Obj)
{
	m_fSpeed = Obj.m_fSpeed;
	m_fForceOrigin = Obj.m_fForceOrigin; 
	m_bPhysics = Obj.m_bPhysics;
}

CMoveObj::~CMoveObj()
{
	EraseEffect();
}

void CMoveObj::SetInfo(CHARACTER_NAME_TYPE eType)
{
	m_tInfo.eType = eType;

	switch (eType)
	{
	case CNT_BENIMARU:
		m_tInfo.fAttackMin = BENIMARU_ATTACK_MIN;
		m_tInfo.fAttackMax = BENIMARU_ATTACK_MAX;
		m_tInfo.fDefenseMin = BENIMARU_DEFENSE_MIN;
		m_tInfo.fDefenseMax = BENIMARU_DEFENSE_MAX;
		return;
	case CNT_KYO:
		m_tInfo.fAttackMin = KYO_ATTACK_MIN;
		m_tInfo.fAttackMax = KYO_ATTACK_MAX;
		m_tInfo.fDefenseMin = KYO_DEFENSE_MIN;
		m_tInfo.fDefenseMax = KYO_DEFENSE_MAX;
		return;
	}
}

CEffect* CMoveObj::CreateEffect(const string& strTag, EFFECT_TYPE eType)
{
	EraseEffect(strTag);

	CEffect* pEffect = new CEffect;

	if (!pEffect->Init())
	{
		SAFE_RELEASE(pEffect);
		return NULL;
	}

	pEffect->SetTag(strTag);
	pEffect->SetType(eType);
	pEffect->SetObj(this);
	pEffect->AddRef();

	m_EffectList.push_back(pEffect);

	return pEffect;
}

bool CMoveObj::EraseEffect(const string& strTag)
{
	list<CEffect*>::iterator iter;
	list<CEffect*>::iterator iterEnd = m_EffectList.end();

	for (iter = m_EffectList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
		{
			SAFE_RELEASE((*iter));
			iter = m_EffectList.erase(iter);
			iterEnd = m_EffectList.end();
			return true;
		}
	}

	return false;
}

bool CMoveObj::EraseEffect(CEffect* pEffect)
{
	list<CEffect*>::iterator iter;
	list<CEffect*>::iterator iterEnd = m_EffectList.end();

	for (iter = m_EffectList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter) == pEffect)
		{
			SAFE_RELEASE((*iter));
			iter = m_EffectList.erase(iter);
			iterEnd = m_EffectList.end();
			return true;
		}
	}

	return false;
}


bool CMoveObj::EraseEffect()
{
	Safe_Release_VecList(m_EffectList);

	return true;
}

void CMoveObj::Jump()
{
	if (!m_bJump)
	{
		m_bJump = true;
		m_fForce = m_fForceOrigin;
	}
}

void CMoveObj::MoveToX(float x)
{
	m_tPos.x += x;
	m_bMove = true;
}

void CMoveObj::MoveToX(float x, float fDeltaTime)
{
	m_tPos.x += x * fDeltaTime;
	m_bMove = true;
}

void CMoveObj::MoveToXSpeed(float fDeltaTime)
{
	m_tPos.x += m_fSpeed * fDeltaTime * m_eDir;
	m_bMove = true;
}

void CMoveObj::MoveToAngle(float fDeltaTime)
{
	m_tPos.x += cosf(m_fAngle) * m_fSpeed * fDeltaTime; 
	m_tPos.y += sinf(m_fAngle) * m_fSpeed * fDeltaTime;
	m_bMove = true;
}

void CMoveObj::MoveToY(float y)
{
	m_tPos.y += y;
	m_bMove = true;
}

void CMoveObj::MoveToY(float y, float fDeltaTime)
{
	m_tPos.y += y * fDeltaTime;
	m_bMove = true;
}

void CMoveObj::MoveToYSpeed(float fDeltaTime)
{
	m_tPos.y += m_fSpeed * fDeltaTime * m_eDir;
	m_bMove = true;
}

bool CMoveObj::Init()
{
#ifdef _DEBUG
	AddGuage(100.f);
#endif

	m_tInfo.fHP = m_tInfo.fHPMax;

	// 미리 각 캐릭터의 사운드 갯수를 찾는다.
	m_tInfo.tSoundCount.iHit = GET_SINGLE(CSoundManager)->FindSoundCount("Hit", m_tInfo.eType);
	m_tInfo.tSoundCount.iDamage = GET_SINGLE(CSoundManager)->FindSoundCount("Damage", m_tInfo.eType);

	return true;
}

void CMoveObj::Input(float fDeltaTime)
{
	CGameObj::Input(fDeltaTime);

	list<CEffect*>::iterator iter;
	list<CEffect*>::iterator iterEnd = m_EffectList.end();

	for (iter = m_EffectList.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetLife())
		{
			SAFE_RELEASE((*iter));
			iter = m_EffectList.erase(iter);
			iterEnd = m_EffectList.end();

			if (iter == iterEnd)
				return;
		}

		if (!(*iter)->GetEnable())
		{
			continue;
		}

		(*iter)->Input(fDeltaTime);
	}

}

int CMoveObj::Update(float fDeltaTime)
{
	CGameObj::Update(fDeltaTime);

	if (m_bPhysics)
	{
		m_fGravityTime += fDeltaTime;

		m_fForce -= (GRAVITY * m_fGravityTime);

		m_tPos.y -= m_fForce * fDeltaTime;
	}


	list<CEffect*>::iterator iter;
	list<CEffect*>::iterator iterEnd = m_EffectList.end();

	for (iter = m_EffectList.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetLife())
		{
			SAFE_RELEASE((*iter));
			iter = m_EffectList.erase(iter);
			iterEnd = m_EffectList.end();

			if (iter == iterEnd)
				return 0;
		}

		if (!(*iter)->GetEnable())
		{
			continue;
		}

		(*iter)->Update(fDeltaTime);
	}

	return 0;
}

void CMoveObj::Collision(float fDeltaTime)
{
	CGameObj::Collision(fDeltaTime);

	list<CEffect*>::iterator iter;
	list<CEffect*>::iterator iterEnd = m_EffectList.end();

	for (iter = m_EffectList.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetLife())
		{
			SAFE_RELEASE((*iter));
			iter = m_EffectList.erase(iter);
			iterEnd = m_EffectList.end();

			if (iter == iterEnd)
				return;
		}

		if (!(*iter)->GetEnable())
		{
			continue;
		}

		(*iter)->Collision(fDeltaTime);
	}

}

int CMoveObj::LateUpdate(float fDeltaTime)
{
	CGameObj::LateUpdate(fDeltaTime);

	list<CEffect*>::iterator iter;
	list<CEffect*>::iterator iterEnd = m_EffectList.end();

	for (iter = m_EffectList.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetLife())
		{
			SAFE_RELEASE((*iter));
			iter = m_EffectList.erase(iter);
			iterEnd = m_EffectList.end();

			if (iter == iterEnd)
				return 0;
		}

		if (!(*iter)->GetEnable())
		{
			continue;
		}

		(*iter)->LateUpdate(fDeltaTime);
	}


	m_bMove = false;

	return 0;
}

void CMoveObj::Render(HDC hDC, float fDeltaTime)
{
	CGameObj::Render(hDC, fDeltaTime);

	list<CEffect*>::iterator iter;
	list<CEffect*>::iterator iterEnd = m_EffectList.end();

	for (iter = m_EffectList.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetLife())
		{
			SAFE_RELEASE((*iter));
			iter = m_EffectList.erase(iter);
			iterEnd = m_EffectList.end();

			if (iter == iterEnd)
				return;
		}

		if (!(*iter)->GetEnable())
		{
			continue;
		}

		(*iter)->Render(hDC, fDeltaTime);
	}


}
