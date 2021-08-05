#pragma once
#include "MoveObj.h"
class CEnemy :
    public CMoveObj
{
private:
	friend class CGameObj;
	friend class CScene;

private:
	float m_fHP;

private:
	CEnemy();
	CEnemy(const CEnemy& enemy);
	~CEnemy();

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

