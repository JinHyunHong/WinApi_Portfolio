#include "Obj.h"


CObj::CObj()	:
	m_bLife(true),
	m_bEnable(true)
{
	DEFINITION_REFERENCE_COUNT();
}

CObj::CObj(const CObj& obj)
{
	m_strTag = obj.m_strTag;
}

CObj::~CObj()
{
}


bool CObj::Init()
{
	return true;
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
