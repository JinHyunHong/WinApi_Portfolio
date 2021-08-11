#include "StaticObj.h"

CStaticObj::CStaticObj()
{
}

CStaticObj::CStaticObj(const CStaticObj& Obj)   :
    CGameObj(Obj)
{
}

CStaticObj::~CStaticObj()
{
}

bool CStaticObj::Init()
{
    return true;
}

void CStaticObj::Input(float fDeltaTime)
{
    CGameObj::Input(fDeltaTime);
}

int CStaticObj::Update(float fDeltaTime)
{
    CGameObj::Update(fDeltaTime);
    return 0;
}

void CStaticObj::Collision(float fDeltaTime)
{
    CGameObj::Collision(fDeltaTime);
}

int CStaticObj::LateUpdate(float fDeltaTime)
{
    CGameObj::LateUpdate(fDeltaTime);
    return 0;
}

void CStaticObj::Render(HDC hDC, float fDeltaTime)
{
    CGameObj::Render(hDC, fDeltaTime);
}
