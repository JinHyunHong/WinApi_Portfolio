#include "ColliderPixel.h"
#include "../Logic/FileManager.h"
#include "../Logic/Math.h"
#include "ColliderPoint.h"
#include "ColliderRect.h"

CColliderPixel::CColliderPixel()	:
	m_iWidth(0),
	m_iHeight(0)
{
}

CColliderPixel::CColliderPixel(const CColliderPixel& pixel)	:
	CCollider(pixel)
{
}

CColliderPixel::~CColliderPixel()
{
}

bool CColliderPixel::SetPixelInfo(const char* pFileName, const string& strPathKey)
{
	m_strFileName = pFileName;
	m_strPathKey = strPathKey;

	string strFullPath;
	const char* pPath = GET_SINGLE(CFileManager)->FindPathMultiByte(strPathKey);

	if (pPath)
	{
		strFullPath = pPath;
		strFullPath += m_strFileName;

		FILE* pFile = NULL;

		//c_str는 string을 const char*로 리턴한다.
		fopen_s(&pFile, strFullPath.c_str(), "rb");

		if (!pFile)
			return false;

		BITMAPFILEHEADER fh;
		BITMAPINFOHEADER ih;

		fread(&fh, sizeof(fh), 1, pFile);
		fread(&ih, sizeof(ih), 1, pFile);

		m_iWidth = ih.biWidth;
		m_iHeight = ih.biHeight;

		m_vecPixel.clear();

		m_vecPixel.resize(m_iWidth * m_iHeight);
		
		fread(&m_vecPixel[0], sizeof(PIXEL), m_vecPixel.size(), pFile);

		PPIXEL pPixelArr = new PIXEL[m_iWidth];

		for (int i = 0; i < m_iHeight / 2; ++i)
		{
			memcpy(pPixelArr, &m_vecPixel[i * m_iWidth], sizeof(PIXEL) * m_iWidth);
			memcpy(&m_vecPixel[i * m_iWidth], &m_vecPixel[(m_iHeight - i - 1) * m_iWidth],
				sizeof(PIXEL) * m_iWidth);
			memcpy(&m_vecPixel[(m_iHeight - i - 1) * m_iWidth], pPixelArr,
				sizeof(PIXEL) * m_iWidth);
		}

		delete[] pPixelArr;

		fclose(pFile);

		return true;
	}
}

bool CColliderPixel::Init()
{
	m_eType = CT_PIXEL;

	return true;
}

void CColliderPixel::Input(float fDeltaTime)
{
	CCollider::Input(fDeltaTime);
}

int CColliderPixel::Update(float fDeltaTime)
{
	CCollider::Update(fDeltaTime);
	return 0;
}

bool CColliderPixel::Collision(CCollider* pDest)
{
	switch (pDest->GetColliderType())
	{
	case CT_POINT:
		return CMath::PointToPixel(((CColliderPoint*)pDest)->GetPos(), m_vecPixel, m_iWidth, m_iHeight);
	case CT_RECT:
		return CMath::RectToPixel(((CColliderRect*)pDest)->GetWorldInfo(), m_vecPixel, m_iWidth, m_iHeight);
	}

	return false;
}

int CColliderPixel::LateUpdate(float fDeltaTime)
{
	CCollider::LateUpdate(fDeltaTime);

	return 0;
}

void CColliderPixel::Render(HDC hDC, float fDeltaTime)
{
	CCollider::Render(hDC, fDeltaTime);
}
