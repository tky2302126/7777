#pragma once
#include "HandlerWaltanForDxLib.h"

/**
* @struct Vector2Int
* @brief 2次元座標を管理する構造体
*/
struct Vector2Int
{
	int x;
	int y;

	bool operator== (const Vector2Int& other) const { return x == other.x && y == other.y; }
	bool operator!=(const Vector2Int& other) const { return !(*this == other); }
};

#define SUIT_NUM 4
#define DECK_RANGE 13
#define PLAYER_NUM 4
#define PLACE_CARD 10
#define LINE_COMPLETE 100
#define SUIT_COMPLETE 25
// 秒数
#define PLACE_COOL_TIME 1.5f
#define EVENT_TIME 6000

#define UDP_PORT_NUM 9999
#define MAX_PLAYER 3
// #define


//! カードの幅(scale = 1 の場合)
constexpr int CARD_WIDTH = 90;
//! カードの高さ(scale = 1 の場合)
constexpr int CARD_HEIGHT = 135;

//! カードのdefault座標(ワールド座標)
constexpr Vector2Int DEFAULT_CARD_POSITION = { CARD_WIDTH * 3,CARD_HEIGHT};
//! 盤面の補助線のカードとカードのベゼル(ワールド座標)
constexpr Vector2Int FIELD_BEZEL = { 20, 20 };

//! 盤面上におかれているカードのscale
constexpr float CARD_SIZE_ON_BOARD = 0.75f;
//! カードのdefault座標(ローカル座標) ※Cardで参照する際に使用する
constexpr VECTOR DEFAULT_CARD_POSITION_LOCAL = { -102.f,-8.55f};
//! 盤面の補助線のカードとカードのベゼル(ローカル)
constexpr VECTOR FIELD_BEZEL_LOCAL = { 7.5f, 10.55f };



//! カードのコリジョンサイズ_X(半径)
constexpr float CARD_COLLISION_WIDTH = 60.0f;
//! カードのコリジョンサイズ_Y(半径)
constexpr float CARD_COLLISION_HEIGHT = 90.0f;

// 通信で使うイベント
enum Event
{
	Event_None,		   // イベント実行なし
	Event_CountDown,   // スタート時のカウントダウン
	Event_MouseEnable, // マウス入力を許可
	Event_DiceRoll,    // ダイスロール
	Event_IsAgari,	   // あがり
	Event_Bomb,		   // 爆弾
	Event_Fever,	   // フィーバータイム
	Event_LuckyNumber, // ラッキーナンバー
	Event_LimitArea,   // エリア制限
	Event_MoveArea,    // エリア移動
	Event_ShuffleHand, // 手札交換
};