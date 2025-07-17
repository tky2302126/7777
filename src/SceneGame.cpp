#include "SceneGame.h"

#define DEBUG

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

	// イベント告知用のコールバック関数を登録
	boardCp->SubscribeEventCallback(std::bind(&SceneGame::SendEventData, this, std::placeholders::_1));

	countDownLeftTop = Vector2Int();
	alpha = 0;

	GameManager::portNum = UDP_PORT_NUM;

	if(GameManager::role == Role::Client)
	{
		//UDPSocketHandle[0] = MakeUDPSocket(-1);
		UDPSocketHandle[0] = MakeUDPSocket(UDP_PORT_NUM);
	}
	if(GameManager::role == Role::Server)
	{
		for(auto& socket : UDPSocketHandle)
		{
			socket = MakeUDPSocket(UDP_PORT_NUM);
		}
	}

	outputfile_c = std::ofstream("client.txt");
	outputfile_s = std::ofstream("server.txt");
	
	std::ofstream f("connect.txt");

	f << "socket : " << UDPSocketHandle[0] << "\n";
	f <<"IP Address [" << 0 << "] : " << (int)GameManager::IPAdress[0].d1 << "."
		<< (int)GameManager::IPAdress[0].d2 << "."
		<< (int)GameManager::IPAdress[0].d3 << "."
		<< (int)GameManager::IPAdress[0].d4 << "\n";
	f << "Port Number : " << GameManager::portNum << "\n";
}

SceneGame::~SceneGame()
{
	board.reset();
	input->DeleteCallBack("cursor", callBackId);
}

void SceneGame::LoadComplete()
{
	boardCp->ManualLoad();
	CountDouwnGH = LoadGraph("Assets/UI/CountDown.png");
	gaugeHandle = LoadGraph("Assets/UI/TestCircle.png");


	if (GameManager::role == Role::Server)
	{
		SendInitData();
		isGame = true;
	}
	///
	CountDown();

	if(GameManager::role == Role::Server)
	{
		HWDotween::DoDelay(300)->OnComplete([&]{
				boardCp->DrawingEvent();});
	}
}

void SceneGame::KeyInputCallback(InputAction::CallBackContext _c)
{
}

void SceneGame::Update()
{
	// clientの場合、最初のデータ受信までゲーム開始を待機
	if (GameManager::role == Role::Client)
	{
		if (!ReceiveInitData())return;
	}
			DrawFormatString(
				10, 60, GetColor(255, 255, 255),
				"接続人数 = %d : %d", GameManager::connectNum, boardCp->handData.size());

			for (int i = 0; i < GameManager::connectNum; ++i)
	{
		if (i != GameManager::playerId)
		{
			DrawFormatString(
				10, 100 + 30 * i, GetColor(255, 255, 255),
				"Player%d = %d : score = %d", i, boardCp->handData[i].size(), GameManager::score[i]);
		}
		else
		{
			DrawFormatString(
				10, 100 + 30 * i, GetColor(0, 255, 0),
				"Player%d = %d : score = %d", i, boardCp->handData[i].size(), boardCp->score);
		}
	}

	// カウントダウンのスプライトの描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawRectExtendGraph(760, 340, 1160, 740, countDownLeftTop.x, countDownLeftTop.y, 512, 512, CountDouwnGH, TRUE);
	if (isFade) { alpha -= fadeSpeed; }
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

#ifdef _DEBUG
	/*if(CheckHitKey(KEY_INPUT_A))
	{
		boardCp->MoveArea(true, 1);
	}
	if(CheckHitKey(KEY_INPUT_D))
	{
		boardCp->MoveArea(false, 1);
	}*/
	auto edge = boardCp->cards[0]->leftEdgeNum;
	DrawFormatString(0, 900, 65535, "leftEdgeNum : %d", edge);

#endif // _DEBUG

}

void SceneGame::LateUpdate()
{
	if (!isGame || isCountDown)return;

	if (GameManager::role == Role::Server)
	{
		if (ReceiveUpdateData_Client() == TRUE)
		{
			// 受信したら全clientに送信
			SendData data =
			{
				boardCp->score,
				boardCp->cards
			};
			UDPConnection::SendClients(data, UDPSocketHandle);
		}
	}
	else if (GameManager::role == Role::Client)
	{
		ReceiveUpdateData_Server();
	}

	// カードの設置関係
	CheckMouseInput();

	DrawFormatString(
		550, 20, GetColor(0, 255, 0),
		"PlayerID = %d", GameManager::playerId);

	if (GetNowCount() - lastPlacedTime < (int)(boardCp->coolTime * 1000))
	{
		float percent = (float)(GetNowCount() - lastPlacedTime) / (float)(boardCp->coolTime * 1000);
		percent *= 100;

		DrawCircleGauge(1920 / 2, 900,
			100.0 - percent,
			gaugeHandle, 0.0);
	}
}

