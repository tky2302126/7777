#include "Board.h"

Board::Board()
{
	timer = -1;
	areaL = -1;
	areaR = -1;
	edgeNumLeft = -1;

	std::vector<std::thread> threads;

	for (int i = 0; i < SUIT_NUM * DECK_RANGE; ++i)
	{
		cards[i] = std::make_shared<Card>();
	}

#ifdef _DEBUG
	ShuffleCard();
	DistributeCard(4);
#endif // _DEBUG

}

Board::~Board()
{
	// カードの破棄
	for(auto card : cards)
	{
		card.reset();
	}
}

void Board::Draw()
{
	// 盤面の補助線の描画
	DrawBox(0, 0, 1920 / 2, 1080 / 2, GetColor(255, 255, 255), FALSE);


	// カードの描画
	MV1SetPosition(Card::modelHandle, Card::position_model);
	MV1SetRotationXYZ(Card::modelHandle, Card::rotate_model);
	MV1SetScale(Card::modelHandle, Card::scale_model);
	MV1DrawModel(Card::modelHandle);

	// テーブルのモデルの描画
	MV1DrawModel(modelHandle);
}

void Board::Move(Card& card)
{
}

void Board::Update()
{
	for (auto& card : cards)
	{
		card->ManualUpdate();
	}

	Draw();
}

void Board::ManualLoad()
{
	Card::modelHandle = MV1LoadModel("Assets/model/Cards/Cards.mv1");
	modelHandle = MV1LoadModel("Assets/model/Table/Table.mv1");

	// テーブの座標は固定のため、初期化時に設定
	MV1SetPosition(modelHandle, { 950,500,500 });
	MV1SetRotationXYZ(modelHandle, { (float)Deg2Rad(-90.0f),0,0 });
	MV1SetScale(modelHandle, { 1.5f,1.5f,1.5f });
}

void Board::OnCardClicked(Card* cardPtr)
{
	if(CanPlace(cardPtr))
	{
		// 配置処理を実行
	}
}

bool Board::CanPlace(Card* cardPtr)
{
	// 手札のカードか
	if (cardPtr->area == Area::Area_Board || cardPtr->area == Area::Area_Invailed) return false;
	// 制限エリア内か
	int num = cardPtr->number;
	if(areaL != -1) // エリア制限されているか
	{
		if(areaL > num || areaR < num)
		{
			return false;
		}
	}
	// 隣接するカードが置かれているか

	auto suit = cardPtr->suit;
	auto arrayNum = num - 1;
	if (boardData[suit][arrayNum - 1] == '1') return true;
	if (boardData[suit][arrayNum + 1] == '1') return true;

	return false;
}

void Board::ShuffleCard()
{
	// アニメーション(できたらやる)

	// データ
	// 最初に7を入れとく

	for(int i = 0; i< SUIT_NUM; ++i)
	{
		auto SevenFrameId = i * DECK_RANGE + 6;
		SwapCard(i, SevenFrameId);
	}

	// シャッフル
	std::random_device rd;
	std::mt19937 seed(rd());
	std::shuffle(cards + SUIT_NUM, std::end(cards), seed);

}

void Board::DistributeCard(int playerNum)
{
	// データ
	for(int i = 0; i < SUIT_NUM; ++i)
	{
		cards[i]->area = Area_Board;
	}

	for(int i = SUIT_NUM; i < SUIT_NUM * DECK_RANGE; ++i)
	{
		cards[i]->area = (Area)(i % playerNum + 2);
	}

#ifdef _DEBUG
	std::vector<std::shared_ptr<Card>> cardVec;
	for(auto card: cards)
	{
		if(card->area == Area_Player1)
		{
			cardVec.push_back(card);
		}
	}

	//
	float merginX = -8;
	float merginY = -25;
	std::sort(cardVec.begin(), cardVec.end());
	for(int i =0; i < cardVec.size(); ++i)
	{
		cardVec[i]->areaNumber = i;

		HWDotween::DoAction(&cardVec[i]->position, { merginX * i, merginY, 0 }, 30);
		HWDotween::DoAction(&cardVec[i]->rotate, { 0, 0, 180 }, 30);
	}


	
#endif // _DEBUG

	
}

void Board::SwapCard(int sendFrameId, int recvFrameId)
{
	std::swap(cards[sendFrameId], cards[recvFrameId]);
}

void Board::SwapCard(CardInfo& _a, CardInfo& _b)
{
	int a = _a.suit * DECK_RANGE + _a.number;
	int b = _b.suit * DECK_RANGE + _b.number;
	SwapCard(a, b);
}
