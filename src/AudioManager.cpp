#include "AudioManager.h"

std::unique_ptr<AudioManager> AudioManager::Instance = nullptr;

AudioManager::AudioManager()
	:BGMVolume(0), SEVolume(0)
{
}

AudioManager::~AudioManager()
{
	if (asyncThread.joinable())
	{
		asyncThread.join();
	}
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
}





void AudioManager::Release(SEList)
{
}

void AudioManager::Release(BGMList)
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

void AudioManager::PlaySECustom(SEList seName, BGMList bgmName, bool loop)
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
	auto future = std::async(std::launch::async, &AudioManager::SurveySEAsync, this, seName);
	future.get();
	PlayBGM(bgmName, loop);
}

void AudioManager::SetLoop(bool)
{
}

void AudioManager::SurveySEAsync(SEList name)
{
	std::lock_guard<std::mutex> lock(seMutex);
	PlaySE(name);
	while (true)
	{
		if (CheckSoundMem(SETrack[name]) == 0)
		{
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

}
