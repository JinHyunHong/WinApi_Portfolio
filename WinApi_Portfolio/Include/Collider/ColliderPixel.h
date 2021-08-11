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
	PIXEL	      m_tCollRGB;

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

	PIXEL GetCollRGB()	const
	{
		return m_tCollRGB;
	}

	void SetCollRGB(PIXEL rgb)
	{
		m_tCollRGB = rgb;
	}

	void SetCollRGB(unsigned int r, unsigned int g, unsigned int b)
	{
		SetCollRGB(PIXEL(r, g, b));
	}

public:
	bool SetPixelInfo(const char* pFileName,
		const string& strPathKey = TEXTURE_PATH);
	bool SetPixelInfo(const string& strFullPath);

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual bool Collision(CCollider* pDest);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

