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

	countDownLeftTop = Vector2Int();
	alpha = 0;

	auto portNum = GameManager::portNum;

	if(GameManager::role == Role::Client)
	{
		UDPSocketHandle[0] = MakeUDPSocket(-1);
	}
	if(GameManager::role == Role::Server)
	{
		for(auto& socket : UDPSocketHandle)
		{
			socket = MakeUDPSocket(UDP_PORT_NUM);
		}
	}
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
}

void SceneGame::KeyInputCallback(InputAction::CallBackContext _c)
{
}

void SceneGame::Update()
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
				//if (!boardCp->CanPlace(*card)) continue;

				// カードを置いた場合、一定時間経つまで置けなくする
				if (GetNowCount() - lastPlacedTime < (int)(PLACE_COOL_TIME * 1000)) break;
				{
					lastPlacedTime = GetNowCount();
				}

#ifdef _DEBUG
				boardCp->CardOnBoard(card);
				SendData data =
				{
					boardCp->score,
					boardCp->cards
				};
				if(GameManager::role == Role::Client)
				{
					UDPConnection::SendServer(data, UDPSocketHandle[0]);
				}

#else
				if(boardCp->CanPlace(*card))
				{
					boardCp->CardOnBoard(card);

				}
#endif // _DEBUG

				break;
			}
		}
	}

	if (GetNowCount() - lastPlacedTime < (int)(PLACE_COOL_TIME * 1000))
	{
		DrawFormatString(
			10, 30, GetColor(0, 255, 0),
			"coolTime = %d", (int)(PLACE_COOL_TIME * 1000) - (GetNowCount() - lastPlacedTime));
	}

	// カウントダウンのスプライトの描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawRectExtendGraph(760, 340, 1160, 740, countDownLeftTop.x, countDownLeftTop.y, 512, 512, CountDouwnGH, TRUE);
	if (isFade) { alpha -= fadeSpeed; }
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

#ifdef _DEBUG
	if(CheckHitKey(KEY_INPUT_C))
	{
		if(!isCountDown)
		{
			CountDown();
		}
	}
#endif // _DEBUG

}

void SceneGame::LateUpdate()
{
	if (GameManager::role == Role::Server)
	{
		int portNum = UDP_PORT_NUM;
		char* recvData[164];

		int ret = NetWorkRecvUDP(UDPSocketHandle[0], &GameManager::IPAdress[0], &portNum,
			recvData, 164, TRUE);

		static int debug = -999;

		//! 受け取ったカードデータのデコード先
		static Card decodeData[SUIT_NUM * DECK_RANGE];
		if (ret > 0)
		{
			debug = ret;

			int sendTime = -1;

			// 送信時刻を書き込み
			sendTime = *(int*)recvData;

			//! 受け取ったカードデータ
			CardData* cdp = (CardData*)(recvData + sizeof(int) + sizeof(int));


			// カードデータをデコードする
			for (int i = 0; i < SUIT_NUM * DECK_RANGE; ++i)
			{
				decodeData[i].suit = (Suit)(cdp[i].data / 13);
				decodeData[i].number = cdp[i].data % 13 + 1;
				decodeData[i].area = static_cast<Area>(cdp[i].area);
				decodeData[i].areaNumber = cdp[i].areaNumber;
			}

			// デコードしたデータを記録
		}

		int index = 0;
		for (auto card : decodeData)
		{
			if (card.area == Area_Player1)
			{
				DrawFormatString(
					100, 20 * index++, GetColor(0, 255, 0),
					"SUIT = %d, NUMBER", card.suit, card.number);
			}
		}

		DrawFormatString(
			10, 110, GetColor(0, 255, 0),
			"受信データサイズ = %d", debug);
	}
	if (GameManager::role == Role::Client)
	{
	}

	DrawFormatString(
		10, 60, GetColor(0, 255, 0),
		"PlayerID = %d", GameManager::playerId);
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



