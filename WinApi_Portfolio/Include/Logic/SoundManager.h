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
	Channel*							m_pChannel[ST_END];
	unordered_map<string, PSOUNDINFO>	m_mapSound;

public:
	bool Init();
	bool LoadSound(const string& strKey, bool bLoop,
		const char* pFileName,  const string& strPathKey = SOUND_PATH);
	bool Play(const string& strKey);
	void Stop(GAME_SOUND_TYPE eType);
	void Volume(GAME_SOUND_TYPE eType, float fVolume);

private:
	PSOUNDINFO FindSound(const string& strKey);
};

