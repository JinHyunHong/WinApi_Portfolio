#pragma once
#include "../Obj.h"
#include "../Game.h"
#include "../Collider/Collider.h"

class CGraphicObj :
    public CObj
{
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

public:
	void SetTexture(class CTexture* pTex);
	void SetTexture(const string& strKey, const wchar_t* pFileName, const string& strPathKey = TEXTURE_PATH);
	void SetColorKey(unsigned int r, unsigned int g, unsigned int b);
	void SetColorKey(COLORREF rgb);

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

