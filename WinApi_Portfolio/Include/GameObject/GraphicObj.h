#pragma once
#include "../Obj.h"
#include "../Collider/Collider.h"

class CGraphicObj :
    public CObj
{
private:
	friend class CScene;

protected:
	CGraphicObj();
	CGraphicObj(const CGraphicObj& graphicobj);
	virtual ~CGraphicObj();

protected:
	class CTexture*			m_pTexture;
	list<CCollider*>		m_ColliderList;
	POSITION				m_tPos;
	POSITION				m_tPivot;
	_SIZE					m_tSize;
	class CAnimation*		m_pAnimation;
	_SIZE					m_tImageOffset;

public:
	POSITION GetPos()		const
	{
		return m_tPos;
	}

	void SetPos(const POSITION& tPos)
	{
		m_tPos = tPos;
	}

	void SetPos(float x, float y)
	{
		m_tPos.x = x;
		m_tPos.y = y;
	}

	POSITION GetPivot()		const
	{
		return m_tPivot;
	}

	void SetPivot(const POSITION& tPivot)
	{
		m_tPivot = tPivot;
	}

	void SetPivot(float x, float y)
	{
		m_tPivot.x = x;
		m_tPivot.y = y;
	}

	_SIZE GetSize()		const
	{
		return m_tSize;
	}

	void SetSize(const _SIZE& tSize)
	{
		m_tSize = tSize;
	}

	void SetSize(float x, float y)
	{
		m_tSize.x = x;
		m_tSize.y = y;
	}

	void ImageOffset(const _SIZE& tOffset)
	{
		m_tImageOffset = tOffset;
	}

	void SetImageOffset(float x, float y)
	{
		m_tImageOffset.x = x;
		m_tImageOffset.y = y;
	}

	class CAnimation* GetAnimation()	const
	{
		if (m_pAnimation)
			return m_pAnimation;

		return NULL;
	}

public:
	void SetTexture(class CTexture* pTex);
	void SetTexture(const string& strKey, const wchar_t* pFileName, const string& strPathKey = TEXTURE_PATH);
	void SetColorKey(unsigned int r, unsigned int g, unsigned int b);
	void SetColorKey(COLORREF rgb);


public:
	class CAnimation* CreateAnimation(const string& strTag);
	bool AddAnimationClip(const string& strName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption, float fAnimationLimitTime,
		int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY, int iLengthX, int iLengthY, float fOptionLimitTime, const string& strTexKey,
		const wchar_t* pFileName, const string& strPathKey = TEXTURE_PATH);
	bool AddAnimationClip(const string& strName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption, float fAnimationLimitTime,
		int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY, int iLengthX, int iLengthY, float fOptionLimitTime, const string& strTexKey,
		const vector<wstring>& vecFileName, const string& strPathKey = TEXTURE_PATH);
	void SetAnimationClipColorKey(const string& strClip, unsigned char r, unsigned char g, unsigned char b);


public:
	const list<CCollider*>& GetColliderList()
	{
		return m_ColliderList;
	}

	bool GetCollisonEmpty()	const
	{
		return m_ColliderList.empty();
	}

	CCollider* GetCollider(const string& strTag);

	template<typename T>
	void AddColliderFunction(const string& strTag, COLLIDER_STATE eState, T* pObj,
		void(T::* pFunc)(CCollider*, CCollider*, float))
	{
		list<CCollider*>::iterator iter;
		list<CCollider*>::iterator iterEnd = m_ColliderList.end();

		for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
		{
			if ((*iter)->GetTag() == strTag)
			{
				(*iter)->AddFunction(eState, pObj, pFunc);
				break;
			}
		}
	}

	template<typename T>
	T* AddCollider(const string& strTag)
	{
		T* pColl = new T;

		pColl->SetObj(this);

		if (!pColl->Init())
		{
			SAFE_RELEASE(pColl);
			return NULL;
		}

		pColl->SetTag(strTag);
		m_ColliderList.push_back(pColl);

		return pColl;
	}

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

