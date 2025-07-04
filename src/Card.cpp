#include "Card.h"
#define DEBUG
int Card::modelHandle = -1;
int Card::instanceCount = 0;

Card::Card()
{
	instanceCount++;
	area = Area_Invailed;
	areaNumber = -1;
	frameId = -1;
	number = -1;
	suit = SPADE;
	position = VECTOR();
	rotate = VECTOR();
	scale = VECTOR();
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
