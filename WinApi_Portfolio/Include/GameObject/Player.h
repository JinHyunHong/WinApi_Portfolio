#pragma once
#include "MoveObj.h"

class CPlayer :
    public CMoveObj
{
private:
	friend class CGameObj;
	friend class CScene;

private:
	CPlayer();
	CPlayer(const CPlayer& player);
	~CPlayer();

private:
	float	m_fHP;
	bool	m_bSit;
	bool	m_bAttack;

public:
	float GetHP()	const
	{
		return m_fHP;
	}

	bool GetSit()	const
	{
		return m_bSit;
	}

	bool GetAttack()	const
	{
		return m_bAttack;
	}


public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);

public:
	static void Hurt(CCollider* pCollSrc, CCollider* pCollDest, float fDeltaTime);
};

