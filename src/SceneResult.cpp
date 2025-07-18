// @author : h_suzuki
// @date : 2025-07-03
// @history : 2025-07-03 update : SceneResultの仮実装

#include "SceneResult.h"
//#define DEBUG

/// <summary>
/// to do
/// 順位の表示
/// 再戦確認
/// </summary>

SceneResult::SceneResult()
{

#ifdef DEBUG
	GameManager::score[0] = 100;
	GameManager::score[1] = 200;
	GameManager::score[2] = 300;
	GameManager::score[3] = 400;
#endif // DEBUG
	GHPos[0] = {600, 250};
	StringPos[0] = {STRING_DEFAULT_POS, 245, 0};

}

SceneResult::~SceneResult()
{
}

void SceneResult::LoadComplete()
{
	medalGH[0] = LoadGraph("Assets/Sprite/goldmedal.png");
	medalGH[1] = LoadGraph("Assets/Sprite/silvermedal.png");
	medalGH[2] = LoadGraph("Assets/Sprite/blonzemedal.png");
	resultGH = LoadGraph("Assets/Sprite/result.png");
	fontHandleWhite = CreateFontToHandle(NULL, FONT_SIZE, 3);
	fontHandleBlack = CreateFontToHandle(NULL, FONT_SIZE + 2, 3);

	ShowResult();
}

void SceneResult::AsyncAwake()
{
}

void SceneResult::KeyInputCallback(InputAction::CallBackContext _c)
{

}

void SceneResult::Update()
{
	

#ifdef DEBUG
	if(CheckHitKey(KEY_INPUT_W))
	{
		StringPos[0].y -= 1;
	}
	if(CheckHitKey(KEY_INPUT_S))
	{
		StringPos[0].y += 1;
	}
	if(CheckHitKey(KEY_INPUT_A))
	{
		StringPos[0].x -= 1;
	}
	if(CheckHitKey(KEY_INPUT_D))
	{
		StringPos[0].x += 1;
	}

	
#endif // DEBUG
	
}

void SceneResult::LateUpdate()
{
	DrawExtendGraph(0, 0, 1920, 1080, resultGH, FALSE);

	DrawExtendGraph(GHPos[0].x, GHPos[0].y,
		GHPos[0].x + MEDAL_WIDTH, GHPos[0].y + MEDAL_HEIGHT,
		medalGH[0], TRUE);
	DrawExtendGraph(GHPos[0].x, GHPos[1].y,
		GHPos[0].x + MEDAL_WIDTH, GHPos[1].y + MEDAL_HEIGHT,
		medalGH[1], TRUE);
	DrawExtendGraph(GHPos[0].x, GHPos[2].y,
		GHPos[0].x + MEDAL_WIDTH, GHPos[2].y + MEDAL_HEIGHT,
		medalGH[2], TRUE);

	DrawFormatStringToHandle(StringPos[0].x, StringPos[0].y, GetColor(0, 0, 0),
		fontHandleBlack, resultText[0].c_str());
	DrawFormatStringToHandle(StringPos[1].x, StringPos[1].y, GetColor(0, 0, 0),
		fontHandleBlack, resultText[1].c_str());
	DrawFormatStringToHandle(StringPos[2].x, StringPos[2].y, GetColor(0, 0, 0),
		fontHandleBlack, resultText[2].c_str());
	DrawFormatStringToHandle(StringPos[3].x, StringPos[3].y, GetColor(0, 0, 0),
		fontHandleBlack, resultText[3].c_str());

	DrawFormatStringToHandle(StringPos[0].x, StringPos[0].y, GetColor(255, 255, 255),
		fontHandleWhite, resultText[0].c_str());
	DrawFormatStringToHandle(StringPos[1].x, StringPos[1].y, GetColor(255, 255, 255),
		fontHandleWhite, resultText[1].c_str());
	DrawFormatStringToHandle(StringPos[2].x, StringPos[2].y, GetColor(255, 255, 255),
		fontHandleWhite, resultText[2].c_str());
	DrawFormatStringToHandle(StringPos[3].x, StringPos[3].y, GetColor(255, 255, 255),
		fontHandleWhite, resultText[3].c_str());


	//DrawFormatString(0, 50, GetColor(0, 0, 0),
	//	"StringPos x : %f, y : %f", StringPos[0].x, StringPos[0].y);
}

void SceneResult::ShowResult()
{
	//! 後でconnectNumに対応
	for(int i = 1; i< 3; ++i)
	{
		GHPos[i].x = GHPos[0].x;
		GHPos[i].y = GHPos[0].y + (MEDAL_HEIGHT + PADDING_GH) * i;
	}

	for(int i = 1; i < 4; ++i)
	{
		StringPos[i].x = StringPos[0].x;
		StringPos[i].y = StringPos[0].y + (FONT_SIZE + PADDING_STRING) * i;
		StringPos[i].z = 0;

	}

	std::vector<int> indices(4);
	for(int i = 0; i< 4; ++i)
	{
		indices[i] = i;
	}

	// ソート
	std::sort(indices.begin(), indices.end(), [&](int a, int b)
	{
			return GameManager::score[a] > GameManager::score[b];
	});

	// テキストの登録
	for(int i = 0; i < 4; ++i)
	{
		std::stringstream ss;
		if(GameManager::playerId == i)
		{
			ss << "You" << ": "
				<< GameManager::score[indices[i]];
		}
		else
		{
			ss << "Player" << (indices[i] + 1) << ": "
			   << GameManager::score[indices[i]];
		}
		resultText[i] = ss.str();
	}

	// アニメーション
	for(int i = 0; i < 4; ++i)
	{
		targetPos[i] = VGet(
			STRING_TARGET_POS,
			StringPos[i].y,
			0
		);
		auto index = i;
		HWDotween::DoDelay(90 + 30 * index)->OnComplete([&, index] {
			HWDotween::DoAction(&StringPos[index], targetPos[index], 30);
			});
	}

}