void SceneGame::SendEventData(EventData& _sendData)
{
	UDPConnection::SendEventData(_sendData, UDPSocketHandle);
}

void SceneGame::CountDown()
{
	if (isCountDown) return;
	isCountDown = true;
	alpha = 255;

	Vector2Int CountDownFrames[] =
	{
		{0,   0},
		{511, 0},
		{0, 511},
		{511,511}
	};
	const int totalSteps = sizeof(CountDownFrames) / sizeof(CountDownFrames[0]);
	auto currentIndex = std::make_shared<int>(0);
	auto doCountStep = std::make_shared<std::function<void()>>();

	*doCountStep = [this, currentIndex, CountDownFrames, doCountStep]() 
		{
			if(*currentIndex >= totalSteps)
			{
				// カウントダウン終了
				alpha = 0;
				isCountDown = false;
				return;
			}

			countDownLeftTop = CountDownFrames[*currentIndex];
			alpha = 255;
			isFade = false;

			HWDotween::DoDelay(30)->OnComplete([this, currentIndex, CountDownFrames, doCountStep]()
				{
					isFade = true;
					HWDotween::DoDelay(30)->OnComplete([this, currentIndex, CountDownFrames, doCountStep]()
						{
							(*currentIndex)++;
							(*doCountStep)();
						});
				});

		};

	(*doCountStep)();

}

void SceneGame::CheckMouseInput()
{
	static Mouse mouse;
	mouse.MouseInfoUpdate();

	if (mouse.IsMouseRightButtonClicked())
	{
		for (auto& card : boardCp->cards)
		{
			auto mousePos = mouse.GetMouseInfo().position;

			if (card->collisionCenter.x - CARD_COLLISION_WIDTH <= mousePos.x &&
				card->collisionCenter.x + CARD_COLLISION_WIDTH >= mousePos.x &&
				card->collisionCenter.y - CARD_COLLISION_HEIGHT <= mousePos.y &&
				card->collisionCenter.y + CARD_COLLISION_HEIGHT >= mousePos.y)
			{
				// カードが置けるかどうかチェック
				
#ifdef DEBUG
				if (card->area != Area_Player1) continue;
#else
				if (card->area != (Area)(GameManager::playerId + 2)) continue;
				if (!boardCp->CanPlace(*card)) continue;
#endif // DEBUG

				// カードを置いた場合、一定時間経つまで置けなくする
				if (GetNowCount() - lastPlacedTime < (int)(boardCp->coolTime * 1000)) break;

				lastPlacedTime = GetNowCount();

				boardCp->CardOnBoard(card, GameManager::playerId);
				boardCp->AddScore(boardCp->CalculateScore(card));
				// 手札の並べなおし
#ifdef DEBUG
				boardCp->ShowHand(Area::Area_Player1);
#else
				boardCp->ShowHand((Area)(GameManager::playerId + 2));
#endif // DEBUG

				if (GameManager::role == Role::Client)
				{
					UDPConnection::SendServer(*card, boardCp->score,UDPSocketHandle[0]);
				}
				if (GameManager::role == Role::Server)
				{
					SendData data =
					{
						boardCp->score,
						boardCp->cards
					};

					UDPConnection::SendClients(data, UDPSocketHandle);
				}
				
				break;
			}
		}
	}
}

