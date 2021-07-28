#pragma once

#include "../Game.h"

class CCamera
{
	DECLARE_SINGLE(CCamera);

private:
	POSITION	m_tPos;
	POSITION	m_tPivot;
	SCREENSIZE	m_tClientRS;

public:
	bool Init(SCREENSIZE tClientRS);
	void Update();
};

