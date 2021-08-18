#include "ColliderManager.h"
#include "../GameObject/GraphicObj.h"
#include "Collider.h"

DEFINITION_SINGLE(CColliderManager);


CColliderManager::CColliderManager()
{

}

CColliderManager::~CColliderManager()
{
	Clear();
}


void CColliderManager::AddObj(CGraphicObj* pGrapicObj)
{
	if (!pGrapicObj->GetCollisonEmpty())
	{
		m_ColliderList.push_back(pGrapicObj);
	}
}

void CColliderManager::Collision(float fDeltaTime)
{
	if (m_ColliderList.size() < 2)
	{
		Clear();
		return;
	}

	list<CGraphicObj*>::iterator iter;
	list<CGraphicObj*>::iterator iterEnd = m_ColliderList.end();
	--iterEnd;

	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		list<CGraphicObj*>::iterator iter1 = iter;
		++iter1;
		list<CGraphicObj*>::iterator iter1End = m_ColliderList.end();

		for (; iter1 != iter1End; ++iter1)
		{
			Collision(*iter, *iter1, fDeltaTime);
		}

	}

	Clear();
}

bool CColliderManager::Collision(CGraphicObj* pSrc, CGraphicObj* pDest, float fDeltaTime)
{
	bool bCollision = false;

	const list<CCollider*>& SrcList = pSrc->GetColliderList();	
	const list<CCollider*>& DestList = pDest->GetColliderList();

	list<CCollider*>::const_iterator SrcIter;
	list<CCollider*>::const_iterator SrcIterEnd = SrcList.end();

	list<CCollider*>::const_iterator DestIter;
	list<CCollider*>::const_iterator DestIterEnd = DestList.end();

	for (SrcIter = SrcList.begin(); SrcIter != SrcIterEnd; ++SrcIter)
	{
		for (DestIter = DestList.begin(); DestIter != DestIterEnd; ++DestIter)
		{
			(*SrcIter)->m_bCollision = false;
			(*DestIter)->m_bCollision = false;
		}
	}

	for (SrcIter = SrcList.begin(); SrcIter != SrcIterEnd; ++SrcIter)
	{
		for (DestIter = DestList.begin(); DestIter != DestIterEnd; ++DestIter)
		{
			if(!(*SrcIter)->GetEnable())
			{
				continue;
			}

			if ((*SrcIter)->Collision(*DestIter))
			{
				(*SrcIter)->m_bCollision = true;
				(*DestIter)->m_bCollision = true;
				bCollision = true;

				if (!(*SrcIter)->CheckColliderList(*DestIter))
				{
					(*SrcIter)->AddCollider(*DestIter);
					(*DestIter)->AddCollider(*SrcIter);

					(*SrcIter)->CallFunction(CS_ENTER, *DestIter, fDeltaTime);
					(*DestIter)->CallFunction(CS_ENTER, *SrcIter, fDeltaTime);
				}

				else
				{
					(*SrcIter)->CallFunction(CS_STAY, *DestIter, fDeltaTime);
					(*DestIter)->CallFunction(CS_STAY, *SrcIter, fDeltaTime);
				}
			}

			else if ((*SrcIter)->CheckColliderList(*DestIter))
			{
				(*SrcIter)->EraseCollider(*DestIter);
				(*DestIter)->EraseCollider(*SrcIter);

				(*SrcIter)->CallFunction(CS_LEAVE, *DestIter, fDeltaTime);
				(*DestIter)->CallFunction(CS_LEAVE, *SrcIter, fDeltaTime);
			}
		}
	}

	return bCollision;
}

void CColliderManager::Clear()
{
	m_ColliderList.clear();
}
