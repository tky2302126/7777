#include "Board.h"

Board::Board()
{
	timer = -1;
	areaL = -1;
	areaR = -1;
	edgeNumLeft = -1;

	// カードの作成
	for(int i = 0; i < 4; i++) // SuitNumで置き換えたい
	{
		for(int j = 1; j <= 13; j++) // 
		{
			
		}
	}
}

Board::~Board()
{
	// カードの破棄
	for(auto card : cards)
	{
		
	}
}

void Board::Draw()
{
}

void Board::Move(Card& card)
{
}

void Board::Update()
{
}