int SceneGame::ReceiveInitData()
{
	// 一度受信したら、以降はtrue
	static int ret = FALSE;

	if (ret) return TRUE;

	//! 受け取ったカードデータのデコード先
	static Card decodeData[SUIT_NUM * DECK_RANGE];
	int sendTime = -1;
	int sendId = -1;

	if (CheckNetWorkRecvUDP(UDPSocketHandle[0]) == TRUE)
	{
		int portNum = UDP_PORT_NUM;
		unsigned char recvData[250];

		NetWorkRecvUDP(UDPSocketHandle[0], NULL, NULL,
			recvData, 250, FALSE);

		// 送信時刻を書き込み
		sendTime = *(int*)recvData + sizeof(SendDataType);
		sendId = *(int*)(recvData + sizeof(SendDataType) + sizeof(int));

		//! 受け取ったカードデータ
		CardData* cdp = (CardData*)(recvData + sizeof(SendDataType) + sizeof(int) * 6);

		// カードデータをデコードする
		for (int i = 0; i < SUIT_NUM * DECK_RANGE; ++i)
		{
			decodeData[i].suit = (Suit)(cdp[i].data / 13);
			decodeData[i].number = cdp[i].data % 13 + 1;
			decodeData[i].area = static_cast<Area>(cdp[i].area);
			decodeData[i].areaNumber = cdp[i].areaNumber;
		}
		// デコードしたデータで上書き
		for (int i = 0; i < SUIT_NUM * DECK_RANGE; ++i)
		{
			boardCp->cards[i]->suit = decodeData[i].suit;
			boardCp->cards[i]->number = decodeData[i].number;
			boardCp->cards[i]->area = decodeData[i].area;
			boardCp->cards[i]->areaNumber = decodeData[i].areaNumber;
		}

		for (int i = 0; i < MAX_PLAYER; ++i)
		{
			std::vector<std::shared_ptr<Card>> playerHand;
			for (auto card : boardCp->cards)
			{
				if (card->area == (Area)(i + 2))
				{
					playerHand.push_back(card);
				}
			}
			boardCp->handData.push_back(playerHand);
		}

#ifdef DEBUG
		boardCp->SortHand(Area::Area_Player1);
		boardCp->ShowHand(Area::Area_Player1);
#else
		boardCp->SortHand((Area)(GameManager::playerId + 2));
		boardCp->ShowHand((Area)(GameManager::playerId + 2));
#endif // DEBUG

		ret = 1;
		isGame = true;
	}

	return ret;
}

void SceneGame::SendInitData()
{
	SendData data =
	{
		boardCp->score,
		boardCp->cards
	};

	UDPConnection::SendClients(data, UDPSocketHandle);
}

int SceneGame::ReceiveUpdateData_Client()
{
	int recvCount = 0;

	static bool isRecv = false;

#ifdef DEBUG
	if (isRecv)
		DrawFormatString(
			10, 60, GetColor(0, 255, 0),
			"Recv");
	else
		DrawFormatString(
			10, 60, GetColor(0, 255, 0),
			"なし");
#endif // DEBUG



	for (int i = 0; i < MAX_PLAYER; ++i)
	{
		// 受信データのチェック
		if (CheckNetWorkRecvUDP(UDPSocketHandle[i]) == TRUE) 
		{
			outputfile_s << "受信 -> " << i << "\n";

			isRecv = true;
			HWDotween::DoDelay(120)->OnComplete([&] {isRecv = false; });

			// 受信データがあったらカウントアップ
			recvCount++;
			//! 受け取ったカードデータのデコード先
			Card decodeData;
			//! 送信時刻
			int sendTime = -1;

			int portNum = UDP_PORT_NUM;
			unsigned char recvData[15];

			int ret = NetWorkRecvUDP(UDPSocketHandle[i], NULL, NULL,
				recvData, 15, FALSE);

			// 送信時刻を書き込み
			sendTime = *(int*)recvData;
			// 送信時刻を書き込み
			GameManager::score[i + 1] = *(int*)(recvData + sizeof(int) * 2);

			//! 受け取ったカードデータ
			CardData* cdp = (CardData*)(recvData + sizeof(int) * 3);

			// カードデータをデコードする
			decodeData.suit = (Suit)(cdp->data / 13);
			decodeData.number = cdp->data % 13 + 1;
			decodeData.area = static_cast<Area>(cdp->area);
			decodeData.areaNumber = cdp->areaNumber;

			// デコードしたデータと現在のデータを比較し、変更点を反映する
			for (int j = 0; j < SUIT_NUM * DECK_RANGE; ++j)
			{
				if (decodeData.suit == boardCp->cards[j]->suit &&
					decodeData.number == boardCp->cards[j]->number &&
					decodeData.area == Area_Board)
				{
					boardCp->CardOnBoard(boardCp->cards[j], boardCp->cards[j]->area - 2);
				}
			}
		}
	}

	return recvCount > 0 ? TRUE : FALSE;
}

