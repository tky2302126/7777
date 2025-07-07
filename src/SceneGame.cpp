#include "SceneGame.h"

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneTitleの実装ファイル
*/


SceneGame::SceneGame()
{
	// 実行中のシーンタグ
	sceneTag = SceneTag::Game;

	// 背景色を変更
	SetBackgroundColor(255, 255, 255);

	// キー入力のコールバックを登録
	callBackId = input->AddCallBack("cursor", std::bind(&SceneGame::KeyInputCallback, this, std::placeholders::_1));

	// 暗転解除
	HWDotween::DoDelay(15)->OnComplete([&]
		{
			UIManager::FadeOut(20);
			isLoad = false;
		});

	board = std::make_shared<HWGameObject>();
	boardCp = board->AddComponent<Board>();
}

SceneGame::~SceneGame()
{
	board.reset();
	input->DeleteCallBack("cursor", callBackId);
}

void SceneGame::LoadComplete()
{
	boardCp->ManualLoad();
}

void SceneGame::KeyInputCallback(InputAction::CallBackContext _c)
{
}

void SceneGame::Update()
{
}

void SceneGame::LateUpdate()
{
}



