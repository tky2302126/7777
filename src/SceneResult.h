// @author : h_suzuki
// @date : 2025-07-03
// @history : 2025-07-03 update : SceneResultの仮実装

#pragma once
#include "SceneBase.h"
#include "MovieManager.h"
#include "UIManager.h"
#include <sstream>

#define MEDAL_WIDTH 80
#define MEDAL_HEIGHT 120
#define PADDING_GH 60
#define FONT_SIZE 100
#define PADDING_STRING 80
#define STRING_DEFAULT_POS 1920
#define STRING_TARGET_POS 700

class SceneResult : public SceneBase
{
public:
	SceneResult();
	~SceneResult();

	void LoadComplete() override;

	void AsyncAwake() override;

	void KeyInputCallback(InputAction::CallBackContext _c) override;

	void Update() override;

	void LateUpdate() override;

	void ShowResult();

private:
	Vector2Int GHPos[3];

	VECTOR StringPos[4];
	VECTOR targetPos[4];

	int medalGH[3];

	int fontHandleWhite;
	int fontHandleBlack;

	int resultGH;

	std::string resultText[4];
};

