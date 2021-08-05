#include "ResourcesManager.h"
#include "../Texture/Texture.h"
#include "FileManager.h"

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


	//===================================================
	// 폰트 리소스 추가하기
	string strPath = GET_SINGLE(CFileManager)->FindPathMultiByte(FONT_PATH);
	strPath += "Kemco Pixel Bold.ttf";
	AddFontResourceA(strPath.c_str());

	AddFont("KOFMainFont10", 10, 10, 0, 0, 0, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, "KOF '96 - '99 Big Font");
	AddFont("KOFMainFont17", 15, 17, 0, 0, 0, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, "Kemco Pixel");
	AddFont("KOFMainFont23", 21, 23, 0, 0, 0, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, "Kemco Pixel");

	return true;
}

HFONT CResourcesManager::FindFont(const string& strKey)
{
	unordered_map<string, HFONT>::iterator iter = m_mapFont.find(strKey);

	if (iter == m_mapFont.end())
		return NULL;

	return iter->second;
}

HFONT CResourcesManager::AddFont(const string& strKey, int iHeight, int iWidth, int iEscapement, int iOrientation, int iWeight,
	DWORD bItalic, DWORD bUnderline, DWORD bStrikeOut, DWORD lCharSet, DWORD lOutPrecision, DWORD lClipPrecision, DWORD lQuality,
	DWORD lPitchAndFamily, LPCSTR strFaceName)
{
	HFONT hFindFont;
	hFindFont = FindFont(strKey);
	if (hFindFont)
		return hFindFont;

	HFONT pFont = new HFONT__;

	pFont = CreateFontA(iHeight, iWidth, iEscapement, iOrientation, iWeight,
		bItalic, bUnderline, bStrikeOut, lCharSet, lOutPrecision, lClipPrecision, lQuality,
		lPitchAndFamily, strFaceName);

	m_mapFont.insert(make_pair(strKey, pFont));

	return pFont;
}
