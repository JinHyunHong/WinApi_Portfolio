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
	int				m_iSecondLimit;
	int				m_iSecond;
	float			m_fDeltaSumTime;
	class CUIPanel* m_pTimerPanel[TIMER_MAX_PANEL];
	CUIPanel*		m_pPlayerHP[PT_END];
	CUIPanel*		m_pPlayerGuage[PT_END];
	class CPlayer*  m_pPlayer;
	class CEnemy*	m_pEnemy;


public:
	virtual bool Init();
	virtual int Update(float fDeltaTime);
};

