/**
* @note		Cursorの定義ファイル
*/

#pragma once
#include "HandlerWaltanForDxLib.h"


/**
 * @class	Cursor
 * @brief   カーソル管理
 */
class Cursor
{
public:

	/**
	 * @brief       初期化関数
	 */
	void ManualInitialize(const VECTOR& _pos, const VECTOR& _scale)
	{
		position = _pos;
		targetScale = scale = _scale;

		color = GetColor(100, 100, 255);
		//color = GetColor(255, 255, 255);
	}

	/**
	 * @brief       移動させる
	 */
	void SetTargetPosition(const VECTOR& _target)
	{
		targetPos = _target;
	}

	/**
	 * @brief       サイズ変更
	 */
	void SetTargetScale(const VECTOR& _target)
	{
		targetScale = _target;
	}

	/**
	 * @brief       カラー変更
	 */
	void SetColor(const unsigned int _color)
	{
		color = _color;
	}

	/**
	 * @brief       毎F呼ばれるメソッド
	 */
	void ManualUpdate()
	{
		DrawBox((int)position.x - (int)scale.x, (int)position.y - (int)scale.y,
				(int)position.x + (int)scale.x, (int)position.y + (int)scale.y,
			color, TRUE);

		//DrawTriangle((int)position.x + (int)scale.x, (int)position.y - (int)scale.y,
		//			 (int)position.x + (int)scale.x, (int)position.y + (int)scale.y,
		//			 (int)position.x + (int)scale.x + 50, (int)position.y,
		//	color, TRUE);

		//DrawTriangle((int)position.x - (int)scale.x, (int)position.y - (int)scale.y,
		//			 (int)position.x - (int)scale.x, (int)position.y + (int)scale.y,
		//			 (int)position.x - (int)scale.x - 50, (int)position.y,
		//	color, TRUE);


		// 移動処理
		VECTOR dir = (targetPos - position) * 0.3f;
		position += dir;

		// 拡縮処理
		dir = (targetScale - scale) * 0.3f;
		scale += dir;
	}


private:

	//! 座標
	VECTOR position;
	//! 目標地点
	VECTOR targetPos;
	//! サイズ
	VECTOR scale;
	//! 目標サイズ
	VECTOR targetScale;
	//! カラー
	unsigned int color;
};