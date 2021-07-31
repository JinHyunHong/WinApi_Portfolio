#include "Texture.h"
#include "../Logic/FileManager.h"

CTexture::CTexture()
{
    DEFINITION_REFERENCE_COUNT();
}

CTexture::CTexture(const CTexture& tex) :
    m_hOldBitMap(NULL),
    m_hBitMap(NULL),
    m_bColorKeyEnable(false),
    m_tColorKey(RGB(255, 0, 255))
{
}

CTexture::~CTexture()
{
    SelectObject(m_hMemDC, m_hOldBitMap);
    DeleteObject(m_hBitMap);
    DeleteDC(m_hMemDC);
}


void CTexture::SetColorKey(unsigned char r, unsigned char g, unsigned char b)
{
    m_bColorKeyEnable = true;
    m_tColorKey = RGB(r, g, b);
}

void CTexture::SetColorKey(COLORREF colorKey)
{
    m_bColorKeyEnable = true;
    m_tColorKey = colorKey;
}

bool CTexture::LoadTexture(HINSTANCE hInst, HDC hDC, const wchar_t* pFileName, const string& strPathKey)
{
    m_strFileName = pFileName;
    m_strPathKey = strPathKey;

    m_hMemDC = CreateCompatibleDC(hDC);

    const wchar_t* pPath = GET_SINGLE(CFileManager)->FindPath(strPathKey);

    wstring strFullPath;

    if (!pPath)
        return false;

    strFullPath = pPath;

    strFullPath += pFileName;

    m_hBitMap = (HBITMAP)LoadImage(hInst, strFullPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    m_hOldBitMap = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);
    GetObject(m_hBitMap, sizeof(m_tInfo), &m_tInfo);
        

    return true;
}
