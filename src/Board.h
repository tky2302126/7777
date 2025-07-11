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

#pragma region イベント関連
	//イベント抽選の関数
	// サーバーで実行→クライアントに送信する予定
	void DrawingEvent();

#pragma endregion


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

	// イベント用の実行時間カウントタイマー
	int eventCountTimer;
	// 実行しているイベント
	Event currentEvent;
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

	/// <summary>
	/// スコア計算
	/// </summary>
	/// <param name="card">置かれたカード</param>
	void CalculateScore(std::shared_ptr<Card>& card);

	/// <summary>
	/// 爆弾イベント
	/// </summary>
	void Bomb();

	/// <summary>
	/// フィーバータイムイベント
	/// </summary>
	void FeverTime();

	/// <summary>
	/// ラッキーナンバーイベント
	/// </summary>
	/// <param name="num">対象の数字</param>
	void LuckyNumber();

	/// <summary>
	/// エリア制限
	/// </summary>
	void LimitArea();

	/// <summary>
	/// エリア移動
	/// </summary>
	void SlideArea();

	/// <summary>
	/// 手札入れ替え
	/// </summary>
	void ShuffleHand();
#pragma endregion
};

