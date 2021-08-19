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

// CNT_NONE은 배경음으로 활용, 나머지 캐릭터 용으로 분류
public:
	bool Init();
	bool LoadSound(CHARACTER_NAME_TYPE eType, const string& strKey, bool bLoop,
		const char* pFileName,  const string& strPathKey = SOUND_PATH);
	bool Play(const string& strKey, GAME_SOUND_TYPE eType, CHARACTER_NAME_TYPE eCharacterType = CNT_NONE);
	void Stop(GAME_SOUND_TYPE eType);
	void Volume(GAME_SOUND_TYPE eType, float fVolume);
	// 해당 문자열과 같은 문자의 사운드가 몇개 있는지 확인해준다. -> 캐릭터 마다 사운드 갯수가 다르다.
	int FindSoundCount(const string& strKey, CHARACTER_NAME_TYPE eType = CNT_NONE);

private:
	PSOUNDINFO FindSound(const string& strKey, CHARACTER_NAME_TYPE eType = CNT_NONE);
};

