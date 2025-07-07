#include "Card.h"
#define DEBUG
int Card::modelHandle = -1;
int Card::instanceCount = 0;
VECTOR Card::position_model = VGet(400, 200, -290);
VECTOR Card::rotate_model = VGet(0, (float)Deg2Rad(180), 0);
VECTOR Card::scale_model = VGet(10, 10, 10);


Card::Card() : 
	position(VECTOR()), rotate(VECTOR()), scale({1,1,1}),
	areaNumber(-1),area(Area::Area_Invailed)
{
	//
	// 自身がどのカードかを設定
	//

	suit = static_cast<Suit>(instanceCount / 13);
	number = instanceCount++ % 13 + 1; // 1~13の数字

	switch (suit)
	{
	case Suit::HEART:
		frameId = number + 1;
		break;
	case Suit::DIA:
		frameId = number + 13 + 2;
		break;
	case Suit::CLAB:
		frameId = number + 13 * 2 + 3;
		break;
	case Suit::SPADE:
		frameId = number + 13 * 3 + 4;
		break;
	default:
		frameId = -1;
		break;
	}

	// 初期座標
	position = {0,0,frameId * -0.03f };

	if (number == 7)
	{
		switch (suit)
		{
		case Suit::HEART:
			HWDotween::DoAction(&position, { -40,15,0 }, 60)->OnComplete([&] {	
				HWDotween::DoAction(&position, position + VGet(0, 0, -10), 10)->OnComplete([&] {
					HWDotween::DoAction(&rotate, { 0,0,180 }, 30)->OnComplete([&] {
						HWDotween::DoAction(&position, position + VGet(0, 0, 10), 10);
						});});});
			break;
		case Suit::DIA:
			HWDotween::DoAction(&position, { -40,0,0 }, 60)->OnComplete([&] {
				HWDotween::DoAction(&position, position + VGet(0, 0, -10), 10)->OnComplete([&] {
					HWDotween::DoAction(&rotate, { 0,0,180 }, 30)->OnComplete([&] {
						HWDotween::DoAction(&position, position + VGet(0, 0, 10), 10);
						}); }); });
					break;
		case Suit::CLAB:
			HWDotween::DoAction(&position, { -40,-15,0 }, 60)->OnComplete([&] {
				HWDotween::DoAction(&position, position + VGet(0, 0, -10), 10)->OnComplete([&] {
					HWDotween::DoAction(&rotate, { 0,0,180 }, 30)->OnComplete([&] {
						HWDotween::DoAction(&position, position + VGet(0, 0, 10), 10);
						}); }); });
					break;
		case Suit::SPADE:
			HWDotween::DoAction(&position, { -40,-30,0 }, 60)->OnComplete([&] {
				HWDotween::DoAction(&position, position + VGet(0, 0, -10), 10)->OnComplete([&] {
					HWDotween::DoAction(&rotate, { 0,0,180 }, 30)->OnComplete([&] {
						HWDotween::DoAction(&position, position + VGet(0, 0, 10), 10);
						}); }); });
					break;
		}
	}
}

Card::~Card()
{
	instanceCount--;
	if(instanceCount == 0&&modelHandle != -1)
	{
		MV1DeleteModel(modelHandle);
		modelHandle = -1;
	}
}


void Card::ManualUpdate()
{
	// transform行列
	MATRIX mat, t, r, s;
	t = r = s = MGetIdent();

	// 平行移動
	t.m[3][0] = position.x;
	t.m[3][1] = position.z;
	t.m[3][2] = position.y;

	// 回転
	MATRIX rotX = MGetRotX((float)Deg2Rad(rotate.x));
	MATRIX rotY = MGetRotY((float)Deg2Rad(rotate.y));
	MATRIX rotZ = MGetRotZ((float)Deg2Rad(rotate.z));
	r = MMult(rotZ, MMult(rotY, rotX));

	// 拡縮
	s.m[0][0] = scale.x;
	s.m[1][1] = scale.y;
	s.m[2][2] = scale.z;

	// 行列の合成(t -> r -> s)
	mat = MMult(s, MMult(r, t));

	MV1SetFrameUserLocalMatrix(Card::modelHandle, frameId, mat);
}

void Card::AreaChange(Area& _area)
{
	if (area == _area) return;


	area = _area;

}

Card* Card::Onclick()
{
	return this;
}
