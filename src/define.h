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
#define PLACE_CARD 10
#define LINE_COMPLETE 100
#define SUIT_COMPLETE 25
// #define

constexpr int CARD_WIDTH = 90;
constexpr int CARD_HEIGHT = 135;
constexpr Vector2Int DEFAULT_CARD_POSITION = { CARD_WIDTH * 3,CARD_HEIGHT};
constexpr Vector2Int FIELD_BEZEL = { 20, 20 };



//! カードのコリジョンサイズ_X(半径)
constexpr float CARD_COLLISION_WIDTH = 60.0f;
//! カードのコリジョンサイズ_Y(半径)
constexpr float CARD_COLLISION_HEIGHT = 90.0f;