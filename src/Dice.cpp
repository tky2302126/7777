#include "dice.h"

dice::dice()
{
	modelHandle = MV1LoadModel(_T("C:/Users/student2/Desktop/Dice.mv1"));
}

void dice::Roll()
{
	// ÉTÉCÉRÉçèàóù
	if (rolling) {
		rotXA += 0.3f + (rand() % 100) / 500.0f;
		rotYA += 0.4f + (rand() % 100) / 500.0f;
		rotZA += 0.2f + (rand() % 100) / 500.0f;
		timerA--;

		rotXB += 0.3f + (rand() % 100) / 500.0f;
		rotYB += 0.4f + (rand() % 100) / 500.0f;
		rotZB += 0.2f + (rand() % 100) / 500.0f;
		timerB--;

		if (timerA <= 0 && timerB <= 0) {
			rolling = false;
			resultA = 1 + rand() % 6;
			resultB = 1 + rand() % 6;
			SetRotationByResult(resultA, rotXA, rotYA, rotZA);
			SetRotationByResult(resultB, rotXB, rotYB, rotZB);
		}
	}
}

void dice::SetRotationByResult(int value, float& x, float& y, float& z)
{
	switch (value) {
	case 1: x = 0.0f;              y = 0.0f;         z = 0.0f; break;
	case 4: x = DX_PI_F / 2;  y = 0.0f;         z = 0.0f; break;
	case 5: x = DX_PI_F / 2;  y = 0.0f;         z = DX_PI_F / 2; break;
	case 2: x = DX_PI_F / 2;  y = 0.0f;         z = -DX_PI_F / 2; break;
	case 3: x = -DX_PI_F / 2; y = 0.0f;         z = 0.0f; break;
	case 6: x = DX_PI_F;       y = 0.0f;        z = 0.0f; break;
	}
}
