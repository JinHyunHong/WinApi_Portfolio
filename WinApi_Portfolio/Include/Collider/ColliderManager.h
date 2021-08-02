#pragma once

#include "../Game.h"

class CColliderManager
{
	DECLARE_SINGLE(CColliderManager);

private:
	list<class CGraphicObj*> m_ColliderList;

public:
	void AddObj(CGraphicObj* pGrapicObj);
	void Collision(float fDeltaTime);
	bool Collision(CGraphicObj* pSrc, CGraphicObj* pDest, float fDeltaTime);
	void Clear();

};

