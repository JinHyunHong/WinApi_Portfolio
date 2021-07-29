#pragma once

#include "../Game.h"

class CResourcesManager
{
	DECLARE_SINGLE(CResourcesManager);
	
private:
	unordered_map<string, class CTexture*> m_mapTex;
	HINSTANCE							   m_hInst;
	HDC									   m_hDC;
	CTexture*							   m_pBackBuffer;

public:
	CTexture* GetBackBuffer()	const;

public:
	CTexture* LoadTexture(const string& strKey, const wchar_t* pFileName, const string& strPathKey = TEXTURE_PATH);
	CTexture* FindTexture(const string& strKey);
	bool EraseTexture(const string& strKey);

public:
	bool Init(HINSTANCE hInst, HDC hDC);
	
};

