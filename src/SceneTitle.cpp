#include "SceneTitle.h"

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneTitleの実装ファイル
*/


SceneTitle::SceneTitle()
{
	// 実行中のシーンタグ
	sceneTag = SceneTag::Title;

	// 背景色を変更
	SetBackgroundColor(255, 255, 255);

	// キー入力のコールバックを登録
	callBackId = input->AddCallBack("cursor", std::bind(&SceneTitle::KeyInputCallback, this, std::placeholders::_1));

	// 暗転解除
	HWDotween::DoDelay(15)->OnComplete([&]
		{
			UIManager::FadeOut(20);
			isLoad = false;
		});
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::LoadComplete()
{
}

void SceneTitle::KeyInputCallback(InputAction::CallBackContext _c)
{
}

void SceneTitle::Update()
{
}

void SceneTitle::LateUpdate()
{
	std::string text = "スタート";

	// テキスト表示座標
	float posX = 1920 / 2 - (50 * (text.size() / 4));

	DrawFormatString((int)posX, 900, GetColor(0, 0, 0),
		 text.c_str());


	DrawFormatString((int)posX, 500, GetColor(0, 0, 0),
		"Title");
}



