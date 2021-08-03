#pragma once

#include "Game.h"

class CObj
{
	DECLARE_REFERENCE_COUNT();

protected:
	CObj();
	CObj(const CObj& obj);
	virtual ~CObj();

protected:
	string					m_strTag;
	bool					m_bLife;

public:
	string GetTag()		const
	{
		return m_strTag;
	}

	void SetTag(const string& strTag)
	{
		m_strTag = strTag;
	}

	bool GetLife()	const
	{
		return m_bLife;
	}

	void Die()
	{
		m_bLife = false;
	}

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);

};

