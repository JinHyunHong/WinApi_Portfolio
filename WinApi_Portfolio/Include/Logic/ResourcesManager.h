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
	unordered_map<string, HFONT>		   m_mapFont;

public:
	CTexture* GetBackBuffer()	const;

public:
	CTexture* LoadTexture(const string& strKey, const wchar_t* pFileName, const string& strPathKey = TEXTURE_PATH);
	CTexture* FindTexture(const string& strKey);
	bool EraseTexture(const string& strKey);


public:
	// 화면에 출력할때는 DrawText로 해야한다.
	HFONT AddFont(const string& strKey, int iHeight, int iWidth, int iEscapement, int iOrientation, int iWeight,
		DWORD bItalic, DWORD bUnderline, DWORD bStrikeOut, DWORD lCharSet, DWORD lOutPrecision, DWORD lClipPrecision, DWORD lQuality,
		DWORD lPitchAndFamily, LPCSTR strFaceName);
	HFONT FindFont(const string& strKey);

public:
	bool Init(HINSTANCE hInst, HDC hDC);
	
};

