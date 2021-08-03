#include "FileManager.h"

DEFINITION_SINGLE(CFileManager);

CFileManager::CFileManager()
{

}

CFileManager::~CFileManager()
{
}

bool CFileManager::Init()
{
	wchar_t	 strBasePath[MAX_PATH];
	GetModuleFileName(NULL, strBasePath, MAX_PATH);

	for (int i = lstrlen(strBasePath) - 1; i > 0; --i)
	{
		if (strBasePath[i] == '\\' || strBasePath[i] == '/')
		{
			m_mapPath.insert(make_pair(BASE_PATH, strBasePath));
			break;
		}
			
		wmemset(&strBasePath[i], 0, 2);
	}

	CreatePath(TEXTURE_PATH, L"Texture\\");
	CreatePath(CHARACTER_PATH, L"Texture\\Character\\");

	return true;
}

void CFileManager::CreatePath(const string& strKey, const wchar_t* pFileName, const char* pBasePath)
{
	const wchar_t* strBasePath = FindPath(pBasePath);

	wstring strFullPath;

	if(strBasePath)
		strFullPath = strBasePath;

	strFullPath += pFileName;

	m_mapPath.insert(make_pair(strKey, strFullPath));
}

const wchar_t* CFileManager::FindPath(const string& strKey)
{
	unordered_map<string, wstring>::iterator iter = m_mapPath.find(strKey);

	if (iter == m_mapPath.end())
		return NULL;

	return iter->second.c_str();
}

const char* CFileManager::FindPathMultiByte(const string& strKey)
{
	const wchar_t* pPath = FindPath(strKey);

	if (!pPath)
		return NULL;

	WideCharToMultiByte(CP_ACP, 0, pPath, -1, m_strPath,
		lstrlen(pPath), 0, 0);

	return m_strPath;
}
