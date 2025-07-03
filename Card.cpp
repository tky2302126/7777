#include "Card.h"
int Card::modelHandle = -1;

Card::Card()
{
	if(modelHandle == -1)
	{
		modelHandle = MV1LoadModel("Assets/model/Cards/Cards.mv1");
	}
	area = Invailed;
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
	if (modelHandle == -1)
	{
		modelHandle = MV1LoadModel("Assets/model/Cards/Cards.mv1");
	}
	area = Invailed;
	areaNumber = -1;
	frameId = _frameId;
	number = frameId %13;
	suit = static_cast<Suit>(frameId/13);
	position = VECTOR();
	rotate = VECTOR();
	scale = VECTOR();
}

Card::~Card()
{
	if(modelHandle != -1)
	{
		MV1DeleteModel(modelHandle);
		modelHandle = -1;
	}
}

void Card::ManualUpdate()
{
	
}
