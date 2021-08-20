#include "SoundManager.h"
#include "FileManager.h"

DEFINITION_SINGLE(CSoundManager);

CSoundManager::CSoundManager()	:
	m_pSystem(NULL)
{

}

CSoundManager::~CSoundManager()
{
	unordered_map<string, PSOUNDINFO>::iterator iter;

	for (int i = CNT_NONE; i < CNT_END; ++i)
	{
		for (iter = m_mapSound[i].begin(); iter != m_mapSound[i].end(); ++iter)
		{
			iter->second->pSound->release();
			SAFE_DELETE(iter->second);
		}

	}
	m_pSystem->close();
	m_pSystem->release();
}


bool CSoundManager::Init()
{
	System_Create(&m_pSystem);

	m_pSystem->init(10, FMOD_INIT_NORMAL, NULL);

	LoadSound(CNT_NONE, "BlueMary", true, "BlueMary.mp3");
	LoadSound(CNT_NONE, "ReadyGo", false, "ReadyGo.wav");
	LoadSound(CNT_NONE, "KO", false, "KO.wav");
	LoadSound(CNT_NONE, "TimesOut", false, "TimesOut.wav");
	LoadSound(CNT_NONE, "YouWin", false, "YouWin.wav");
	LoadSound(CNT_NONE, "GameOver", false, "GameOver.wav");
	LoadSound(CNT_NONE, "Draw", false, "Draw.wav");
	
	//=============================================
	// BENIMARU SOUND
	LoadSound(CNT_BENIMARU, "SpecialAttack1", false, "BenimaruSpecialAttack1.wav", SOUND_BENIMARU_PATH);
	LoadSound(CNT_BENIMARU, "Hit1", false, "BenimaruHit1.wav", SOUND_BENIMARU_PATH);
	LoadSound(CNT_BENIMARU, "Hit2", false, "BenimaruHit2.wav", SOUND_BENIMARU_PATH);
	LoadSound(CNT_BENIMARU, "Hit3", false, "BenimaruHit3.wav", SOUND_BENIMARU_PATH);
	LoadSound(CNT_BENIMARU, "Hit4", false, "BenimaruHit4.wav", SOUND_BENIMARU_PATH);
	LoadSound(CNT_BENIMARU, "Hit5", false, "BenimaruHit5.wav", SOUND_BENIMARU_PATH);
	LoadSound(CNT_BENIMARU, "Hit6", false, "BenimaruHit6.wav", SOUND_BENIMARU_PATH);
	LoadSound(CNT_BENIMARU, "Damage1", false, "BenimaruDamage1.wav", SOUND_BENIMARU_PATH);
	LoadSound(CNT_BENIMARU, "Damage2", false, "BenimaruDamage2.wav", SOUND_BENIMARU_PATH);
	LoadSound(CNT_BENIMARU, "Damage3", false, "BenimaruDamage3.wav", SOUND_BENIMARU_PATH);
	LoadSound(CNT_BENIMARU, "Damage4", false, "BenimaruDamage4.wav", SOUND_BENIMARU_PATH);
	LoadSound(CNT_BENIMARU, "Damage5", false, "BenimaruDamage5.wav", SOUND_BENIMARU_PATH);

	//=============================================
	//KYO SOUND
	LoadSound(CNT_KYO, "Hit1", false, "KyoHit1.wav", SOUND_KYO_PATH);
	LoadSound(CNT_KYO, "Hit2", false, "KyoHit2.wav", SOUND_KYO_PATH);
	LoadSound(CNT_KYO, "Hit3", false, "KyoHit3.wav", SOUND_KYO_PATH);
	LoadSound(CNT_KYO, "Damage1", false, "KyoDamage1.wav", SOUND_KYO_PATH);
	LoadSound(CNT_KYO, "Damage2", false, "KyoDamage2.wav", SOUND_KYO_PATH);
	LoadSound(CNT_KYO, "Damage3", false, "KyoDamage3.wav", SOUND_KYO_PATH);
	
	return true;
}

bool CSoundManager::LoadSound(CHARACTER_NAME_TYPE eType, const string& strKey, bool bLoop, const char* pFileName, const string& strPathKey)
{
	if (FindSound(strKey))
		return true;

	const char* pPath = GET_SINGLE(CFileManager)->FindPathMultiByte(strPathKey);

	string strPath;

	if (pPath)
		strPath = pPath;

	strPath += pFileName;

	FMOD_MODE eMode = FMOD_LOOP_NORMAL;

	if (!bLoop)
		eMode = FMOD_DEFAULT;

	PSOUNDINFO pSoundInfo = new SOUNDINFO;

	pSoundInfo->bLoop = bLoop;
	m_pSystem->createSound(strPath.c_str(), eMode, NULL, &pSoundInfo->pSound);

	m_mapSound[eType].insert(make_pair(strKey, pSoundInfo));
	
	return true;
}

bool CSoundManager::Play(const string& strKey, GAME_SOUND_TYPE eType, CHARACTER_NAME_TYPE eCharacterType)
{
	PSOUNDINFO pSound = FindSound(strKey, eCharacterType);

	if (!pSound)
		return false;

	m_pSystem->update();

	GAME_SOUND_TYPE eChannel;

	if (!pSound->bLoop)
		eChannel = GST_EFFECT;

	else
		eChannel = eType;

	m_pSystem->playSound(pSound->pSound, NULL, false, &m_pChannel[eChannel]);

	return true;
}

void CSoundManager::Stop(GAME_SOUND_TYPE eType)
{
	m_pChannel[eType]->stop();
}

void CSoundManager::Volume(GAME_SOUND_TYPE eType, float fVolume)
{
	m_pChannel[eType]->setVolume(fVolume);
}

PSOUNDINFO CSoundManager::FindSound(const string& strKey, CHARACTER_NAME_TYPE eType)
{
	unordered_map<string, PSOUNDINFO>::iterator iter = m_mapSound[eType].find(strKey);

	if (iter == m_mapSound[eType].end())
		return NULL;
	
	return iter->second;
}

int CSoundManager::FindSoundCount(const string& strKey, CHARACTER_NAME_TYPE eType)
{
	int iCount = 0;

	unordered_map<string, PSOUNDINFO>::iterator iter;
	unordered_map<string, PSOUNDINFO>::iterator iterEnd = m_mapSound[eType].end();

	for (iter = m_mapSound[eType].begin(); iter != iterEnd; ++iter)
	{
		if (iter->first.find(strKey) >= 0)
		{
			++iCount;
		}
	}

	return iCount;
}
