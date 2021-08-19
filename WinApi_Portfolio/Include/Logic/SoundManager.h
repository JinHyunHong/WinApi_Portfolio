#pragma once

#include "../Game.h"

typedef struct _tagSoundInfo
{
	Sound* pSound;
	bool   bLoop;
}SOUNDINFO, *PSOUNDINFO;

class CSoundManager
{
	DECLARE_SINGLE(CSoundManager);

private:
	System*								m_pSystem;
	Channel*							m_pChannel[GST_END];
	unordered_map<string, PSOUNDINFO>	m_mapSound[CNT_END];

// CNT_NONE�� ��������� Ȱ��, ������ ĳ���� ������ �з�
public:
	bool Init();
	bool LoadSound(CHARACTER_NAME_TYPE eType, const string& strKey, bool bLoop,
		const char* pFileName,  const string& strPathKey = SOUND_PATH);
	bool Play(const string& strKey, GAME_SOUND_TYPE eType, CHARACTER_NAME_TYPE eCharacterType = CNT_NONE);
	void Stop(GAME_SOUND_TYPE eType);
	void Volume(GAME_SOUND_TYPE eType, float fVolume);
	// �ش� ���ڿ��� ���� ������ ���尡 � �ִ��� Ȯ�����ش�. -> ĳ���� ���� ���� ������ �ٸ���.
	int FindSoundCount(const string& strKey, CHARACTER_NAME_TYPE eType = CNT_NONE);

private:
	PSOUNDINFO FindSound(const string& strKey, CHARACTER_NAME_TYPE eType = CNT_NONE);
};

