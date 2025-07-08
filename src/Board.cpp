#include "Board.h"

Board::Board()
{
	timer = -1;
	areaL = -1;
	areaR = -1;
	edgeNumLeft = -1;

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
	if (CheckHitKey(KEY_INPUT_RETURN))
		Shuffle();

	Draw();

	for (auto& card : cards)
	{
		card->ManualUpdate();
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
