#pragma once

#include "../Game.h"

class CResourcesManager
{
	DECLARE_SINGLE(CResourcesManager);
	
private:
	unordered_map<string, class CTexture*>								  m_mapTex;
	HINSTANCE														      m_hInst;
	HDC																      m_hDC;
	CTexture*															  m_pBackBuffer;
	unordered_map<string, HFONT>										  m_mapFont;
	// ĳ���� ���ý� ������Ʈ�� �ش� ĳ���� �ִϸ��̼� ������ ����
	// �� ĳ���� ��������Ʈ�� �ִϸ��̼� ������ ������ �ִ´�.
	class CAnimation*													  m_AnimationList[WCT_END];

public:
	CTexture* GetBackBuffer()	const;

public:
	CTexture* LoadTexture(const string& strKey, const wchar_t* pFileName, const string& strPathKey = TEXTURE_PATH);
	CTexture* FindTexture(const string& strKey);
	bool EraseTexture(const string& strKey);

public:
	CAnimation* CreateAnimation(WORLD_CHARACTER_TYPE eAnimationType);
	CAnimation* GetAnimation(WORLD_CHARACTER_TYPE eAnimationType);
	bool AddAnimationClip(WORLD_CHARACTER_TYPE eAnimationType, const string& strKey, ANIMATION_TYPE eType, ANIMATION_OPTION eOption, float fAnimationLimitTime,
		int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY, int iLengthX, int iLengthY, float fOptionLimitTime,
		const string& strTexKey, const wchar_t* pFileName, const string& strPathKey = TEXTURE_PATH);
	bool AddAnimationClip(WORLD_CHARACTER_TYPE eAnimationType, const string& strKey, ANIMATION_TYPE eType, ANIMATION_OPTION eOption, float fAnimationLimitTime,
		int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY, int iLengthX, int iLengthY, float fOptionLimitTime,
		const string& strTexKey, const vector<wstring>& vecFileName, const string& strPathKey = TEXTURE_PATH);
	bool SetAniamtionColorKey(WORLD_CHARACTER_TYPE eAnimationType, const string& strClip, unsigned char r, unsigned char g, unsigned char b);


public:
	// ȭ�鿡 ����Ҷ��� DrawText�� �ؾ��Ѵ�.
	HFONT AddFont(const string& strKey, int iHeight, int iWidth, int iEscapement, int iOrientation, int iWeight,
		DWORD bItalic, DWORD bUnderline, DWORD bStrikeOut, DWORD lCharSet, DWORD lOutPrecision, DWORD lClipPrecision, DWORD lQuality,
		DWORD lPitchAndFamily, LPCSTR strFaceName);
	HFONT FindFont(const string& strKey);

public:
	bool Init(HINSTANCE hInst, HDC hDC);
	
};

