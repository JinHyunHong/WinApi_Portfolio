#pragma once
#include "GameObj.h"

class CMoveObj :
    public CGameObj
{
protected:
	CMoveObj();
	CMoveObj(const CMoveObj& Obj);
	virtual ~CMoveObj();

protected:
	float			         m_fSpeed;
	float			         m_fForce;
	float			         m_fForceOrigin;
	bool			         m_bJump;
	float					 m_fJumpOffset;
	DIR				         m_eDir;
	float			         m_fGravityTime;
	bool			         m_bPhysics;
	float			         m_fAngle;
	CHARACTER_DIR			 m_eCharacterDir;
	list<class CEffect*>	 m_EffectList;
	float					 m_fHP;
	float					 m_fGuage;
	bool					 m_bSit;
	bool					 m_bAttack;
	bool					 m_bHit;
	bool					 m_bMove;

public:
	float GetHP()	const
	{
		return m_fHP;
	}

	float GetGuage()	const
	{
		return m_fGuage;
	}

	bool GetSit()	const
	{
		return m_bSit;
	}

	bool GetAttack()	const
	{
		return m_bAttack;
	}

	bool GetHit()	const
	{
		return m_bHit;
	}

	void AddHP(float fHP)
	{
		m_fHP += fHP;
	}

	void AddGuage(float fGuage)
	{
		m_fGuage += fGuage;
	}

	void SetPhysics(bool bPhysics)
	{
		m_bPhysics = bPhysics;
	}

	void SetHit(bool bHit)
	{
		m_bHit = bHit;
	}

public:
	void SetSpeed(float fSpeed)
	{
		m_fSpeed = fSpeed;
	}

	void SetCharacterDir(CHARACTER_DIR eCharacterDir)
	{
		m_eCharacterDir = eCharacterDir;
	}

	float GetSpeed()	const
	{
		return m_fSpeed;
	}

	CHARACTER_DIR GetCharacterDir()	const
	{
		return m_eCharacterDir;
	}

	void ClearGravity()
	{
		m_fGravityTime = 0.f;
	}

	void JumpEnd()
	{
		m_bJump = false;
		m_fForce = 0;
	}

	void SetForce(float fForce)
	{
		m_fForceOrigin = fForce;
	}


public:
	CEffect* CreateEffect(const string& strTag, EFFECT_TYPE eType, int iLimitCount = 1);
	bool EraseEffect(const string& strTag);
	bool EraseEffect(CEffect* pEffect);
	bool EraseEffect();

protected:
	void Jump();
	void MoveToX(float x);
	void MoveToX(float x, float fDeltaTime);
	void MoveToXSpeed(float fDeltaTime);
	void MoveToAngle(float fDeltaTime);
	void MoveToY(float y);
	void MoveToY(float y, float fDeltaTime);	
	void MoveToYSpeed(float fDeltaTime);

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

