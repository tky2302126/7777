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

void Board::OnCardClicked(Card*)
{
}
