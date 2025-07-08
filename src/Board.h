#pragma once
#include "Card.h"
#include "define.h"

class Board : public HWComponent
{
public:
#pragma region publicメンバ変数
	// 手札
	std::shared_ptr<Card> cards[SUIT_NUM * DECK_RANGE];
#pragma endregion

#pragma region publicメソッド
	Board();
	~Board();
	void Draw();
	void Move(Card& card);
	void Update()override;
	void ManualLoad();
#pragma endregion

#pragma region privateメンバ変数
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
	//! 盤面のデータ
	char boardData[SUIT_NUM][DECK_RANGE];
	//! 手札のデータ
	char hundData[PLAYER_NUM][DECK_RANGE];
#pragma endregion

#pragma region privateメソッド
private:
	void Shuffle();
#pragma endregion
};

