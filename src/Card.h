#pragma once
#include "HandlerWaltanForDxLib.h"
#include "define.h"
enum Suit : int
{
	SPADE = 0,
	CLAB,
	DIA,
	HEART
};

enum Area
{
	Area_Invailed,
	Area_Board,
	Area_Player1,
	Area_Player2,
	Area_Player3,
	Area_Player4,
};

class Card
{
#pragma region フィールド
public:
	
	Suit suit;
	// カードの数字
	int number;
	// 表示する位置を決めるID
	// カードのモデルをuvの要領で決めるために必要
	int frameId;
	// カードの場所
	Area area;
	// 手札の位置
	int areaNumber;

	static int modelHandle;
	
private:
	VECTOR position;
	VECTOR rotate;
	VECTOR scale;
#pragma endregion

#pragma region メソッド
public:
	Card();
	Card(int _frameId);
	~Card();
	void ManualUpdate();
#pragma endregion

};

