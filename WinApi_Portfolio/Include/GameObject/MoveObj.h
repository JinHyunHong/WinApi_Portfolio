#pragma once
#include "GameObj.h"
class CMoveObj :
    public CGameObj
{
protected:
	CMoveObj();
	CMoveObj(const CMoveObj& Obj);
	virtual ~CMoveObj() = 0;

protected:
	float m_fSpeed;
	float m_fForce;
	float m_fForceOrigin;
	bool  m_bJump;
	bool  m_bFalling;
	DIR	  m_eDir;
	float m_fGravityTime;
	bool  m_bPhysics;
	float m_fAngle;

protected:
	void Jump();
	void MoveToX(float x);
	void MoveToX(float x, float fDeltaTime);
	void MoveToXSpeed(float fDeltaTime);
	void MoveToAngle(float fDeltaTime);
	void MoveToY(float y);
	void MoveToY(float y, float fDeltaTime);	
	void MoveToYSpeed(float fDeltaTime);

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

