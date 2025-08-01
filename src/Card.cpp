﻿#include "Card.h"
#include "Board.h"
#define DEBUG
int Card::modelHandle = -1;
int Card::instanceCount = 0;
int Card::leftEdgeNum = 1;
VECTOR Card::position_model = VGet(400, 200, -300);
VECTOR Card::rotate_model = VGet(0, (float)Deg2Rad(180), 0);
VECTOR Card::scale_model = VGet(10, 10, 10);


Card::Card() : 
	position(VECTOR()), rotate(VECTOR()), scale({1,1,1}),
	areaNumber(-1), area(Area::Area_Invalid), collisionCenter(VECTOR())
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
	position = {-55,50,frameId * 0.0f };
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
	// コリジョン
	collisionCenter = ConvWorldPosToScreenPos(MV1GetFramePosition(Card::modelHandle, frameId));
	//DrawBox(
	//	(int)(collisionCenter.x - CARD_COLLISION_WIDTH),
	//	(int)(collisionCenter.y - CARD_COLLISION_HEIGHT),
	//	(int)(collisionCenter.x + CARD_COLLISION_WIDTH),
	//	(int)(collisionCenter.y + CARD_COLLISION_HEIGHT),
	//	GetColor(255, 0, 0), FALSE);

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

void Card::AreaChange(Area _newArea)
{
	if (area == _newArea) return;

	area = _newArea;

	// leftEdgeNumを加えた位置に補正
	auto bezelPosX = (DECK_RANGE - number + leftEdgeNum) % DECK_RANGE;
	if (bezelPosX <= 0)bezelPosX += DECK_RANGE; // マイナス補正
	bezelPosX--; // 配列の数値に補正
	if(_newArea == Area_Board)
	{
		VECTOR boardPos = {
			DEFAULT_CARD_POSITION_LOCAL.x + bezelPosX * FIELD_BEZEL_LOCAL.x,
			DEFAULT_CARD_POSITION_LOCAL.y + suit				* FIELD_BEZEL_LOCAL.y,
		};

		HWDotween::DoAction(&position, { (float)boardPos.x, (float)boardPos.y, 0 }, 10);
		HWDotween::DoAction(&scale, { CARD_SIZE_ON_BOARD, CARD_SIZE_ON_BOARD, CARD_SIZE_ON_BOARD }, 5);

		if (rotate.z != 180.0f)
			HWDotween::DoAction(&rotate, { 0, 0, 180 }, 30);
	}
}

void Card::Slide()
{
	if (area != Area_Board) return;
	// leftEdgeNumを加えた位置に補正
	auto bezelPosX = (DECK_RANGE - number + leftEdgeNum) % DECK_RANGE;
	if (bezelPosX <= 0)bezelPosX += DECK_RANGE; // マイナス補正
	bezelPosX--; // 配列の数値に補正
	VECTOR newPos = {
		DEFAULT_CARD_POSITION_LOCAL.x + bezelPosX * FIELD_BEZEL_LOCAL.x,
		DEFAULT_CARD_POSITION_LOCAL.y + suit * FIELD_BEZEL_LOCAL.y,
	};

	HWDotween::DoAction(&position, { newPos.x, newPos.y, 0 }, 10);
}
