#include "MoveObj.h"

CMoveObj::CMoveObj()	:
	m_fSpeed(200.f),
	m_fForce(0.f),
	m_fForceOrigin(0.f),
	m_bJump(false),
	m_bFalling(false),
	m_eDir(DIR_NONE),
	m_fAngle(0.f),
	m_fGravityTime(0.f),
	m_bPhysics(false)
{
}

CMoveObj::CMoveObj(const CMoveObj& Obj) :
	CGameObj(Obj)
{
	m_fSpeed = Obj.m_fSpeed;
	m_fForceOrigin = Obj.m_fForceOrigin; 
	m_bPhysics = Obj.m_bPhysics;
}

void CMoveObj::Jump()
{
	if (!m_bFalling)
	{
		m_bJump = true;
		m_fForce = m_fForceOrigin;
	}
}

void CMoveObj::MoveToX(float x)
{
	m_tPos.x += x;
}

void CMoveObj::MoveToX(float x, float fDeltaTime)
{
	m_tPos.x += x * fDeltaTime;
}

void CMoveObj::MoveToXSpeed(float fDeltaTime)
{
	m_tPos.x += m_fSpeed * fDeltaTime * m_eDir;
}

void CMoveObj::MoveToAngle(float fDeltaTime)
{
	m_tPos.x += cosf(m_fAngle) * m_fSpeed * fDeltaTime; 
	m_tPos.y += sinf(m_fAngle) * m_fSpeed * fDeltaTime;
}

void CMoveObj::MoveToY(float y)
{
	m_tPos.y += y;
}

void CMoveObj::MoveToY(float y, float fDeltaTime)
{
	m_tPos.y += y * fDeltaTime;
}

void CMoveObj::MoveToYSpeed(float fDeltaTime)
{
	m_tPos.y += m_fSpeed * fDeltaTime * m_eDir;
}

bool CMoveObj::Init()
{
	return true;
}

void CMoveObj::Input(float fDeltaTime)
{
	CGameObj::Input(fDeltaTime);
}

int CMoveObj::Update(float fDeltaTime)
{
	if (m_bPhysics)
	{
		m_fGravityTime += fDeltaTime;

		m_fForce -= (GRAVITY * m_fGravityTime);

		m_tPos.y -= m_fForce * fDeltaTime;
	}

	CGameObj::Update(fDeltaTime);
	return 0;
}

void CMoveObj::Collision(float fDeltaTime)
{
	CGameObj::Collision(fDeltaTime);
}

int CMoveObj::LateUpdate(float fDeltaTime)
{
	CGameObj::LateUpdate(fDeltaTime);
	return 0;
}

void CMoveObj::Render(HDC hDC, float fDeltaTime)
{
	CGameObj::Render(hDC, fDeltaTime);
}
