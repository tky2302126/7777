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
	static Card* selectedCard = nullptr;
	static bool isSelect = false;
	static HWDotween::TweenCallback* callback = nullptr;
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
				selectedCard = card.get();
				HWDotween::DoDelay(60)->OnComplete([&]
					{
						if (selectedCard)
							selectedCard = nullptr;
					});

				break;
			}
		}
	}

	if(selectedCard)
	{
		DrawFormatString(
			10, 10, GetColor(0, 255, 0),
			"SUIT = %d, Number = %d", (int)selectedCard->suit, selectedCard->number);
	}
}

void SceneGame::LateUpdate()
{
}



