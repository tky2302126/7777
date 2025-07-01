#include "MovieManager.h"

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneTitle�̎����t�@�C��
*/

//
// �ÓI�����o�ϐ��̏�����
//

MovieManager* MovieManager::instance = nullptr;


void MovieManager::Awake()
{
	// ���g�̃C���X�^���X�����ɑ��݂���ꍇ�͍폜���A���̂܂܏I��
	if (instance != nullptr)
	{
		gameObject->Destroy(gameObject);
		return;
	}

	//
	// instance��nullptr�̏ꍇ�̂ݎ��s
	//

	instance = this;
	gameObject->priority = -9999;
}

void MovieManager::LateUpdate()
{
	//
	// ���̃V�[���Ŏg�p����f�[�^��ǂݍ���
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
	// ���g�̃C���X�^���X��Ԃ�
	return *instance;
}

void MovieManager::Play(const std::string& _key, bool _isReset)
{
	//
	// �V�[���Ŏg�p����f�[�^���猟��
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
	// �V�[���Ŏg�p����f�[�^���猟��
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
	// �V�[���Ŏg�p����f�[�^���猟��
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
	// �V�[���Ŏg�p����f�[�^���猟��
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
	// �V�[���Ŏg�p����f�[�^���猟��
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
	// ���̃V�[���Ŏg�p����f�[�^��ǂݍ���
	//

	switch (_sceneTag)
	{
	case SceneTag::Title:
	{
		crrSceneTag = _sceneTag;
		// �^�C�g����ʂŎg�p���铮���ǂݍ���
		if (!movie_title.empty()) return;

		// CSV�t�@�C������ǂݍ���
		LoadCSV("Assets/Movie/Title/Movie_Title.csv", movie_title);
		break;
	}

	case SceneTag::Game:
	{
		crrSceneTag = _sceneTag;
		// �^�C�g����ʂŎg�p���铮���ǂݍ���
		if (!movie_game.empty()) return;

		// CSV�t�@�C������ǂݍ���
		LoadCSV("Assets/Movie/Game/Movie_Game.csv", movie_game);
		break;
	}

	case SceneTag::MainMenu:
	{
		crrSceneTag = _sceneTag;
		// �^�C�g����ʂŎg�p���铮���ǂݍ���
		if (!movie_MainMenu.empty()) return;

		// CSV�t�@�C������ǂݍ���
		LoadCSV("Assets/Movie/MainMenu/Movie_MainMenu.csv", movie_MainMenu);
		break;
	}

	case SceneTag::Result:
		break;
	}
}

void MovieManager::LoadCSV(const std::string& _path, std::unordered_map<std::string, std::unique_ptr<VideoPlayer>>& _output)
{
	// CSV�t�@�C������e�L�X�g��ǂݍ���
	auto csv = CsvLoader::Load(_path);

	/*
		[][0] = ���O
		[][1] = �t�@�C���p�X
 		[][2] = ���[�v�����邩
		[][3] = ���ߏ������{����
	*/
	for (int i = 1; i < csv.size(); ++i)
	{
		if(csv[i][2] == "TRUE" ? true : false)
			_output[csv[i][0]] = std::make_unique<VideoPlayer>(csv[i][1], DX_PLAYTYPE_LOOP, csv[i][3] == "TRUE" ? true : false);
		else
			_output[csv[i][0]] = std::make_unique<VideoPlayer>(csv[i][1], DX_PLAYTYPE_BACK, csv[i][3] == "TRUE" ? true : false);
	}
}
