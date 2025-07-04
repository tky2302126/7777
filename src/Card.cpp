#include "Card.h"
#define DEBUG
int Card::modelHandle = -1;
int Card::instanceCount = 0;

Card::Card() : 
	position(VECTOR()), rotate(VECTOR()), scale(VECTOR()),
	areaNumber(0),area(Area::Area_Invailed)
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
	}
}

Card::Card(int _frameId)
{
	instanceCount++;
	area = Area_Invailed;
	areaNumber = -1;
	frameId = _frameId;
	number = frameId %13 + 1;
	suit = static_cast<Suit>(frameId/13);
	position = VGet(960, 360, 0);
	rotate = VGet(0, 0, 0);
	scale = VGet(10, 10, 10);
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

// DXライブラリとマルチスレッドの相性が悪いのでタイミングをコントロールする
void Card::ManualLoad()
{
#ifdef DEBUG
	modelHandle = MV1LoadModel("Assets/model/Cards/Cards.mv1");
#else
	modelHandle = MV1LoadModel("Assets/model/Cards/Cards.mv1");
#endif // DEBUG
}

void Card::ManualUpdate()
{
	
}
