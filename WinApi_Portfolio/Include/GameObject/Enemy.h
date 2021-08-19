#pragma once
#include "MoveObj.h"
class CEnemy :
    public CMoveObj
{
private:
	friend class CGameObj;
	friend class CScene;

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

public:
	void Coll(CCollider* pCollSrc, CCollider* pCollDest, float fDeltaTime);
	void Physics(CCollider* pCollSrc, CCollider* pCollDest, float fDeltaTime);
	void FloorColl(CCollider* pCollSrc, CCollider* pCollDest, float fDeltaTime);
};

