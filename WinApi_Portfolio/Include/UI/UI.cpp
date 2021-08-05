#include "UI.h"
#include "../Texture/Texture.h"
#include "../Animation/Animation.h"
#include "../Logic/ResourcesManager.h"

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

    // 텍스트 출력
    vector<PUITEXTINFO>::iterator iterText;
    vector<PUITEXTINFO>::iterator iterTextEnd = m_vecText.end();

    for (iterText = m_vecText.begin(); iterText != iterTextEnd; ++iterText)
    {
        if (!(*iterText)->strText.empty())
        {
            HFONT hFont = GET_SINGLE(CResourcesManager)->FindFont((*iterText)->strFontName);
            m_hOldFont = (HFONT)SelectObject(hDC, hFont);
            SetTextColor(hDC, RGB((*iterText)->r, (*iterText)->g, (*iterText)->b));
            SetBkMode(hDC, (*iterText)->iMode);
            //TextOutA(hDC, m_tPos.x + (*iterText)->tPos.x, m_tPos.y + (*iterText)->tPos.y,
            //    (*iterText)->strText.c_str(), (*iterText)->strText.length());
            LOGFONT lf = {0};
            GetObject(hFont, sizeof(LOGFONT), &lf);
            RECT tRC = { (*iterText)->tPos.x, (*iterText)->tPos.y, (*iterText)->tPos.x + m_tSize.x ,
                (*iterText)->tPos.y + m_tSize.y};
            DrawTextA(hDC, (*iterText)->strText.c_str(), (*iterText)->strText.length(), &tRC, (*iterText)->iFormat);
        }

    }
}

PUITEXTINFO CUI::FindUIText(const string& strText)
{
    vector<PUITEXTINFO>::iterator iter;
    vector<PUITEXTINFO>::iterator iterEnd = m_vecText.end();

    for (iter = m_vecText.begin(); iter != iterEnd; ++iter)
    {
        if ((*iter)->strText.c_str() == strText)
            return (*iter);
    }

    return NULL;
}

void CUI::AddUIText(const string& strText, const POSITION& pos, const string& strFontName, 
    unsigned int r, unsigned int g, unsigned int b, int iMode, unsigned int iFormat)
{
    PUITEXTINFO pTextInfo = FindUIText(strText);

    if (pTextInfo)
        return;

    POSITION tPos = m_tPos - m_tSize * m_tPivot;

    pTextInfo = new UITEXTINFO;
    pTextInfo->strText = strText;
    pTextInfo->tPos = tPos + pos;
    pTextInfo->strFontName = strFontName;
    pTextInfo->iMode = iMode;
    pTextInfo->iFormat = iFormat;

    m_vecText.push_back(pTextInfo);
}

void CUI::AddUIText(const string& strText, float x, float y, const string& strFontName, 
    unsigned int r, unsigned int g, unsigned int b, int iMode, unsigned int iFormat)
{
    PUITEXTINFO pTextInfo = FindUIText(strText);

    if (pTextInfo)
        return;

    POSITION tPos = m_tPos - m_tSize * m_tPivot;

    pTextInfo = new UITEXTINFO;
    pTextInfo->strText = strText;
    pTextInfo->tPos.x = tPos.x + x;
    pTextInfo->tPos.y = tPos.y + y;
    pTextInfo->strFontName = strFontName;
    pTextInfo->r = r;
    pTextInfo->g = g;
    pTextInfo->b = b;
    pTextInfo->iMode = iMode;
    pTextInfo->iFormat = iFormat;

    m_vecText.push_back(pTextInfo);
}