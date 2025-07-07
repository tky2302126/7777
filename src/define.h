#pragma once
// ! Includeを入れない

#define SUIT_NUM 4
#define DECK_RANGE 13

constexpr int CARD_WIDTH = 110;
constexpr int CARD_HEIGHT = 170;

//! カードのコリジョンサイズ_X(半径)
constexpr float CARD_COLLISION_WIDTH = 60.0f;
//! カードのコリジョンサイズ_Y(半径)
constexpr float CARD_COLLISION_HEIGHT = 90.0f;