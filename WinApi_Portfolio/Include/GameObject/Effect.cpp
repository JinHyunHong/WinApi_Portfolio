#include "Effect.h"
#include "../Logic/ResourcesManager.h"
#include "../Animation/Animation.h"

CEffect::CEffect()	:
	m_pObj(NULL)
{
}

CEffect::CEffect(const CEffect& effect)	:
	CStaticObj(effect)
{
}

CEffect::~CEffect()
{
}

bool CEffect::Init()
{
	m_pAnimation = GET_SINGLE(CResourcesManager)->GetAnimation(RT_EFFECT)->Clone();
	m_pAnimation->SetObj(this);

	return true;
}

void CEffect::Input(float fDeltaTime)
{
	CStaticObj::Input(fDeltaTime);
}

int CEffect::Update(float fDeltaTime)
{
	CStaticObj::Update(fDeltaTime);
	return 0;
}

void CEffect::Collision(float fDeltaTime)
{
	CStaticObj::Collision(fDeltaTime);
}

int CEffect::LateUpdate(float fDeltaTime)
{
	CStaticObj::LateUpdate(fDeltaTime);
	return 0;
}

void CEffect::Render(HDC hDC, float fDeltaTime)
{
	CStaticObj::Render(hDC, fDeltaTime);
}
