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
	static list<CUI*>   m_ObjList;
	vector<PUITEXTINFO> m_vecText;
	HFONT				m_hOldFont;

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

		if (pLayer)
		{
			pLayer->AddObj(pUIObj);
		}

		return pUIObj;
	}

	static CUI* FindUIObj(const string& strTag);
	static bool DeleteUIObj(const string& strTag);
	static void DeleteUIObj();

public:
	PUITEXTINFO FindUIText(const string& strText);
	void AddUIText(const string& strText, const POSITION& pos, const string& strFontName,
		unsigned int r, unsigned int g, unsigned int b, int iMode = TRANSPARENT, unsigned int iFormat = DT_CENTER);
	void AddUIText(const string& strText, float x, float y, const string& strFontName,
		unsigned int r, unsigned int g, unsigned int b, int iMode = TRANSPARENT, unsigned int iFormat = DT_CENTER);

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

