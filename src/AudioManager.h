#pragma once
#include "define.h"
#include "HandlerWaltanForDxLib.h"
#include "SceneBase.h"
#include <unordered_map>

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
public:

	AudioManager();
	~AudioManager();

	static AudioManager& GetInstance();
	void Init();
	void UnInit();
	/// <summary>
	/// 登録されている音声データを全てメモリにロードする
	/// </summary>
	void Load();
	/// <summary>
	/// シーンごとに必要なリソースを読み込む
	/// LoadCompleteで呼ばれることを想定
	/// </summary>
	/// <param name="sceneName">シーン</param>
	void Load(SceneTag sceneName);
	void ReleaseSE(SEList);
	void ReleaseBGM(BGMList);
	void PlayBGM(BGMList name, bool loop = true);
	void PlaySE(SEList);

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
};

