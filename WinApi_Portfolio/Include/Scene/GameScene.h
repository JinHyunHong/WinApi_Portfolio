#pragma once
#include "Scene.h"
class CGameScene :
    public CScene
{
private:
	friend class CSceneManager;

protected:
	CGameScene();
	~CGameScene();

public:
	virtual bool Init();
};

