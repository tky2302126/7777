#pragma once
#include "Card.h"

class Board
{
public:
#pragma region メソッド
	Board();
	~Board();
	void Draw();
	void Move(Card& card);
	void Update();
#pragma endregion


private:
#pragma region フィールド
	// 手札
	Card cards[52];
	// イベントタイマー
	int timer;
	// 制限エリア左端
	int areaL;
	// 制限エリア右端
	int areaR;
	// 盤面の左端の数字
	int edgeNumLeft;
#pragma endregion

};

