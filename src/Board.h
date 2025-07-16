#pragma once
#include "Card.h"
#include "Dice.h"
#include "define.h"
#include "UDPConnection.h"

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
	//! 配置のクールタイム
	float coolTime = 1.5f;
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
	// 乱数生成器
	static std::mt19937 engine;

	float GetCoolTime() { return coolTime; }
#pragma region イベント関連
	//イベント抽選の関数
	// サーバーで実行→クライアントに送信する予定
	void DrawingEvent();

	// イベント関連の変数の初期化
	//! サーバー・クライアントどちらも通る場所で呼ぶ
	void InitEventMember();

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
	void LuckyNumber(int num = -1);

	/// <summary>
	/// エリア制限
	/// </summary>
	void LimitArea(int left = -1, int right = -1);

	/// <summary>
	/// エリア移動
	/// </summary>
	void MoveArea(bool left = true, int num = -1);

	/// <summary>
	/// 手札入れ替え
	/// </summary>
	void ShuffleHand();
#pragma endregion


#pragma endregion

#pragma region privateメンバ変数
	int rank;
	int currentrank;
	int winHandle;
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
	//! ラッキーナンバー
	int luckyNum;
	// イベント用の実行時間カウントタイマー
	int eventCountTimer;
	// 実行しているイベント
	Event currentEvent;
	// イベント抽選用のさいころ
	Dice* dice;
	
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
	/// <param name="_index">変更するHandDataのインデックス</param>
	void CardOnBoard(std::shared_ptr<Card> _card, int _index);

	/// <summary>
	/// 手札をソートする
	/// </summary>
	/// <param name="playerArea"></param>
	void SortHand(Area playerArea);

	/// <summary>
	/// スコア計算
	/// </summary>
	/// <param name="card">置かれたカード</param>
	int CalculateScore(std::shared_ptr<Card>& card);

	/// <summary>
	/// 縦にそろったか
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	bool IsCompleteRowOfSuit(int num);

	/// <summary>
	/// 横にそろったか
	/// </summary>
	/// <param name="suit"></param>
	/// <returns></returns>
	bool IsCompleteColumnAt(const Suit& suit);

	bool IsLuckyNumber(const int& num) { return luckyNum == num; };

	/// <summary>
	/// 完全順列かどうかを判定
	/// </summary>
	/// <param name="original">元のカード情報</param>
	/// <param name="shuffled">シャッフル後の情報</param>
	/// <returns></returns>
	bool IsDerangement(const std::vector<std::vector<std::shared_ptr<Card>>>& original,
		const std::vector<std::vector<std::shared_ptr<Card>>>& shuffled);

	static void InitRandomGenerator();
#pragma endregion
};

