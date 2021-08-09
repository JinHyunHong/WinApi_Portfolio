#pragma once
#include "../Game.h"

// ��ο� ������ �������ִ� Ŭ����
class CFileManager
{
	DECLARE_SINGLE(CFileManager);

private:
	unordered_map<string, wstring> m_mapPath;
	char						   m_strPath[MAX_PATH];


public:
	bool Init();

public:
	void CreatePath(const string& strKey, const wchar_t* pFileName,
		const char* pBasePath = BASE_PATH);
	const wchar_t* FindPath(const string& strKey);
	const char* FindPathMultiByte(const string& strKey);
};

