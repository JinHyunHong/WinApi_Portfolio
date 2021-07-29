#pragma once
#include "../Game.h"

class CTexture
{
    DECLARE_REFERENCE_COUNT();

private:
    friend class CResourcesManager;

private:
    CTexture();
    CTexture(const CTexture& tex);
    ~CTexture();

private:
    HBITMAP     m_hOldBitMap;
    HBITMAP     m_hBitMap;
    BITMAP      m_tInfo;
    COLORREF    m_tColorKey;
    bool        m_bColorKeyEnable;
    HDC         m_hMemDC;
    wstring     m_strFileName;
    string      m_strPathKey;

public:
    long GetWidth() const
    {
        return m_tInfo.bmWidth;
    }

    long GetHeight()    const
    {
        return m_tInfo.bmHeight;
    }

    void SetColorKey(unsigned char r, unsigned char g,
        unsigned char b);

    void SetColorKey(COLORREF colorKey);

    COLORREF GetColorKey()  const
    {
        return m_tColorKey;
    }

    bool GetColorKeyEnable()    const
    {
        return m_bColorKeyEnable;
    }

    bool LoadTexture(HINSTANCE hInst, HDC hDC,
        const wchar_t* pFileName,
        const string& strPathKey = TEXTURE_PATH);

    HDC GetDC() const
    {
        return m_hMemDC;
    }

};

