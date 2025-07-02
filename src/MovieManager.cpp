#include "MovieManager.h"

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneTitleの実装ファイル
*/

//
// 静的メンバ変数の初期化
//

MovieManager* MovieManager::instance = nullptr;


void MovieManager::Awake()
{
	// 自身のインスタンスが既に存在する場合は削除し、そのまま終了
	if (instance != nullptr)
	{
		gameObject->Destroy(gameObject);
		return;
	}

	//
	// instanceがnullptrの場合のみ実行
	//

	instance = this;
	gameObject->priority = -9999;
}

void MovieManager::LateUpdate()
{
	//
	// そのシーンで使用するデータを読み込む
	//

	for (auto it = movie_title.begin(); it != movie_title.end(); ++it)
		if (it->second->playStatus == PlayStatus::Play)
			it->second->ManualUpdate();

	for (auto it = movie_game.begin(); it != movie_game.end(); ++it)
		if (it->second->playStatus == PlayStatus::Play)
			it->second->ManualUpdate();

	for (auto it = movie_MainMenu.begin(); it != movie_MainMenu.end(); ++it)
		if (it->second->playStatus == PlayStatus::Play)
			it->second->ManualUpdate();
}

MovieManager& MovieManager::Instance()
{
	// 自身のインスタンスを返す
	return *instance;
}

void MovieManager::Play(const std::string& _key, bool _isReset)
{
	//
	// シーンで使用するデータから検索
	//

	switch (crrSceneTag)
	{
	case SceneTag::Title:
		movie_title[_key]->Play(_isReset);
		break;

	case SceneTag::Game:
		movie_game[_key]->Play(_isReset);
		break;

	case SceneTag::MainMenu:
		movie_MainMenu[_key]->Play(_isReset);
		break;

	case SceneTag::Result:
		break;
	}
}

void MovieManager::Play(const std::string& _key, SceneTag _tag, bool _isReset)
{
	//
	// シーンで使用するデータから検索
	//
	switch (_tag)
	{
	case SceneTag::Title:
		movie_title[_key]->Play(_isReset);
		break;
	case SceneTag::Game:
		movie_game[_key]->Play(_isReset);
		break;
	case SceneTag::MainMenu:
		movie_MainMenu[_key]->Play(_isReset);
		break;
	case SceneTag::Result:
		break;
	}
}

void MovieManager::Stop(const std::string& _key, bool _isReset)
{
	//
	// シーンで使用するデータから検索
	//

	switch (crrSceneTag)
	{
	case SceneTag::Title:
		movie_title[_key]->Stop(_isReset);
		break;

	case SceneTag::Game:
		movie_game[_key]->Stop(_isReset);
		break;

	case SceneTag::MainMenu:
		movie_MainMenu[_key]->Stop(_isReset);
		break;

	case SceneTag::Result:
		break;
	}
}

void MovieManager::Stop(const std::string& _key, SceneTag _tag, bool _isReset)
{
	//
	// シーンで使用するデータから検索
	//
	switch (_tag)
	{
	case SceneTag::Title:
		movie_title[_key]->Stop(_isReset);
		break;
	case SceneTag::Game:
		movie_game[_key]->Stop(_isReset);
		break;
	case SceneTag::MainMenu:
		movie_MainMenu[_key]->Stop(_isReset);
		break;
	case SceneTag::Result:
		break;
	}
}



std::unique_ptr<VideoPlayer>& MovieManager::GetMovie(const std::string& _key)
{
	//
	// シーンで使用するデータから検索
	//

	switch (crrSceneTag)
	{
	case SceneTag::Title:
		return movie_title[_key];
		break;

	case SceneTag::Game:
		return movie_game[_key];
		break;

	case SceneTag::MainMenu:
		return movie_MainMenu[_key];
		break;

	case SceneTag::Result:
		break;
	}
}

void MovieManager::LoadMovie(SceneTag _sceneTag)
{
	//
	// そのシーンで使用するデータを読み込む
	//

	switch (_sceneTag)
	{
	case SceneTag::Title:
	{
		crrSceneTag = _sceneTag;
		// タイトル画面で使用する動画を読み込む
		if (!movie_title.empty()) return;

		// CSVファイルから読み込む
		LoadCSV("Assets/Movie/Title/Movie_Title.csv", movie_title);
		break;
	}

	case SceneTag::Game:
	{
		crrSceneTag = _sceneTag;
		// タイトル画面で使用する動画を読み込む
		if (!movie_game.empty()) return;

		// CSVファイルから読み込む
		LoadCSV("Assets/Movie/Game/Movie_Game.csv", movie_game);
		break;
	}

	case SceneTag::MainMenu:
	{
		crrSceneTag = _sceneTag;
		// タイトル画面で使用する動画を読み込む
		if (!movie_MainMenu.empty()) return;

		// CSVファイルから読み込む
		LoadCSV("Assets/Movie/MainMenu/Movie_MainMenu.csv", movie_MainMenu);
		break;
	}

	case SceneTag::Result:
		break;
	}
}

void MovieManager::LoadCSV(const std::string& _path, std::unordered_map<std::string, std::unique_ptr<VideoPlayer>>& _output)
{
	// CSVファイルからテキストを読み込む
	auto csv = CsvLoader::Load(_path);

	/*
		[][0] = 名前
		[][1] = ファイルパス
 		[][2] = ループさせるか
		[][3] = 透過処理を施すか
	*/
	for (int i = 1; i < csv.size(); ++i)
	{
		if(csv[i][2] == "TRUE" ? true : false)
			_output[csv[i][0]] = std::make_unique<VideoPlayer>(csv[i][1], DX_PLAYTYPE_LOOP, csv[i][3] == "TRUE" ? true : false);
		else
			_output[csv[i][0]] = std::make_unique<VideoPlayer>(csv[i][1], DX_PLAYTYPE_BACK, csv[i][3] == "TRUE" ? true : false);
	}
}
