#pragma once

#include "../Scene/Layer.h"
#include "../GameObject/GraphicObj.h"

class CUI	:
	public CGraphicObj
{
protected:
	CUI();
	CUI(const CUI& ui);
	virtual ~CUI();


private:
	static list<CUI*> m_ObjList;

public:
	template<typename T>
	static T* CreateUIObj(const string& strTag, class CLayer* pLayer = NULL)
	{
		T* pUIObj = new T;

		if (!pUIObj->Init())
		{
			SAFE_RELEASE(pUIObj);
			return NULL;
		}

		pUIObj->SetTag(strTag);
		m_ObjList.push_back(pUIObj);
		pLayer->AddObj(pUIObj);
		return pUIObj;
	}

	static CUI* FindUIObj(const string& strTag);
	static bool DeleteUIObj(const string& strTag);
	static void DeleteUIObj();

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

