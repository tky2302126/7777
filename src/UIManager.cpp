#include "UIManager.h"

/**
* @author   Suzuki N
* @date     24/01/29
* @note		UIManagerの実装ファイル
*/


//
// 静的メンバ変数の初期化
//

int UIManager::fadeGraphHandle = -1;
bool UIManager::isFade = false;
int UIManager::alpha = 0;
int UIManager::add = 0;
int UIManager::loadingGraphHandle = -1;
int UIManager::menuFont = -1;


void UIManager::FadeIn(int _speed, int _frame, bool _autoFadeOut)
{
	if (isFade) return;

	isFade = true;
	add = _speed;
	alpha = 0;

	if(_autoFadeOut)
	{
		HWDotween::DoDelay(255 / _speed + _frame)->OnComplete([&]
			{
				alpha = 255;
				FadeOut(add);
			});
	}
}

void UIManager::FadeOut(int _speed)
{
	if (!isFade) return;

	add = -_speed;

	HWDotween::DoDelay(255 / _speed)->OnComplete([&]
		{	
			isFade = false;
			alpha = 0;
		});
}

void UIManager::ManualInitialize()
{
	// フェードイン、フェードアウト用の画像
	{
		fadeGraphHandle = LoadGraph("Assets/UI/Fade.png");
		isFade = false;
	}
	// ロード中のアニメーションに必要なもの
	{
		loadingGraphHandle = LoadGraph("Assets/UI/Loading.png");
		menuFont = CreateFontToHandle(NULL, 50, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	}
}

UIManager::‾UIManager()
{
}

void UIManager::Awake()
{
	gameObject->priority = -5;
}

void UIManager::ManualLateUpdate()
{
	//
	// フェードイン、フェードアウト中の処理
	//
	if (isFade)
	{
		// 画像のアルファブレンドで描画
		// ( 描画した後ブレンドモードを元に戻す )
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawGraph(0, 0, fadeGraphHandle, FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		alpha += add;
		if(alpha > 255) alpha = 255;
		else if (alpha < 0) alpha = 0;
	}
}

void UIManager::LoadingAnimation()
{
	//! 回転数
	static float rot = 0.0f;

	// 回転数の加算
	rot += 0.08f;

	DrawRotaGraph3(200, 850 + 50 / 2,
		1500/2, 1500 /2,
		0.05, 0.05,
		rot,
		loadingGraphHandle,
		TRUE);

	DrawFormatStringToHandle(250, 850, GetColor(0, 255, 0),
		menuFont, "Loading...");
}
