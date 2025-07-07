#pragma once
#include "Card.h"
#include "define.h"

class Board : public HWComponent
{
public:
#pragma region publicメンバ変数
#pragma endregion

#pragma region メソッド
	Board();
	~Board();
	void Draw();
	void Move(Card& card);
	void Update()override;
	void ManualLoad();
	void OnCardClicked(Card*);
#pragma endregion


private:
#pragma region privateメンバ変数
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
	//! 盤面のデータ
	char boardData[SUIT_NUM][DECK_RANGE];
#pragma endregion

#pragma region privateメソッド
	/// <summary>
	/// カードが設置可能か判定する
	/// </summary>
	/// <param name="cardPtr">判定するカード</param>
	bool CanPlace(Card* cardPtr);
#pragma endregion

};

