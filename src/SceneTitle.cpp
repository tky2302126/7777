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

	inputHandle = MakeKeyInput(3, TRUE, FALSE, TRUE);

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

		if (it->keyCode == PAD_INPUT_DOWN)
		{
			++selectIndex;

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
		DrawFormatString(450, 1000, GetColor(0, 0, 0), "Complete!");
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
		SetActiveKeyInput(inputHandle);
		SetKeyInputString("", inputHandle);
	}
	else if(selectIndex == 3)
	{
		connectParameter = ConnectParameter::Wait;
		Connect();
	}
}

void SceneTitle::ServerInputForm()
{
	connectParameter = ConnectParameter::Wait;
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
	networkHandle = ConnectNetWork(ipData, portId);
	static HWDotween::TweenCallback* tweenCallback = nullptr;

	// �ڑ��Ɏ��s�����ꍇ�A��莞�Ԍ�ɍēx�ڑ�����݂�
	if (networkHandle == -1)
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
		tweenCallback->tweenEvent->isCancel = true;
	}
}

void SceneTitle::ServerInit()
{
	int portNum = 7777;
	PreparationListenNetWork(portNum);
	for(auto N: NetWorkHandles)
	{
		N = -1;
	}
	
}

void SceneTitle::ServerUpdate()
{
	int ConnectedNum = 0;
	for(int NetHandle : NetWorkHandles)
	{
		if (NetHandle > 0) ConnectedNum++;
	}

	// 接続
	if(ConnectedNum >=3)
	{
		StopListenNetWork();
	}
	else
	{
		Connect();
	}

	// 受信
	if(ConnectedNum >0)
	{
		DisConnect();
		RecieveNetData();
	}
}

void SceneTitle::ConnectServer()
{
	int portNum = 7777;
	PreparationListenNetWork(portNum);
	for(int NetHandle : NetWorkHandles)
	{
		if (NetHandle != -1) continue;
		NetHandle = GetNewAcceptNetWork();
	}
}

void SceneTitle::DisConnect()
{
	int LostHandle = 0;
	LostHandle = GetLostNetWork();

	for(auto NetHandle: NetWorkHandles)
	{
		if(NetHandle == LostHandle)
		{
			NetHandle = -1;
		}
	}


}

void SceneTitle::RecieveNetData()
{
	for(auto NetHandle : NetWorkHandles)
	{
		if (NetHandle == -1) continue; // NetHandle が登録されていないとき、スキップ
		IPDATA Ip;            // 接続先ＩＰアドレスデータ
		// 接続してきたマシンのＩＰアドレスを得る
		GetNetWorkIP(NetHandle, &Ip);
	
		// 取得していない受信データ量が０のときは終了
		if (GetNetWorkDataLength(NetHandle) == 0) continue;

		int DataLength;
		unsigned char StrBuf[256];

		// データ受信
		DataLength = GetNetWorkDataLength(NetHandle);    // データの量を取得
		NetWorkRecv(NetHandle, StrBuf, DataLength);    // データをバッファに取得
		// バッファをスタックに追加
		// デコードしてupdateにイベントを追加
		
	}

}



