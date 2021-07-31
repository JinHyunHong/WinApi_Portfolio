#include "Obj.h"
#include "Texture/Texture.h"
#include "Logic/Camera.h"
#include "Logic/ResourcesManager.h"


CObj::CObj()	:
	m_bLife(true),
	m_pTexture(NULL)
{
	DEFINITION_REFERENCE_COUNT();
}

CObj::CObj(const CObj& obj)
{
	m_strTag = obj.m_strTag;
	m_tSize = obj.m_tSize;
}

CObj::~CObj()
{
	SAFE_RELEASE(m_pTexture);
}

void CObj::SetTexture(CTexture* pTex)
{
	SAFE_RELEASE(m_pTexture);
	m_pTexture = pTex;
}


void CObj::SetTexture(const string& strKey, const wchar_t* pFileName, const string& strPathKey)
{
	SAFE_RELEASE(m_pTexture);
	m_pTexture = GET_SINGLE(CResourcesManager)->LoadTexture(strKey, pFileName, strPathKey);
}



void CObj::SetColorKey(unsigned int r, unsigned int g, unsigned int b)
{
	m_pTexture->SetColorKey(r, g, b);
}

void CObj::SetColorKey(COLORREF rgb)
{
	m_pTexture->SetColorKey(rgb);
}

bool CObj::Init()
{
	return true;
}

void CObj::Input(float fDeltaTime)
{
}

int CObj::Update(float fDeltaTime)
{
	return 0;
}

void CObj::Collision(float fDeltaTime)
{
}

int CObj::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CObj::Render(HDC hDC, float fDeltaTime)
{
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
