#pragma once
#include "../Game.h"

class CSceneManager
{
	DECLARE_SINGLE(CSceneManager);

private:
	class CScene* m_pScene[ST_END];

public:
	template<typename T>
	T* CreateScene(SCENE_TRANSITION eType)
	{
		T* pScene = new T;

		if (!pScene->Init())
		{
			SAFE_DELETE(pScene);
			return NULL;
		}

		switch (eType)
		{		
		case ST_CURRENT:
			SAFE_DELETE(m_pScene[ST_CURRENT]);
			m_pScene[ST_CURRENT] = pScene;
			break;		
		case ST_NEXT:
			SAFE_DELETE(m_pScene[ST_CURRENT]);
			m_pScene[ST_NEXT] = pScene;
			break;
		}

		return pScene;
	}

	void ChangeScene();
	CScene* GetScene(SCENE_TRANSITION eType);
	class CLayer* FindSceneLayer(SCENE_TRANSITION eType, const string& strTag); 
	class CLayer* CreateSceneLayer(SCENE_TRANSITION eType, const string& strTag, int iZOrder);

public:
	bool Init();
	void Input(float fDeltaTime);
	int Update(float fDeltaTime);
	int LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(HDC hDC, float fDeltaTime);
};


