#include "InputManager.h"

DEFINITION_SINGLE(CInputManager);

CInputManager::CInputManager()	:
	m_pKeyInfo(NULL)
{

}

CInputManager::~CInputManager()
{
	Safe_Delete_Map(m_mapKey);
}

bool CInputManager::Init()
{
	CreateKey("MoveLeft", VK_LEFT);
	CreateKey("MoveRight", VK_RIGHT);
	CreateKey("MoveDown", VK_DOWN);	
	CreateKey("Jump", VK_SPACE);

	return true;
}

void CInputManager::Update(float fDeltaTime)
{
	unordered_map<string, PKEYINFO>::iterator iter;
	unordered_map<string, PKEYINFO>::iterator iterEnd = m_mapKey.end();

	for (iter = m_mapKey.begin(); iter != iterEnd; ++iter)
	{
		for (size_t i = 0; i < iter->second->vecKey.size(); ++i)
		{
			int iCount = 0;
			if (GetAsyncKeyState(iter->second->vecKey[i]) && 0x8000)
			{
				++iCount;
			}

			if (iCount == iter->second->vecKey.size())
			{
				if (!iter->second->bDown && !iter->second->bPress)
				{
					iter->second->bDown = true;
					iter->second->bPress = false; 
					iter->second->bUp = false;
				}

				else if (iter->second->bDown && !iter->second->bPress)
				{
					iter->second->bDown = false;
					iter->second->bPress = true;
					iter->second->bUp = false;
				}
			}

			else if (!iter->second->bUp && iter->second->bPress)
			{
				iter->second->bDown = false;
				iter->second->bPress = false;
				iter->second->bUp = true;
			}
		}
	}
}

PKEYINFO CInputManager::FindKey(const string& strKey)	const
{
	unordered_map<string, PKEYINFO>::const_iterator iter = m_mapKey.find(strKey);

	if (iter == m_mapKey.end())
		return NULL;

	return iter->second;
}