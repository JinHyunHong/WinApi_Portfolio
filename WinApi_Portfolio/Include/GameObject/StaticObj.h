#pragma once
#include "GameObj.h"
class CStaticObj :
    public CGameObj
{
protected:
	CStaticObj();
	CStaticObj(const CStaticObj& Obj);
	virtual ~CStaticObj();

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

