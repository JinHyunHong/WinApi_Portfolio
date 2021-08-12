#include "InputManager.h"
#include "../UI/Mouse.h"
#include "../UI/UI.h"

DEFINITION_SINGLE(CInputManager);

CInputManager::CInputManager()	:
	m_pKeyInfo(NULL)
{

}

CInputManager::~CInputManager()
{
	Safe_Delete_Map(m_mapKey);
}

POSITION CInputManager::GetMouseClientPos() const
{
	return m_pMouse->GetPos();
}

POSITION CInputManager::GetMouseWorldPos() const
{
	return m_pMouse->GetWorldPos();
}

POSITION CInputManager::GetMouseMove() const
{
	return m_pMouse->GetMove();
}

bool CInputManager::Init()
{
	CreateKey("MoveLeft", VK_LEFT);
	CreateKey("MoveRight", VK_RIGHT);
	CreateKey("Jump", VK_SPACE);
	//CreateKey("MouseLButton", VK_LBUTTON);
	CreateKey('Z', "Attack1");
	CreateKey('X', "Attack2");
	CreateKey('C', "Attack3");
	CreateKey('V', "Attack4");
	CreateKey("SitAttack1", VK_DOWN, 'Z');
	CreateKey('X', VK_DOWN, "SitAttack2");
	CreateKey(VK_DOWN, 'C', "SitAttack3");
	CreateKey(VK_DOWN, 'V', "SitAttack4");
	CreateKey(VK_DOWN, "Sit");
	CreateKey(VK_LEFT, VK_LEFT, "MovingLeft");
	CreateKey(VK_RIGHT, VK_RIGHT, "MovingRight");
	
	GetCursorPos(&m_tMousePos);

	// 마우스 생성
	m_pMouse = CUI::CreateUIObj<CMouse>("Mouse");

	m_pMouse->SetSize(45, 45);


	return true;
}

void CInputManager::Update(float fDeltaTime)
{
	unordered_map<string, PKEYINFO>::iterator iter;
	unordered_map<string, PKEYINFO>::iterator iterEnd = m_mapKey.end();

	int iUsedKey[MAX_PATH] = {0};
	int iIndex = 0;

	for (iter = m_mapKey.begin(); iter != iterEnd; ++iter)
	{
		int iCount = 0;
		int iUsedCopy[MAX_PATH] = { 0 };
		memcpy(iUsedCopy, iUsedKey, sizeof(iUsedKey));
		for (size_t i = 0; i < iter->second->vecKey.size(); ++i)
		{
			if (GetAsyncKeyState(iter->second->vecKey[i]) && 0x8000)
			{
				++iCount;
				
				iUsedKey[iIndex] = iter->second->vecKey[i];
				++iIndex;
				
			}

			else
			{
				for (int j = 0; j <= iIndex; ++j)
				{
					if (iUsedCopy[j] == iter->second->vecKey[i])
					{
						++iCount;
						iUsedCopy[j] = NULL;
					}
				}
			}

		}

		if (iCount == iter->second->vecKey.size())
		{
			if (!iter->second->bDown && !iter->second->bPress)
			{
				iter->second->bDown = true;
				iter->second->bPress = false;
			}

			else if (iter->second->bDown)
			{
				iter->second->bDown = false;
				iter->second->bPress = true;
			}
		}

		else
		{
			if (iter->second->bPress)
			{
				iter->second->bDown = false;
				iter->second->bPress = false;
				iter->second->bUp = true;
			}

			else if (iter->second->bUp)
			{
				iter->second->bUp = false;
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
