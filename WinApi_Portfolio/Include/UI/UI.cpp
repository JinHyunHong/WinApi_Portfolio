#include "UI.h"
#include "../Texture/Texture.h"
#include "../Animation/Animation.h"

list<CUI*> CUI::m_ObjList;

CUI::CUI()
{
}

CUI::CUI(const CUI& ui) :
    CGraphicObj(ui)
{
}

CUI::~CUI()
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
    return true;
}

void CUI::Input(float fDeltaTime)
{
    CGraphicObj::Input(fDeltaTime);
}

int CUI::Update(float fDeltaTime)
{
    CGraphicObj::Update(fDeltaTime);
    return 0;
}

void CUI::Collision(float fDeltaTime)
{
    CGraphicObj::Collision(fDeltaTime);
}

int CUI::LateUpdate(float fDeltaTime)
{
    CGraphicObj::LateUpdate(fDeltaTime);
    return 0;
}

void CUI::Render(HDC hDC, float fDeltaTime)
{
    list<CCollider*>::iterator iter;
    list<CCollider*>::iterator iterEnd = m_ColliderList.end();

    for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
    {
        if (!(*iter)->GetLife())
        {
            SAFE_RELEASE((*iter));
            iter = m_ColliderList.erase(iter);
            iterEnd = m_ColliderList.end();
            continue;
        }

        (*iter)->Render(hDC, fDeltaTime);
    }

    if (m_pTexture)
    {
        POSITION tPos = m_tPos - m_tSize * m_tPivot;
        

        if (m_pTexture->GetColorKeyEnable())
        {
            TransparentBlt(hDC, tPos.x, tPos.y, m_tSize.x, m_tSize.y,
                m_pTexture->GetDC(), m_tImageOffset.x, m_tImageOffset.y, m_tSize.x, m_tSize.y, m_pTexture->GetColorKey());
        }

        else
        {
            BitBlt(hDC, tPos.x, tPos.y, m_tSize.x,
                m_tSize.y, m_pTexture->GetDC(), m_tImageOffset.x, m_tImageOffset.y, SRCCOPY);
        }
    }
}