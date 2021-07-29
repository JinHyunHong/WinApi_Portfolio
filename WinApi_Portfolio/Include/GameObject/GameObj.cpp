#include "GameObj.h"

list<CGameObj*> CGameObj::m_ObjList;

CGameObj::CGameObj()
{
}

CGameObj::CGameObj(const CGameObj& GameObj) :
    CObj(GameObj)
{
}

CGameObj* CGameObj::FindGameObj(const string& strTag)
{
    list<CGameObj*>::iterator iter;
    list<CGameObj*>::iterator iterEnd = m_ObjList.end();

    for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
    {
        if ((*iter)->GetTag() == strTag)
        {
            return (*iter);
        }
    }

    return NULL;
}

bool CGameObj::DeleteGameObj(const string& strTag)
{
    list<CGameObj*>::iterator iter;
    list<CGameObj*>::iterator iterEnd = m_ObjList.end();

    for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
    {
        if ((*iter)->GetTag() == strTag)
        {
            SAFE_RELEASE((*iter));
            return true;
        }
    }

    return false;
}

void CGameObj::DeleteGameObj()
{
    Safe_Release_VecList(m_ObjList);
}

bool CGameObj::Init()
{
    return true;
}

void CGameObj::Input(float fDeltaTime)
{
    CObj::Input(fDeltaTime);
}

int CGameObj::Update(float fDeltaTime)
{
    CObj::Update(fDeltaTime);
    return 0;
}

void CGameObj::Collision(float fDeltaTime)
{
    CObj::Collision(fDeltaTime);
}

int CGameObj::LateUpdate(float fDeltaTime)
{
    CObj::LateUpdate(fDeltaTime);
    return 0;
}

void CGameObj::Render(HDC hDC, float fDeltaTime)
{
    CObj::Render(hDC, fDeltaTime);
}
