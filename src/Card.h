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
#pragma region Publicメンバ変数
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
	//! 座標
	VECTOR position = VECTOR();
	//! 回転
	VECTOR rotate = VECTOR();
	//! 拡縮
	VECTOR scale = VECTOR();
	//! コリジョンの中心座標
	VECTOR collisionCenter;
	//! モデルの座標(変更するとカード全体が移動する)
	static VECTOR position_model;
	//! モデルの回転(変更するとカード全体が回転する)
	static VECTOR rotate_model;
	//! モデルの拡縮(変更するとカード全体が拡縮する)
	static VECTOR scale_model;
#pragma endregion

#pragma region Publicメソッド
public:
	Card();
	~Card();

	/**
	 * @brief       明示的に呼ぶ必要のある更新処理
	 */
	void ManualUpdate();

	/**
	 * @brief       カードの所属領域の変更
	 * @param[in]	変更後の領域
	 */
	void AreaChange(Area& _area);
#pragma endregion

#pragma region Privateメンバ変数
private:
#pragma endregion

#pragma region Privateメソッド
	Card* Onclick();
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