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
	for (iter = m_mapSound.begin(); iter != m_mapSound.end(); ++iter)
	{
		iter->second->pSound->release();
		SAFE_DELETE(iter->second);
	}

	m_pSystem->close();
	m_pSystem->release();
}


bool CSoundManager::Init()
{
	System_Create(&m_pSystem);

	m_pSystem->init(10, FMOD_INIT_NORMAL, NULL);

	return true;
}

bool CSoundManager::LoadSound(const string& strKey, bool bLoop, const char* pFileName, const string& strPathKey)
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

	m_mapSound.insert(make_pair(strKey, pSoundInfo));
	
	return true;
}

bool CSoundManager::Play(const string& strKey)
{
	PSOUNDINFO pSound = FindSound(strKey);

	if (!pSound)
		return false;

	m_pSystem->update();

	GAME_SOUND_TYPE eChannel = GST_BGM;

	if (!pSound->bLoop)
		eChannel = GST_EFFECT;

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

PSOUNDINFO CSoundManager::FindSound(const string& strKey)
{
	unordered_map<string, PSOUNDINFO>::iterator iter = m_mapSound.find(strKey);

	if (iter == m_mapSound.end())
		return NULL;
	
	return iter->second;
}
