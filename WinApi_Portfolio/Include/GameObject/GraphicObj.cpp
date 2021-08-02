#include "GraphicObj.h"
#include "../Texture/Texture.h"
#include "../Logic/Camera.h"
#include "../Logic/ResourcesManager.h"


CGraphicObj::CGraphicObj()	:
	m_pTexture(NULL)
{
}

CGraphicObj::CGraphicObj(const CGraphicObj& graphicobj)	:
	CObj(graphicobj)
{
	m_pTexture = graphicobj.m_pTexture;
}

CGraphicObj::~CGraphicObj()
{
	Safe_Release_VecList(m_ColliderList);
	SAFE_RELEASE(m_pTexture);
}

bool CGraphicObj::Init()
{
	return true;
}

CCollider* CGraphicObj::GetCollider(const string& strTag) 
{
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
		{
			return (*iter);
		}
	}

	return NULL;
}

void CGraphicObj::Input(float fDeltaTime)
{
	CObj::Input(fDeltaTime);

	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetLife())
		{
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
			continue;
		}

		(*iter)->Input(fDeltaTime);
	}
}

int CGraphicObj::Update(float fDeltaTime)
{
	CObj::Update(fDeltaTime);

	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetLife())
		{
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
			continue;
		}

		(*iter)->Update(fDeltaTime);
	}
	return 0;
}

void CGraphicObj::Collision(float fDeltaTime)
{
}

int CGraphicObj::LateUpdate(float fDeltaTime)
{
	CObj::LateUpdate(fDeltaTime);

	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetLife())
		{
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
			continue;
		}

		(*iter)->LateUpdate(fDeltaTime);
	}
	return 0;
}

void CGraphicObj::Render(HDC hDC, float fDeltaTime)
{
	CObj::Render(hDC, fDeltaTime);

	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetLife())
		{
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
			continue;
		}

		(*iter)->Render(hDC, fDeltaTime);
	}

	if (m_pTexture)
	{
		POSITION tPos = m_tPos - m_tSize * m_tPivot;
		tPos -= GET_SINGLE(CCamera)->GetPos();

		if (m_pTexture->GetColorKeyEnable())
		{
			TransparentBlt(hDC, tPos.x, tPos.y, m_tSize.x, m_tSize.y,
				m_pTexture->GetDC(), 0, 0, m_tSize.x, m_tSize.y, m_pTexture->GetColorKey());
		}

		else
		{
			BitBlt(hDC, tPos.x, tPos.y, m_tSize.x,
				m_tSize.y, m_pTexture->GetDC(), 0, 0, SRCCOPY);
		}
	}
}

void CGraphicObj::SetTexture(CTexture* pTex)
{
	SAFE_RELEASE(m_pTexture);
	m_pTexture = pTex;
}


void CGraphicObj::SetTexture(const string& strKey, const wchar_t* pFileName, const string& strPathKey)
{
	SAFE_RELEASE(m_pTexture);
	m_pTexture = GET_SINGLE(CResourcesManager)->LoadTexture(strKey, pFileName, strPathKey);
}



void CGraphicObj::SetColorKey(unsigned int r, unsigned int g, unsigned int b)
{
	m_pTexture->SetColorKey(r, g, b);
}

void CGraphicObj::SetColorKey(COLORREF rgb)
{
	m_pTexture->SetColorKey(rgb);
}
