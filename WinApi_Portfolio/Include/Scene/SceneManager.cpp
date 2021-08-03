#include "SceneManager.h"
#include "Scene.h"
#include "GameScene.h"

DEFINITION_SINGLE(CSceneManager)

CSceneManager::CSceneManager()
{
	m_pScene[ST_CURRENT] = NULL;
	m_pScene[ST_NEXT] = NULL;
}

CSceneManager::~CSceneManager()
{
	SAFE_DELETE(m_pScene[ST_CURRENT]);
	SAFE_DELETE(m_pScene[ST_NEXT]);
}

void CSceneManager::ChangeScene()
{
	if (m_pScene[ST_CURRENT])
	{
		SAFE_DELETE(m_pScene[ST_CURRENT]);
	}

	m_pScene[ST_CURRENT] = m_pScene[ST_NEXT];
	m_pScene[ST_NEXT] = NULL;
}

CScene* CSceneManager::GetScene(SCENE_TRANSITION eType)
{
	return m_pScene[eType];
}

CLayer* CSceneManager::FindSceneLayer(SCENE_TRANSITION eType, const string& strTag)
{
	CScene* pScene = GetScene(eType);

	return pScene->FindLayer(strTag);
}

CLayer* CSceneManager::CreateSceneLayer(SCENE_TRANSITION eType, const string& strTag, int iZOrder)
{
	CScene* pScene = GetScene(eType);

	return pScene->CreateLayer(strTag, iZOrder);
	return nullptr;
}

bool CSceneManager::Init()
{
	CreateScene<CGameScene>(ST_CURRENT);
	// 씬을 여기서 만들어준다.
	return true;
}

void CSceneManager::Input(float fDeltaTime)
{
	m_pScene[ST_CURRENT]->Input(fDeltaTime);
}

int CSceneManager::Update(float fDeltaTime)
{
	m_pScene[ST_CURRENT]->Update(fDeltaTime);
	return 0;
}

int CSceneManager::LateUpdate(float fDeltaTime)
{
	m_pScene[ST_CURRENT]->LateUpdate(fDeltaTime);
	return 0;
}

void CSceneManager::Collision(float fDeltaTime)
{
	m_pScene[ST_CURRENT]->Collision(fDeltaTime);
}

void CSceneManager::Render(HDC hDC, float fDeltaTime)
{
	m_pScene[ST_CURRENT]->Render(hDC, fDeltaTime);
}
