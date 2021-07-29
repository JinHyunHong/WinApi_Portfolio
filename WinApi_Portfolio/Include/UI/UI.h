#pragma once

#include "../Game.h"

class CUI
{
	DECLARE_REFERENCE_COUNT();

private:
	friend class CLayer;

private:
	CUI();
	~CUI();
};

