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

	int a = 0;

	//// カードの作成
	//for(int suit = 0; suit < SUIT_NUM; ++suit)
	//{
	//	threads.emplace_back([this, suit]
	//		{
	//			for (int rank = 0; rank < DECK_RANGE; ++rank)
	//			{
	//				int FrameID = suit * DECK_RANGE + rank;
	//				cards[FrameID] = Card(FrameID);
	//			}
	//		});
	//}

	//for (auto& thread : threads)
	//{
	//	thread.join();
	//}
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
#ifdef DEBUG

#endif // DEBUG

}

void Board::Move(Card& card)
{
}

void Board::Update()
{
	MV1SetPosition(Card::modelHandle, cards[0]->GetPosition());
	MV1SetScale(Card::modelHandle, cards[0]->GetScale());
	MV1DrawModel(Card::modelHandle);
	MV1DrawModel(modelHandle);
}

void Board::ManualLoad()
{
	Card::modelHandle = MV1LoadModel("Assets/model/Cards/Cards.mv1");
	modelHandle = MV1LoadModel("Assets/model/Table/Table.mv1");
}
