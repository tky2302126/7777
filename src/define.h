#pragma once
// ! Includeを入れない

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