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

private:
	int	  m_iSecondLimit;
	int	  m_iSecond;
	float m_fDeltaSumTime;
	class CUIPanel* m_pTimerPanel[TIMER_MAX_PANEL];


public:
	virtual bool Init();
	virtual int Update(float fDeltaTime);
};

