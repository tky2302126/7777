#include "Board.h"

Board::Board()
{
	timer = -1;
	areaL = -1;
	areaR = -1;
	edgeNumLeft = -1;

	std::vector<std::thread> threads;

	// カードの作成
	for(int suit = 0; suit < SUIT_NUM; ++suit)
	{
		threads.emplace_back([this, suit]
			{
				for (int rank = 0; rank < DECK_RANGE; ++rank)
				{
					int FrameID = suit * DECK_RANGE + rank;
					cards[FrameID] = Card(FrameID);
				}
			});
	}

	for (auto& thread : threads)
	{
		thread.join();
	}
}

Board::~Board()
{
	// カードの破棄
	for(auto card : cards)
	{
		card.~Card();
	}
}

void Board::Draw()
{
#ifdef DEBUG

#endif // DEBUG

}

void Board::Move(Card& card)
{
}

void Board::Update()
{
	MV1SetPosition(cards[0].modelHandle, cards[0].GetPosition());
	MV1SetScale(cards[0].modelHandle, cards[0].GetScale());
	MV1DrawModel(cards[0].modelHandle);
	MV1DrawModel(modelHandle);
}

void Board::ManualLoad()
{
	cards[0].ManualLoad();
	modelHandle = MV1LoadModel("Assets/model/Table/Table.mv1");
}
