#include "AudioManager.h"

std::unique_ptr<AudioManager> AudioManager::Instance = nullptr;

AudioManager::AudioManager()
	:BGMVolume(0), SEVolume(0)
{
}

AudioManager::~AudioManager()
{
	
}

void AudioManager::Init()
{
	const int maxVolume = 255;
	BGMVolume = maxVolume * 80 / 100;
	SEVolume = maxVolume * 80 / 100;
}

void AudioManager::UnInit()
{
	for (int i = 0; i < BGMList::BGM_ALL; i++)
	{
		auto it = BGMTrack.find((BGMList)i);
		// 見つからなかった場合
		if (it == BGMTrack.end() || it->second == -1)
		{
			continue;
		}
		int handle = it->second;
		auto result = DeleteSoundMem(handle);
		if (result == 0) { BGMTrack.erase(it); }
	}

	for (int i = 0; i < SEList::SE_ALL; i++)
	{
		// 見つからなかった場合
		if (SETrack.find((SEList)i) == SETrack.end())
		{
			continue;
		}
		DeleteSoundMem(SETrack[(SEList)i]);
	}
}

AudioManager& AudioManager::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = std::make_unique<AudioManager>();
	}
	return *Instance;
}

void AudioManager::Load()
{
	SETrack[SEList::SE_CARD_FLIP] = LoadSoundMem("Assets/Sound/card_flip.mp3");
	SETrack[SEList::SE_CARD_EXTRACT] = LoadSoundMem("Assets/Sound/card_extract.mp3");
	BGMTrack[BGMList::BGM_BGM] = LoadSoundMem("Assets/Sound/BGM.mp3");
}

void AudioManager::Load(SceneTag sceneName)
{
}


void AudioManager::ReleaseSE(SEList)
{
}

void AudioManager::ReleaseBGM(BGMList)
{
}

void AudioManager::PlayBGM(BGMList name, bool loop)
{
	for (int i = 0; i < BGMList::BGM_ALL; i++)
	{
		auto it = BGMTrack.find((BGMList)i);
		// 見つからなかった場合
		if (it == BGMTrack.end() || it->second == -1)
		{
			continue;
		}
		int handle = it->second;
		auto result = StopSoundMem(handle);
	}

	if (BGMTrack.find(name) == BGMTrack.end()) { return; }
	ChangeVolumeSoundMem(BGMVolume, BGMTrack[name]);
	if (!loop)
	{
		PlaySoundMem(BGMTrack[name], DX_PLAYTYPE_BACK);
	}
	else
	{
		PlaySoundMem(BGMTrack[name], DX_PLAYTYPE_LOOP);
	}
}

void AudioManager::PlaySE(SEList name)
{
	PlaySoundMem(SETrack[name], DX_PLAYTYPE_BACK);
}
