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
	class CTexture*  m_pTexture;
	list<CCollider*> m_ColliderList;

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

