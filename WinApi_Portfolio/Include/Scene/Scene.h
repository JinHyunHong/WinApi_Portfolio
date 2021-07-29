#pragma once

#include "../Game.h"
#include "Layer.h"

class CScene
{
private:
	friend class CSceneManager;

protected:
	CScene();
	virtual ~CScene() = 0;

protected:
	list<class CLayer*> m_LayerList;

public:
	CLayer* CreateLayer(string strTag, int iZOrder)
	{
		CLayer* pLayer = new CLayer;

		if (!pLayer->Init())
		{
			SAFE_DELETE(pLayer);
			return;
		}

		pLayer->SetTag(strTag);
		pLayer->SetScene(this);
		m_LayerList.push_back(pLayer);
		m_LayerList.sort(LayerSort);
		return pLayer;
	}

	CLayer* FindLayer(const string& strTag);

private:
	bool LayerSort(const CLayer* pLayerSrc, const CLayer* pLayerDest);

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

