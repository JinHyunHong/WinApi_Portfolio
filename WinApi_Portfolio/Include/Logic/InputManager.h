#pragma once
#include "../Game.h"


typedef struct _tagKeyInfo
{
	string strName;
	bool bDown;
	bool bPress;
	bool bUp;
	vector<DWORD> vecKey;

	_tagKeyInfo() :
		bDown(false),
		bPress(false),
		bUp(false)
	{
	}

}KEYINFO, * PKEYINFO;

class CInputManager
{
	DECLARE_SINGLE(CInputManager);

private:
	unordered_map<string, PKEYINFO> m_mapKey;
	PKEYINFO						m_pKeyInfo;
	POINT							m_tMousePos;
	POINT							m_tMouseMove;
	class CMouse*					m_pMouse;

public:
	class CMouse* GetMouse()	const
	{
		return m_pMouse;
	}

	POSITION GetMouseClientPos()	const;
	POSITION GetMouseWorldPos()	const;
	POSITION GetMouseMove()	const;

public:
	bool Init();
	void Update(float fDeltaTime);

public:
	bool GetKeyDown(const string& strKey)	const
	{
		PKEYINFO pKeyInfo = FindKey(strKey);

		if(pKeyInfo)
			return pKeyInfo->bDown;

		return false;
	}
	bool GetKeyPress(const string& strKey)	const
	{
		PKEYINFO pKeyInfo = FindKey(strKey);

		if (pKeyInfo)
			return pKeyInfo->bPress;

		return false;
	}
	bool GetKeyUp(const string& strKey)	const
	{
		PKEYINFO pKeyInfo = FindKey(strKey);

		if (pKeyInfo)
			return pKeyInfo->bUp;

		return false;
	}

public:
	PKEYINFO FindKey(const string& strKey)	const;

public:
	template<typename T>
	bool CreateKey(const T& data)
	{
		if(!m_pKeyInfo)
			m_pKeyInfo = new KEYINFO;

		if (strcmp(typeid(T).name(), "int") == 0 ||
			strcmp(typeid(T).name(), "char") == 0)
		{
			m_pKeyInfo->vecKey.push_back((DWORD)data);
		}

		else
		{
			m_pKeyInfo->strName = data;
			m_mapKey.insert(make_pair(m_pKeyInfo->strName, m_pKeyInfo));
		}


		if (m_pKeyInfo)
			m_pKeyInfo = NULL;
		

		return true;
	}


	template<typename T, typename ... Types>
	bool CreateKey(const T& data, const Types&... arg)
	{
		if (!m_pKeyInfo)
			m_pKeyInfo = new KEYINFO;

		if (strcmp(typeid(T).name(), "int") == 0 ||
			strcmp(typeid(T).name(), "char") == 0)
		{
			m_pKeyInfo->vecKey.push_back((DWORD)data);
		}

		else
		{
			m_pKeyInfo->strName = data;
			m_mapKey.insert(make_pair(m_pKeyInfo->strName, m_pKeyInfo));
		}

		CreateKey(arg...);

		if(m_pKeyInfo)
			m_pKeyInfo = NULL;

		return true;
	}
};

