#include "Board.h"

Board::Board()
{
	timer = -1;
	areaL = -1;
	areaR = -1;
	edgeNumLeft = -1;
	score = 0;

	memset(boardData, 0, sizeof(boardData));

	for (int i = 0; i < SUIT_NUM * DECK_RANGE; ++i)
	{
		cards[i] = std::make_shared<Card>();
	}



	// カードの初期配置(手札の配分と7のセット)
	// ホストの場合のみ行う
	if (GameManager::role == Role::server)
	{
		Shuffle();
	}
	//! クライアント側は山札の更新を待つ
	Distribute(4);
	SortHand();
//	ShowHand((Area)(GameManager::playerId + 1));
	ShowHand(Area::Area_Player1);
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
	// テーブルのモデルの描画
	MV1DrawModel(modelHandle);

	//DrawBox(
	//	1920 / 2 - CARD_WIDTH / 2,
	//	1080 / 2 - CARD_HEIGHT / 2,
	//	1920 / 2 + CARD_WIDTH / 2,
	//	1080 / 2 + CARD_HEIGHT / 2,
	//	GetColor(255, 255, 255), FALSE);


	// カードの描画
	MV1SetPosition(Card::modelHandle, Card::position_model);
	MV1SetRotationXYZ(Card::modelHandle, Card::rotate_model);
	MV1SetScale(Card::modelHandle, Card::scale_model);
	MV1DrawModel(Card::modelHandle);

}

void Board::Move(Card& card)
{
}

void Board::Update()
{
	Draw();

	for (auto& card : cards)
	{
		card->ManualUpdate();
	}

	for (int i = 0; i < SUIT_NUM; ++i)
	{
		for (int j = 0; j < DECK_RANGE; ++j)
		{
			DrawBox(
				DEFAULT_CARD_POSITION.x + (FIELD_BEZEL.x + CARD_WIDTH) * j,
				DEFAULT_CARD_POSITION.y + (FIELD_BEZEL.y + CARD_HEIGHT) * i,
				DEFAULT_CARD_POSITION.x + (FIELD_BEZEL.x + CARD_WIDTH) * j + CARD_WIDTH,
				DEFAULT_CARD_POSITION.y + (FIELD_BEZEL.y + CARD_HEIGHT) * i + CARD_HEIGHT,
				GetColor(255, 255, 255), FALSE);
		}
	}
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
void Board::AddScore(int value)
{
	score += value;
}
bool Board::CanPlace(Card* cardPtr)
{
	// 手札のカードか
	if (cardPtr->area == Area::Area_Board || cardPtr->area == Area::Area_Invailed) return false;
	// 制限エリア内か
	int num = cardPtr->number;
	if (areaL != -1) // エリア制限されているか
	{
		if (areaL > num || areaR < num)
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

void Board::Shuffle()
{
	//! シャッフルする配列
	std::vector<int> v;

	for (int i = 0; i < SUIT_NUM * DECK_RANGE; ++i)
		v.push_back(i);

	// シャッフル
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::shuffle(v.begin(), v.end(), engine);

	// 領域座標を更新
	for (int i = 0; i < v.size(); ++i)
		cards[i]->areaNumber = v[i];
}

void Board::Distribute(int playerNum)
{
	for(auto card : cards)
	{
		card->area = (Area)(card->areaNumber % playerNum + 2);
	}

	for (int i = 0; i < playerNum; ++i)
	{
		std::vector<std::shared_ptr<Card>> playerHand;
		for (auto card : cards)
		{
			if (card->area == (Area)(i + 2))
			{
				playerHand.push_back(card);
			}
		}
		handData.push_back(playerHand);
	}
}

void Board::ShowHand(Area playerArea)
{
	int index = (int)playerArea - 2;
	std::vector<std::shared_ptr<Card>> handVec;
	handVec = handData[index];

	float merginX = -8;
	float merginY = -25;
	for (auto it = handVec.begin(); it != handVec.end(); ++it)
	{
		HWDotween::DoAction(&(*it)->position, { merginX * (*it)->areaNumber, merginY, 0 }, 30);
		HWDotween::DoAction(&(*it)->rotate, { 0, 0, 180 }, 30);
	}
}

void Board::SortHand()
{
	std::vector<std::shared_ptr<Card>> handVec;
	std::copy(handData[0].begin(), handData[0].end(), 
		std::back_inserter(handVec));

	std::sort(handVec.begin(), handVec.end(), [](std::shared_ptr<Card> a, std::shared_ptr<Card> b) {
		if (a->number == b->number)
			return a->suit < b->suit;
		return a->number < b->number;
		});

	for (int i = 0; i < handVec.size(); ++i)
	{
		handVec[i]->areaNumber = i;
	}
}
