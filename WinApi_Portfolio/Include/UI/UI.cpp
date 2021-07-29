#include "UI.h"

list<CUI*> CUI::m_ObjList;

CUI::CUI()
{
}

CUI::CUI(const CUI& ui) :
    CObj(ui)
{
}

CUI* CUI::FindUIObj(const string& strTag)
{
    list<CUI*>::iterator iter;
    list<CUI*>::iterator iterEnd = m_ObjList.end();

    for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
    {
        if ((*iter)->GetTag() == strTag)
        {
            return (*iter);
        }
    }

    return NULL;
}

bool CUI::DeleteUIObj(const string& strTag)
{
    list<CUI*>::iterator iter;
    list<CUI*>::iterator iterEnd = m_ObjList.end();

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

void CUI::DeleteUIObj()
{
    Safe_Release_VecList(m_ObjList);
}

bool CUI::Init()
{
    return false;
}

void CUI::Input(float fDeltaTime)
{
    CObj::Input(fDeltaTime);
}

int CUI::Update(float fDeltaTime)
{
    CObj::Update(fDeltaTime);
    return 0;
}

void CUI::Collision(float fDeltaTime)
{
    CObj::Collision(fDeltaTime);
}

int CUI::LateUpdate(float fDeltaTime)
{
    CObj::LateUpdate(fDeltaTime);
    return 0;
}

void CUI::Render(HDC hDC, float fDeltaTime)
{
    CObj::Render(hDC, fDeltaTime);
}