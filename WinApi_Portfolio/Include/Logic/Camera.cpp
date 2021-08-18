#include "Camera.h"
#include "../GameObject/GameObj.h"

DEFINITION_SINGLE(CCamera);

CCamera::CCamera()	:
	m_pTargetObj(NULL)
{

}

CCamera::~CCamera()
{

}

bool CCamera::Init(SCREENSIZE tClientRS, 
	SCREENSIZE tWorldRS)
{
	m_tPos = POSITION(0.f, 0.f);
	m_tClientRS = tClientRS;
	m_tWorldRS = tWorldRS;
	m_tPivot = POSITION(0.5, 0.5);


	return true;
}

void CCamera::Scroll(float x, float y)
{
	m_tPos.y += x;
	m_tPos.y += y;

	if (m_tPos.x < 0)
		m_tPos.x = 0;

	else if (m_tPos.x > m_tWorldRS.iWidth - m_tClientRS.iWidth)
		m_tPos.x = m_tWorldRS.iWidth - m_tClientRS.iWidth;

	if (m_tPos.y < 0)
		m_tPos.y = 0;

	else if (m_tPos.y > m_tWorldRS.iHeight - m_tClientRS.iHeight)
		m_tPos.y = m_tWorldRS.iHeight - m_tClientRS.iHeight;
}

void CCamera::Update(float fDeltaTime)
{
	POSITION tPos = m_pTargetObj->GetPos();
	POSITION tSize = m_pTargetObj->GetSize();
	POSITION tPivot = m_pTargetObj->GetPivot();

	float fL = tPos.x - tPivot.x * tSize.x;
	float fR = fL + tSize.x;
	float fT = tPos.y - tPivot.y * tSize.y;
	float fB = fT + tSize.y;
	
	float fLArea = m_tClientRS.iWidth * tPivot.x;
	float fRArea = m_tClientRS.iWidth - fLArea;
	float fTArea = m_tClientRS.iHeight * tPivot.y;
	float fBArea = m_tClientRS.iHeight - fTArea;

	if (tPos.x < fLArea)
		m_tPos.x = 0.f;

	else if (tPos.x > m_tWorldRS.iWidth - fRArea)
		m_tPos.x = m_tWorldRS.iWidth - m_tClientRS.iWidth;

	else
		m_tPos.x = tPos.x - m_tClientRS.iWidth * m_tPivot.x;

	if (tPos.y < fTArea)
		m_tPos.y = 0.f;

	else if (tPos.y > m_tWorldRS.iHeight - fBArea)
		m_tPos.y = m_tWorldRS.iHeight - m_tClientRS.iHeight;

	else
		m_tPos.y = tPos.y - m_tClientRS.iHeight * m_tPivot.y;
}
