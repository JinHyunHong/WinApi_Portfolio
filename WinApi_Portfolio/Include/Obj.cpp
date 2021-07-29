#include "Obj.h"


CObj::CObj()	:
	m_bLife(true)
{
	DEFINITION_REFERENCE_COUNT();
}

CObj::CObj(const CObj& obj)
{
	m_strTag = obj.m_strTag;
	m_tSize = obj.m_tSize;
}

bool CObj::Init()
{
	return false;
}

void CObj::Input(float fDeltaTime)
{
}

int CObj::Update(float fDeltaTime)
{
	return 0;
}

void CObj::Collision(float fDeltaTime)
{
}

int CObj::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CObj::Render(HDC hDC, float fDeltaTime)
{
}
