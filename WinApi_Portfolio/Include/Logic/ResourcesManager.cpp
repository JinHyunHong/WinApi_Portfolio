#include "ResourcesManager.h"
#include "../Texture/Texture.h"

DEFINITION_SINGLE(CResourcesManager);

CResourcesManager::CResourcesManager()
{

}

CResourcesManager::~CResourcesManager()
{
	SAFE_RELEASE(m_pBackBuffer);
	Safe_Release_Map(m_mapTex);
}

CTexture* CResourcesManager::GetBackBuffer() const
{
	m_pBackBuffer->AddRef();

	return m_pBackBuffer;
}

CTexture* CResourcesManager::LoadTexture(const string& strKey, const wchar_t* pFileName, const string& strPathKey)
{
	CTexture* pTex = FindTexture(strKey);

	if (!pTex)
	{
		pTex = new CTexture;
		if (!pTex->LoadTexture(m_hInst, m_hDC, pFileName, strPathKey))
		{
			SAFE_RELEASE(pTex);
			return NULL;
		}
		m_mapTex.insert(make_pair(strKey, pTex));
	}
	
	pTex->AddRef();

	return pTex;
}

CTexture* CResourcesManager::FindTexture(const string& strKey)
{
	unordered_map<string, CTexture*>::iterator iter = m_mapTex.find(strKey);

	if (iter == m_mapTex.end())
		return NULL;

	iter->second->AddRef();

	return iter->second;
}

bool CResourcesManager::EraseTexture(const string& strKey)
{
	CTexture* pTex = FindTexture(strKey);

	if (pTex)
	{
		SAFE_RELEASE(pTex);
		return true;
	}

	return false;

}

bool CResourcesManager::Init(HINSTANCE hInst, HDC hDC)
{
	m_hInst = hInst;
	m_hDC = hDC;

	m_pBackBuffer = LoadTexture("BackBuffer", L"BackBuffer.bmp");

	return true;
}
