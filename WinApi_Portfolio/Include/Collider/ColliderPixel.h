#pragma once
#include "Collider.h"
class CColliderPixel :
    public CCollider
{
private:
	friend class CGraphicObj;
	friend class CColliderManager;

private:
	CColliderPixel();
	CColliderPixel(const CColliderPixel& pixel);
	virtual ~CColliderPixel();

private:
	vector<PIXEL> m_vecPixel;
	int			  m_iWidth;
	int			  m_iHeight;

private:
	string		  m_strFileName;
	string		  m_strPathKey;

public:
	const vector<PIXEL>& GetPixel()	const
	{
		return m_vecPixel;
	}

	int	GetWidth()	const
	{
		return m_iWidth;
	}

	int	GetHeight()	const
	{
		return m_iHeight;
	}

public:
	bool SetPixelInfo(const char* pFileName,
		const string& strPathKey = TEXTURE_PATH);

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual bool Collision(CCollider* pDest);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

