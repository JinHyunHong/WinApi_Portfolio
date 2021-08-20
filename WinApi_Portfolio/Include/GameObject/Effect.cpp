#include "Effect.h"
#include "../Logic/ResourcesManager.h"
#include "../Animation/Animation.h"
#include "../GameObject/MoveObj.h"

CEffect::CEffect()	:
	m_pObj(NULL),
	m_eType(ET_HURT_SMALL)
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

void CEffect::SetType(EFFECT_TYPE eType)
{
	m_eType = eType;
	
	switch (m_eType)
	{
	case ET_HURT_SMALL:
		m_strClipName = "SmallHurtEffect";
		break;
	
	case ET_HURT_MEDIUM:
		m_strClipName = "MediumHurtEffect";
		break;
	
	case ET_HURT_BIG:
		m_strClipName = "BigHurtEffect";
		break;

	case ET_BENIMARU_SPECIAL1:
		m_strClipName = "BenimaruSpecialEffect1";
		break;

	case ET_BENIMARU_SPECIAL1_1:
		m_strClipName = "BenimaruSpecialEffect1_1";
		break;
	}
	
	if (!m_strClipName.empty())
	{
		m_pAnimation->ChangeClip(m_strClipName);
	}
}
