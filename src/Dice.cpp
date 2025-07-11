#include "dice.h"

Dice::Dice()
{
	modelHandle = -1;
	isRolling = false;
	scale = { 0.7, 0.7, 0.7 };
	position = { 720, 850, -350 };
	rotate = { 0, 0, 0 };
	num = 0;
}

void Dice::ManualLoad()
{
	modelHandle = MV1LoadModel("Assets/model/Dice/Dice.mv1");
}

void Dice::Update()
{
	if (!isRolling) return;
	auto ret = MV1SetPosition(modelHandle, position);
	ret = MV1SetRotationXYZ(modelHandle, rotate);
	ret = MV1SetScale(modelHandle, scale);
	ret =  MV1DrawModel(modelHandle);
	
}

void Dice::Roll(const int& result)
{
	num = result;

	isRolling = true;

	int duration = 90;
	rotate = { 0, 0, 0 };


	// サイコロ処理
	VECTOR target = VGet(
		rotate.x + (0.3 + Random::GetRandomInt(0, 100) /500.f) * duration,
		rotate.y + (0.4 + Random::GetRandomInt(0, 100) /500.f) * duration,
		rotate.z + (0.2 + Random::GetRandomInt(0, 100) /500.f) * duration
	);

	HWDotween::DoAction(&rotate, target, duration)->OnComplete([&] {
		SetRotationByResult(num, rotate.x, rotate.y, rotate.z);
		HWDotween::DoDelay(600)->OnComplete([&] {
			isRolling = false;
			rotate = VGet(0, 0, 0);
			});
		});		
	
}

void Dice::SetRotationByResult(int value, float& x, float& y, float& z)
{
	switch (value) {
	case 1: x = -DX_PI_F / 2;     y = 0.0f;          z = 0.0f;   break;
	case 2: x = 0;		          y = -DX_PI_F / 2;  z = 0.0;    break;
	case 3: x = DX_PI_F ;	      y = 0.0f;          z = 0.0f;   break;
	case 4: x = 0;				  y = 0.0f;          z = 0.0f;   break;
	case 5: x = -DX_PI_F ;		  y = DX_PI_F / 2;   z = 0.0;    break;
	case 6: x = DX_PI_F / 2;      y = 0.0f;          z = 0.0f;   break;
	}
}