int SceneGame::ReceiveUpdateData_Server()
{
	static bool isRecv = false;

#ifdef DEBUG
	if (isRecv)
		DrawFormatString(
			10, 60, GetColor(0, 255, 0),
			"Recv");
	else
		DrawFormatString(
			10, 60, GetColor(0, 255, 0),
			"なし");
#endif // DEBUG


	// 受信データなし
	if (CheckNetWorkRecvUDP(UDPSocketHandle[0]) != TRUE) return 0;

	isRecv = true;
	HWDotween::DoDelay(120)->OnComplete([&] {isRecv = false; });

	//! 送信データ種別
	SendDataType dataType = SendDataType::UnDefine;

	int portNum = UDP_PORT_NUM;
	unsigned char recvData[250];

	int ret = NetWorkRecvUDP(UDPSocketHandle[0], NULL, NULL,
		recvData, 250, FALSE);

	outputfile_c << "受信 -> \n";
	outputfile_c << ret;	

	// 受信したデータ種別
	dataType = *(SendDataType*)recvData;

	switch (dataType)
	{
	case SendDataType::GameData:
		ReceivingGameData(recvData + 1);
		break;
	case SendDataType::EventData:
		ReceivingEventData(recvData + 1);
		break;
	}

	return 1;
}

void SceneGame::ReceivingGameData(unsigned char* _recvData)
{
	//! 受け取ったカードデータのデコード先
	static Card decodeData[SUIT_NUM * DECK_RANGE];
	//! 送信時刻
	int sendTime = -1;
	//! 送信ID
	int sendId = -1;

	sendTime = *(int*)_recvData;
	sendId = *(int*)(_recvData + sizeof(int));

	GameManager::score[0] = *(int*)(_recvData + sizeof(int) * 2);
	GameManager::score[1] = *(int*)(_recvData + sizeof(int) * 3);
	GameManager::score[2] = *(int*)(_recvData + sizeof(int) * 4);
	GameManager::score[3] = *(int*)(_recvData + sizeof(int) * 5);

	//! 受け取ったカードデータ
	CardData* cdp = (CardData*)(_recvData + sizeof(int) * 6);

	// カードデータをデコードする
	for (int i = 0; i < SUIT_NUM * DECK_RANGE; ++i)
	{
		decodeData[i].suit = (Suit)(cdp[i].data / 13);
		decodeData[i].number = cdp[i].data % 13 + 1;
		decodeData[i].area = static_cast<Area>(cdp[i].area);
		decodeData[i].areaNumber = cdp[i].areaNumber;
	}

	//
	// デコードしたデータと現在のデータを比較し、変更点を反映する
	//

	for (int i = 0; i < SUIT_NUM * DECK_RANGE; ++i)
	{
		if (decodeData[i].area == Area_Board &&
			boardCp->cards[i]->area != Area_Board)
		{
			boardCp->CardOnBoard(boardCp->cards[i], (int)(boardCp->cards[i]->area - 2));
		}
	}
}

void SceneGame::ReceivingEventData(unsigned char* _recvData)
{
	//! 受け取ったイベントデータ
	EventData* eventData = (EventData*)(_recvData);


	std::ofstream outputfile("client_Event.txt");
	outputfile << (int)eventData->eventType << "\n";
	outputfile << (int)eventData->data << "\n";
	outputfile.close();

	// ダイスロール
	switch ((int)eventData->eventType)
	{
	case (int)Event::Event_CountDown:
	{
		break;
	}
	case (int)Event::Event_IsAgari:
	{
		break;
	}
	case (int)Event::Event_Bomb:
	{
		break;
	}
	case (int)Event::Event_Fever:
	{
		boardCp->dice->Roll(0);
		boardCp->FeverTime();
	}
		break;
	case (int)Event::Event_LuckyNumber:
	{
		boardCp->dice->Roll(1);
		boardCp->LuckyNumber((int)(*(unsigned char*)eventData));
		break;
	}
	case (int)Event::Event_LimitArea:
	{
		boardCp->dice->Roll(2);
		int areaL = (int)eventData->data % DECK_RANGE;
		int areaR = ((int)eventData->data / DECK_RANGE) + 1;
		boardCp->LimitArea(areaL, areaR);
		break;
	}
	case (int)Event::Event_MoveArea:
	{
		outputfile << "D = 3\n";
		outputfile << (eventData->data >> 7) << "\n";
		outputfile << ((int)eventData->data & 0x7F) << "\n";
		outputfile.close();

		boardCp->dice->Roll(3);
		bool isLeft = eventData->data >> 7;
		int num = (int)eventData->data & 0x7F;
		boardCp->MoveArea(isLeft, num);
		break;
	}
	case (int)Event::Event_ShuffleHand:
	{
		boardCp->dice->Roll(4);
		boardCp->ShuffleHand(eventData->data);
		break;
	}
	}
}
