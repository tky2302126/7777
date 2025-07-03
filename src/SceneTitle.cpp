#include "SceneTitle.h"

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneTitleの実装ファイル
*/


SceneTitle::SceneTitle()
	: selectIndex(0), isSelect(false), inputHandle(-1), 
	ipBuffer{ -1, -1, -1, -1 }
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

	cursor.ManualInitialize({300,300,0}, {100,20,0});
	cursor.SetTargetPosition({ 300,300,0 });

	inputHandle = MakeKeyInput(3, TRUE, FALSE, FALSE);

	SetKeyInputStringColor(inputHandle, 
		GetColor(0, 0, 0), GetColor(0, 0, 0),
		GetColor(0, 0, 0), GetColor(0, 0, 0),
		GetColor(0, 0, 0), GetColor(0, 0, 0)
		); // カラーを設定
}

SceneTitle::‾SceneTitle()
{
}

void SceneTitle::LoadComplete()
{
}

void SceneTitle::KeyInputCallback(InputAction::CallBackContext _c)
{
	for (auto it = _c.key.begin(); it != _c.key.end(); ++it)
	{
		if (it->inputState != InputState::Started)
			continue;

		// 決定キー押下時の処理
		if (it->keyCode == KEY_INPUT_Z)
		{
			SelectInput();
		}

		if (isSelect) continue;

		// カーソル移動と参照項目移動の処理
		if (it->keyCode == PAD_INPUT_UP)
		{
			if (selectIndex == 0)	selectIndex = 1;
			else if (selectIndex == 1)	selectIndex = 0;
		}

		if (it->keyCode == PAD_INPUT_DOWN)
		{
			if (selectIndex == 0)	selectIndex = 1;
			else if (selectIndex == 1)	selectIndex = 0;
		}


		cursor.SetTargetPosition({ 300.0f, (300.0f + 100.0f * (float)selectIndex), 0.0f });
	}
}

void SceneTitle::Update()
{
}

void SceneTitle::LateUpdate()
{
	cursor.ManualUpdate();

	std::string text = "スタート";

	// テキスト表示座標
	float posX = 1920 / 2 - (50 * (text.size() / 4));

	DrawFormatString((int)posX, 900, GetColor(0, 0, 0),
		 text.c_str());


	DrawFormatString((int)posX, 500, GetColor(0, 0, 0),
		"Title");


	DrawFormatString(300, 300 - GetFontSize() / 2, 
		GetColor(0, 0, 0),
		"項目1");

	DrawFormatString(300, 400 - GetFontSize() / 2,
		GetColor(0, 0, 0),
		"項目2");


	if (isSelect)
	{
		// 入力中のグループを設定
		int inputIndex = 0;
		for (int i = 0; i < 4; ++i)
		{
			if (ipBuffer[i] != -1) continue;
			inputIndex = i;
			break;
		}

		for(int i = 0; i < inputIndex; ++i)
		{			
			DrawFormatString(100 + GetFontSize() * 3 * i,
				100, GetColor(0, 0, 0), 
				"%d.", ipBuffer[i]);
		}

		DrawKeyInputString(100 + GetFontSize() * 3 * inputIndex, 100, inputHandle);

		if (CheckKeyInput(inputHandle))
		{
			// 入力された文字列を数列に変換
			int num = GetKeyInputNumber(inputHandle);
			ipBuffer[inputIndex] = num;

			// 入力が完了した場合
			if (ipBuffer[3] != -1)
			{
				IPDATA ip;
				ip.d1 = ipBuffer[0];
				ip.d2 = ipBuffer[1];
				ip.d3 = ipBuffer[2];
				ip.d4 = ipBuffer[3];

				isSelect = false;
				cursor.SetColor(GetColor(100, 100, 255));
				cursor.SetTargetScale({ 100,20,0 });
			}
			else
			{
				SetActiveKeyInput(inputHandle);
				SetKeyInputString("", inputHandle);
			}
		}
	}
}

void SceneTitle::SelectInput()
{
	if (isSelect)
	{
		isSelect = false;
		cursor.SetColor(GetColor(100, 100, 255));
		cursor.SetTargetScale({ 100,20,0 });
		return;
	}

	isSelect = true;
	cursor.SetColor(GetColor(100, 100, 100));
	cursor.SetTargetScale({ 150,15,0 });

	SetActiveKeyInput(inputHandle);
	SetKeyInputString("", inputHandle);
}



