#include "SceneTitle.h"

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneTitleの実装ファイル
*/


SceneTitle::SceneTitle()
	: selectIndex(0), isSelect(false), inputHandle(-1),portId(-1),
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

	inputHandle = MakeKeyInput(4, TRUE, FALSE, TRUE);

	SetKeyInputStringColor(inputHandle,
		GetColor(0, 0, 0), GetColor(0, 0, 0),
		GetColor(0, 0, 0), GetColor(0, 0, 0),
		GetColor(0, 0, 0), GetColor(0, 0, 0)
		); // カラーを設定
}

SceneTitle::~SceneTitle()
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
			if (GameManager::role == Role::server)
			{
				if (--selectIndex < 0)
				{
					if (portId == -1)
					{
						selectIndex = 1;
					}
					else
					{
						selectIndex = 2;
					}
				}
			}
			else if (GameManager::role == Role::Client)
			{
				if (--selectIndex < 0)
				{
					if (ipBuffer[3] == -1 || portId == -1)
					{
						selectIndex = 2;
					}
					else
					{
						selectIndex = 3;
					}
				}
			}
		}

		if (it->keyCode == PAD_INPUT_DOWN)
		{
			++selectIndex;

			if(GameManager::role == Role::Client)
			{
				if ((ipBuffer[3] == -1 || portId == -1) &&
					selectIndex > 2)
				{
					selectIndex = 0;
				}
				else if ((ipBuffer[3] != -1 && portId != -1) &&
					selectIndex > 3)
				{
					selectIndex = 0;
				}
			}
			if(GameManager::role == Role::server)
			{
				if (portId == -1 && selectIndex > 1)
				{
					selectIndex = 0;
				}
				else if (portId != -1 && selectIndex > 2)
				{
					selectIndex = 0;
				}
			}
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
		"Role       : ");
	if (GameManager::role == Role::server)
		DrawFormatString(450, 300 - GetFontSize() / 2, GetColor(0, 0, 0), "Sever");
	else
		DrawFormatString(450, 300 - GetFontSize() / 2, GetColor(0, 0, 0), "Client");


	if (GameManager::role == Role::server)
		ServerInputForm();
	if (GameManager::role == Role::Client)
		ClientInputForm();

	if (connectParameter == ConnectParameter::Wait)
	{
		DrawFormatString(450, 1000, GetColor(0, 0, 0), "Connectiong");
	}
	else if (connectParameter == ConnectParameter::Complete)
	{
		DrawFormatString(450, 800, GetColor(0, 0, 0), "Complete!");
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

	if(selectIndex == 0)
	{
		GameManager::role == Role::server ? GameManager::role = Role::Client : GameManager::role = Role::server;
		isSelect = false;
		cursor.SetColor(GetColor(100, 100, 255));
		cursor.SetTargetScale({ 100,20,0 });
		return;
	}
	else if(selectIndex == 1)
	{
		for (int i = 0; i < 4; ++i)
			ipBuffer[i] = -1;
		SetActiveKeyInput(inputHandle);
		SetKeyInputString("", inputHandle);
	}
	else if(selectIndex == 2)
	{
		if (GameManager::role == Role::server)
		{
			PreparationListenNetWork(portId);
			connectParameter = ConnectParameter::Wait;
		}
		else if (GameManager::role == Role::Client)
		{
			SetActiveKeyInput(inputHandle);
			SetKeyInputString("", inputHandle);
		}
	}
	else if(selectIndex == 3)
	{
		connectParameter = ConnectParameter::Wait;
		Connect();
	}
}

