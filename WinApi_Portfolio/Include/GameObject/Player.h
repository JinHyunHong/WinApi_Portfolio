#pragma once
#include "MoveObj.h"

#include "../Game.h"

class CPlayer :
    public CMoveObj
{
private:
	friend class CGameObj;
	friend class CScene;

private:
	float fHP;

private:
	CPlayer();
	CPlayer(const CPlayer& player);
	~CPlayer();

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

