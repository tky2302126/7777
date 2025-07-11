#pragma once
#include "HandlerWaltan.h"
class Dice
{
public:
	Dice();
	void ManualLoad();
	void Update();
	void Roll(const int&);
	void SetRotationByResult(int value, float& x, float& y, float& z);
private:
	// モデルハンドル
	int modelHandle;
	//! 座標
	VECTOR position = VECTOR();
	//! 回転
	VECTOR rotate = VECTOR();
	//! 拡縮
	VECTOR scale = VECTOR();

	bool isRolling;

	int num;
};