void SceneTitle::ServerInputForm()
{
	if (selectIndex == 1)
	{
		if (isSelect)
		{
			DrawKeyInputString(100, 350, inputHandle);

			// �|�[�g�ԍ��̓��͏���
			if (CheckKeyInput(inputHandle))
			{
				// ���͂��ꂽ������𐔗�ɕϊ�
				portId = GetKeyInputNumber(inputHandle);
				SetKeyInputString("", inputHandle);

				isSelect = false;
				cursor.SetColor(GetColor(100, 100, 255));
				cursor.SetTargetScale({ 100,20,0 });
			}
		}
	}

	DrawFormatString(300, 400 - GetFontSize() / 2,
		GetColor(0, 0, 0),
		"ポート番号 : ");
	if (portId != -1)
	{
		DrawFormatString(450, 400 - GetFontSize() / 2,
			GetColor(0, 0, 0),
			"%d", portId);
	}

	// IPアドレスとポート番号が入力されている場合
	int connectNum = 0;
	for (int i = 0; i < 3; ++i)
		if (GameManager::networkHandle[i] != -1)
			connectNum++;
	DrawFormatString(300, 700 - GetFontSize() / 2,
		GetColor(0, 0, 0),
		"参加人数 : %d/4",connectNum + 1);


	if (portId != -1)
	{
		DrawFormatString(300, 500 - GetFontSize() / 2,
			GetColor(0, 0, 0),
			"Connect");
	}

	//! 接続人数の表示
	

	// 接続中の処理
	if (connectParameter == ConnectParameter::Wait)
	{
		int index = 0;
		for(index = 0; index < 3; ++index)
			if (GameManager::networkHandle[index] == -1)
				break;

		// 新しい接続があったらそのネットワークハンドルを得る
		GameManager::networkHandle[index] = GetNewAcceptNetWork();
		if (GameManager::networkHandle[2] != -1)
			connectParameter = ConnectParameter::Complete;
	}
}

void SceneTitle::ClientInputForm()
{
	if (selectIndex == 1)
	{
		if (isSelect)
		{
			// ���͒��̃O���[�v��ݒ�
			int inputIndex = 0;
			for (int i = 0; i < 4; ++i)
			{
				if (ipBuffer[i] != -1) continue;
				inputIndex = i;
				break;
			}

			for (int i = 0; i < inputIndex; ++i)
			{
				DrawFormatString(100 + GetFontSize() * 3 * i,
					350, GetColor(0, 0, 0),
					"%d.", ipBuffer[i]);
			}

			DrawKeyInputString(100 + GetFontSize() * 3 * inputIndex, 350, inputHandle);


			// IP�A�h���X�̓��͏���
			if (CheckKeyInput(inputHandle))
			{
				// ���͂��ꂽ������𐔗�ɕϊ�
				int num = GetKeyInputNumber(inputHandle);
				ipBuffer[inputIndex] = num;

				// ���͂����������ꍇ
				if (ipBuffer[3] != -1)
				{
					ipData.d1 = ipBuffer[0];
					ipData.d2 = ipBuffer[1];
					ipData.d3 = ipBuffer[2];
					ipData.d4 = ipBuffer[3];

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
	else if (selectIndex == 2)
	{
		if (isSelect)
		{
			DrawKeyInputString(100, 450, inputHandle);

			// �|�[�g�ԍ��̓��͏���
			if (CheckKeyInput(inputHandle))
			{
				// ���͂��ꂽ������𐔗�ɕϊ�
				portId = GetKeyInputNumber(inputHandle);
				SetKeyInputString("", inputHandle);

				isSelect = false;
				cursor.SetColor(GetColor(100, 100, 255));
				cursor.SetTargetScale({ 100,20,0 });
			}
		}
	}


	DrawFormatString(300, 400 - GetFontSize() / 2,
		GetColor(0, 0, 0),
		"IPアドレス : ");
	if (ipBuffer[3] != -1)
	{
		DrawFormatString(450, 400 - GetFontSize() / 2,
			GetColor(0, 0, 0),
			"%d.%d.%d.%d", ipData.d1, ipData.d2, ipData.d3, ipData.d4);
	}

	DrawFormatString(300, 500 - GetFontSize() / 2,
		GetColor(0, 0, 0),
		"ポート番号 : ");
	if (portId != -1)
	{
		DrawFormatString(450, 500 - GetFontSize() / 2,
			GetColor(0, 0, 0),
			"%d", portId);
	}

	// IPアドレスとポート番号が入力されている場合

	if (ipBuffer[3] != -1 && portId != -1)
	{
		DrawFormatString(300, 600 - GetFontSize() / 2,
			GetColor(0, 0, 0),
			"Connect");
	}
}

void SceneTitle::Connect()
{
	GameManager::networkHandle[0] = ConnectNetWork(ipData, portId);
	static HWDotween::TweenCallback* tweenCallback = nullptr;

	// �ڑ��Ɏ��s�����ꍇ�A��莞�Ԍ�ɍēx�ڑ�����݂�
	if (GameManager::networkHandle[0] == -1)
	{
		tweenCallback = HWDotween::DoDelay(60);
		tweenCallback->OnComplete([&]()
			{
				Connect();
			});
	}
	else
	{
		connectParameter = ConnectParameter::Complete;
		//tweenCallback->tweenEvent->isCancel = true;
	}
}
