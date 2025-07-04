#pragma once
#include "HandlerWaltanForDxLib.h"
#include "define.h"
enum Suit : int
{
	HEART	= 0,
	DIA		= 1,
	CLAB	= 2,
	SPADE	= 3,
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
	//! 自身がモデルの何フレーム目のカードか
	int frameId;
	// カードの場所
	Area area;
	// 手札の位置
	int areaNumber;
	//! モデルハンドル(カード全てで一つのモデルのため)
	static int modelHandle;
	//! 生成されたカードインスタンスの数(自身のナンバー決めに使っている)
	static int instanceCount;
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
	void ManualLoad();
	void ManualUpdate();
	VECTOR GetPosition() { return position; };
	VECTOR GetScale() { return scale; };
#pragma endregion

};


#pragma pack(1)

/**
 * @class	CardData
 * @brief  データ送信用
 */
struct CardData
{
	unsigned char data;
	unsigned char area;
	unsigned char areaNumber;
};

#pragma pack()