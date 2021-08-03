#pragma once
#include "../Obj.h"

class CAnimation	:
	public CObj
{
private:
	friend class CGraphicObj;

private:
	CAnimation();
	CAnimation(const CAnimation& anim);
	~CAnimation();

private:
	unordered_map<string, PANIMATIONCLIP> m_mapClip;
	PANIMATIONCLIP						  m_pCurClip;
	string								  m_strCurClip;
	string								  m_strDefaultClip;
	class CGraphicObj*					  m_pGraphicObj;
	bool								  m_bMotionEnd;

public:
	bool GetMotionEnd() const
	{
		return m_bMotionEnd;
	}
public:
	PANIMATIONCLIP GetCurrentClip() const
	{
		return m_pCurClip;
	}
	void SetObj(class CGraphicObj* pGraphicObj)
	{
		m_pGraphicObj = pGraphicObj;
	}

public:
	bool AddClip(const string& strKey, ANIMATION_TYPE eType, ANIMATION_OPTION eOption, float fAnimationLimitTime,
		int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY, int iLengthX, int iLengthY, float fOptionLimitTime,
		const string& strTexKey, const wchar_t* pFileName, const string& strPathKey = TEXTURE_PATH);
	bool AddClip(const string& strKey, ANIMATION_TYPE eType, ANIMATION_OPTION eOption, float fAnimationLimitTime,
		int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY, int iLengthX, int iLengthY, float fOptionLimitTime,
		const string& strTexKey, const vector<wstring>& vecFileName, const string& strPathKey = TEXTURE_PATH);

	void SetClipColorKey(const string& strClip, unsigned char r, unsigned char g, unsigned char b);
	void SetCurrentClip(const string& strCurClip);
	void SetDefaultClip(const string& strDefaultClip);
	void ChangeClip(const string& strClip);
	void ReturnClip();

private:
	PANIMATIONCLIP FindClip(const string& strKey);

public:
	bool Init();
	virtual int	Update(float fDeltaTime);
};

