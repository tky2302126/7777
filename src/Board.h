#pragma once
#include "Card.h"
#include "define.h"

class Board
{
public:
#pragma region メソッド
	Board();
	~Board();
	void Draw();
	void Move(Card& card);
	void Update();
	void ManualLoad();
#pragma endregion


private:
#pragma region フィールド
	// 手札
	std::shared_ptr<Card> cards[SUIT_NUM * DECK_RANGE];
	// イベントタイマー
	int timer;
	// 制限エリア左端
	int areaL;
	// 制限エリア右端
	int areaR;
	// 盤面の左端の数字
	int edgeNumLeft;
	//盤面のモデル
	int modelHandle;
#pragma endregion

};

