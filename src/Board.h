#pragma once
#include "Card.h"
#include "define.h"

struct CardInfo
{
	Suit suit;
	int number;
};

class Board : public HWComponent
{
public:
#pragma region publicメンバ変数
	// 手札
	std::shared_ptr<Card> cards[SUIT_NUM * DECK_RANGE];
	//! ゲームの開始時間(最初のカード情報を受信した時刻を開始時刻とする)
	int statTime = -1;
#pragma endregion

#pragma region publicメソッド
	Board();
	~Board();
	void Draw();
	void Move(Card& card);
	void Update()override;
	void ManualLoad();
	bool IsAgari() const { return handData.size() == 0; }
	int GetScore() const { return score; }
	void AddScore(int value);
	/// <summary>
	/// カードが設置可能か判定する
	/// </summary>
	/// <param name="cardPtr">判定するカード</param>
	bool CanPlace(const Card& card);
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
	std::vector<std::vector<std::shared_ptr<Card>>> handData;
	//! スコア
	int score;
#pragma endregion
#pragma region privateメソッド
	
	void Shuffle();

	/// <summary>
	/// カードを配る処理
	/// </summary>
	/// <param name="playerNum">ゲームの参加者数</param>
	void Distribute(int playerNum);

	/// <summary>
	/// 初期位置から手札を表示する
	/// </summary>
	/// <param name="playerArea">自分のエリア</param>
	void ShowHand(Area playerArea);

	/// <summary>
	/// カードを盤面に配置する
	/// </summary>
	/// <param name="_card">配置するカード</param>
	void CardOnBoard(std::shared_ptr<Card> _card);

	/// <summary>
	/// 手札をソートする
	/// </summary>
	/// <param name="playerArea"></param>
	void SortHand(Area playerArea);
#pragma endregion
};

