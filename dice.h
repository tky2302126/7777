#pragma once
#include "HandlerWaltan.h"
class dice
{
	int modelHandle;
	dice();
	void Roll();
	void SetRotationByResult(int value, float& x, float& y, float& z)
};

