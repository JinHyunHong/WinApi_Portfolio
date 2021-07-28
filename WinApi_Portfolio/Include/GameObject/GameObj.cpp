#include "GameObj.h"

list<CGameObj*> CGameObj::m_ObjList;

CGameObj::CGameObj()
{
    DEFINITION_REFERENCE_COUNT();
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
}

int CGameObj::Update(float fDeltaTime)
{
    return 0;
}

void CGameObj::Collision(float fDeltaTime)
{
}

int CGameObj::LateUpdate(float fDeltaTime)
{
    return 0;
}

void CGameObj::Render(float fDeltaTime)
{
}
