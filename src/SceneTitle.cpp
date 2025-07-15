#include "SceneTitle.h"

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneTitleの実装ファイル
*/

#define DEBUG

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

	// タイトル画面の読み込み
	gh_title = LoadGraph("Assets/Sprite/title8.png");
	gh_titleBack = LoadGraph("Assets/Sprite/title_back2.png");
	gh_titleLogo = LoadGraph("Assets/Sprite/title_Logo3.png");

#ifdef DEBUG
	ipData.d1 = ipBuffer[0] = 10;
	ipData.d2 = ipBuffer[1] = 204;
	ipData.d3 = ipBuffer[2] = 6;
	ipData.d4 = ipBuffer[3] = 89;

	portId = 7777;
#endif // DEBUG

	if(GameManager::role == Role::Server)
		for (auto& socket : GameManager::syncUDPSocketHandle)
			socket = MakeUDPSocket(SYNC_UDP_PORT_NUM);
	if (GameManager::role == Role::Client)
		GameManager::syncUDPSocketHandle[0] = MakeUDPSocket(SYNC_UDP_PORT_NUM);
}

SceneTitle::~SceneTitle()
{
	input->DeleteCallBack("cursor", callBackId);
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
			if (GameManager::role == Role::Server)
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

			if (GameManager::role == Role::Client)
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
			if (GameManager::role == Role::Server)
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
	// 画面背景描画
	DrawGraph(0, 0, gh_titleBack, TRUE);
	//　背景の柄を動かす
	offsetX--;
	if (offsetX <= -tileSize) {
		offsetX = 0;
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);  // 描画ブレンドモードをアルファブレンドにする
	for (int y = 0; y < tilesY; ++y) {
		for (int x = 0; x <= tilesX; ++x) {
			// 画面柄描画
			DrawGraph(x * tileSize + offsetX, y * tileSize, gh_title, TRUE);

		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 描画モードをノーブレンドにする
	// ロゴを画面中央に描画する
	int screenWidth = 1920;
	int logoX, logoY;
	GetGraphSize(gh_titleLogo, &logoX, &logoY);
	DrawGraph((screenWidth-logoX)/2, 200, gh_titleLogo, TRUE);
	

	if (connectParameter == ConnectParameter::Wait)
	{
		DrawFormatString(450, 800, GetColor(0, 0, 0), "Connecting");
	}
	else if (connectParameter == ConnectParameter::Connected)
	{
		if (GameManager::role == Role::Server)
		{
			GameManager::playerId = 0;

			// clientに接続人数とPlayerIDを送信
			// !タイミングがよくなさそう
			for (int i = 0; i < GameManager::connectNum; i++)
			{
				unsigned char sendData = GameManager::connectNum * 10 + i + 1;
				NetWorkSend(GameManager::networkHandle[i],
					&sendData, sizeof(sendData));
				GetNetWorkIP(GameManager::networkHandle[i], &GameManager::IPAdress[i]);
			}

			GameManager::portNum = portId;

			connectParameter = ConnectParameter::Complete;
		}
		else if (GameManager::role == Role::Client)
		{
			unsigned char recvData = 0;
			NetWorkRecv(GameManager::networkHandle[0],
				&recvData, sizeof(char));

			if (recvData != 0)
			{
				GameManager::connectNum = (int)(recvData / 10);
				GameManager::playerId = (int)(recvData % 10);
				GetNetWorkIP(GameManager::networkHandle[0], &GameManager::IPAdress[0]);
				GameManager::portNum = portId;

				connectParameter = ConnectParameter::Complete;
			}
		}

	}
	else if (connectParameter == ConnectParameter::Complete)
	{
		DrawFormatString(450, 800, GetColor(0, 0, 0), "Complete!");
		SceneChangeAsync(SceneTag::Game);
	}
}

void SceneTitle::LateUpdate()
{
	{
		cursor.ManualUpdate();

		DrawFormatString(300, 300 - GetFontSize() / 2,
			GetColor(0, 0, 0),
			"Role       : ");
		if (GameManager::role == Role::Server)
			DrawFormatString(450, 300 - GetFontSize() / 2, GetColor(0, 0, 0), "Sever");
		else
			DrawFormatString(450, 300 - GetFontSize() / 2, GetColor(0, 0, 0), "Client");
	}

	if (GameManager::role == Role::Server)
		ServerInputForm();
	if (GameManager::role == Role::Client)
		ClientInputForm();
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

	if (selectIndex == 0)
	{
		GameManager::role == Role::Server ? GameManager::role = Role::Client : GameManager::role = Role::Server;
		isSelect = false;
		cursor.SetColor(GetColor(100, 100, 255));
		cursor.SetTargetScale({ 100,20,0 });
		return;
	}
	else if (selectIndex == 1)
	{
		for (int i = 0; i < 4; ++i)
			ipBuffer[i] = -1;
		SetActiveKeyInput(inputHandle);
		SetKeyInputString("", inputHandle);
	}
	else if (selectIndex == 2)
	{
		if (GameManager::role == Role::Server)
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
	else if (selectIndex == 3)
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
	int num = 0;
	for (int i = 0; i < MAX_PLAYER - 1; ++i)
		if (GameManager::networkHandle[i] != -1)
			++num;
	GameManager::connectNum = num + 1;
	DrawFormatString(300, 700 - GetFontSize() / 2,
		GetColor(0, 0, 0),
		"参加人数 : %d/%d", GameManager::connectNum, MAX_PLAYER);


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
		for (index = 0; index < 3; ++index)
			if (GameManager::networkHandle[index] == -1)
				break;

		// 新しい接続があったらそのネットワークハンドルを得る
		GameManager::networkHandle[index] = GetNewAcceptNetWork();
		// 接続先にPlayerIDを送信
		NetWorkSend(GameManager::networkHandle[index],
			&index, sizeof(int));

		if (GameManager::networkHandle[MAX_PLAYER - 2] != -1)
			connectParameter = ConnectParameter::Connected;
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
		connectParameter = ConnectParameter::Connected;
	}
}



