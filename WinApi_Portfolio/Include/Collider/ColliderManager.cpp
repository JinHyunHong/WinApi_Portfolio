#include "ColliderManager.h"
#include "../GameObject/GraphicObj.h"

void CColliderManager::AddObj(CGraphicObj* pGrapicObj)
{
	if (!pGrapicObj->GetCollisonEmpty())
	{
		m_ColliderList.push_back(pGrapicObj);
	}
}

void CColliderManager::Collision(float fDeltaTime)
{
}

bool CColliderManager::Collision(CGraphicObj* pSrc, CGraphicObj* pDest, float fDeltaTime)
{
	return false;
}

void CColliderManager::Clear()
{
}
