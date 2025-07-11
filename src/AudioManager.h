#pragma once
#include "define.h"
#include "HandlerWaltanForDxLib.h"
#include <iostream>
#include <unordered_map>
#include <thread>
#include <mutex>

enum SEList
{
	SE_ALL
};

enum BGMList
{
	BGM_ALL
};

class AudioManager
{
	AudioManager();
	~AudioManager();

	static AudioManager& GetInstance();
	void Init();
	void UnInit();
	void Load();
	void LoadTest();
	void Release(SEList);
	void Release(BGMList);
	void PlayBGM(BGMList name, bool loop = true);
	void PlaySE(SEList);
	void PlaySECustom(SEList, BGMList, bool loop = true);
	void SetLoop(bool);

private:
	static std::unique_ptr<AudioManager> Instance;
	std::unordered_map<SEList, int> SETrack;
	std::unordered_map<BGMList, int> BGMTrack;
	bool loop = false;
	int BGMVolume;
	int SEVolume;
	int surveyHandle = -1;
	int surveyConunt = -1;
	int oldVolume = -1;
	std::thread asyncThread;
	std::mutex seMutex;
	void SurveySEAsync(SEList);
};

