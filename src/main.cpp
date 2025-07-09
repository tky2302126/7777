#pragma comment(lib,"Lib/MTd_Debug/MyLib_d.lib")
#pragma comment(lib,"Lib/MTd_Release/MyLib.lib")

// 当ライブラリで必須になるインクルードファイル
// "DxLib.h" もincludeされる
#include "HandlerWaltanForDxLib.h"
#include"SceneManager.h"
#include "GameManager.h"
#include <fstream>


// 静的メンバ変数の初期化
Role GameManager::role = Role::server;
int GameManager::networkHandle[3] = { -1, -1, -1 };
int GameManager::connectNum = -1;
int GameManager::playerId = -1;


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetDoubleStartValidFlag(TRUE);

	// DXライブラリの初期化処理も兼ねている
	if (HandlerWaltan::Instance().Init() == -1)
	{
		return 0;
	}


#ifdef _DEBUG

	// 幅: 1920, 高さ: 1080, ビット深度: 32
	SetGraphMode(1920 / 2, 1080 - 80, 32);
	ChangeWindowMode(TRUE);
	// デバッグモードで起動
	HandlerWaltan::debugMode = true;
	SetMouseDispFlag(TRUE);

#else

	// 幅: 1920, 高さ: 1080, ビット深度: 32
	SetGraphMode(1920, 1080, 32);
	// ウインドウモードで起動
	ChangeWindowMode(FALSE);
	// 非デバッグモードで起動
	HandlerWaltan::debugMode = false;

#endif // DEBUG


	SetUseZBuffer3D(TRUE);     // デプスバッファ（Zバッファ）を有効にする
	SetWriteZBuffer3D(TRUE);   // Zバッファへの書き込みを有効にする

	//! ハンドラーやライフサイクルに基づいたタイミングでメソッドを自動的に呼び出すオブジェクト
	//! シングルトンで設計されているため、以下の方法以外でインスタンスを取得することはできない
	HandlerWaltan& HW = HandlerWaltan::Instance();

	UIManager::ManualInitialize();
	auto& sceneManager = SceneManager::Instance();
	sceneManager.SceneChangeSync(SceneTag::Title);

	HWDotween::DoDelay(30)->OnComplete([&] {
		//sceneManager.SceneChangeAsync(SceneTag::Game);
		//UIManager::FadeIn(20, 0, false);
		});

	//! オブジェクトの生成(unityでいうところのGameObjectの生成)
	HWGameObject* obj = new HWGameObject();


	VECTOR pos = VGet(200, 500, 0);
	VECTOR rot = VGet(0, 0, 0);
	VECTOR scale = VGet(1, 1, 1);

	HWDotween::TweenCallback* callback;

	callback = HWDotween::DoAction(&pos, pos + VGet(800, 0, 0), 240);
	
	HWDotween::DoDelay(60)->OnComplete([&] {
		HWDotween::DoAction(&scale, VGet(5, 5, 5), 60)->OnComplete([&] {
			HWDotween::DoAction(&scale, VGet(1, 1, 1), 60);
			//callback->tweenEvent->isCancel = true;
			});
		});

	// メインループ
	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();
		SetDrawScreen(DX_SCREEN_BACK);


		if (CheckHitKey(KEY_INPUT_ESCAPE))
			break;


		// 全てのUpdateメソッドを全て呼び出す
		HW.Update();

		sceneManager.Update();


		//DrawCapsule3D(
		//	pos, pos + VGet(0,400,0), 50.0f * scale.x,
		//	12, 
		//	GetColor(255, 0, 0),GetColor(255, 0, 0), 
		//	FALSE);


		sceneManager.LateUpdate();
		UIManager::ManualLateUpdate();
		// 非同期でシーンを読み込んでいる最中
		if (sceneManager.atomicLoadState.load() == SceneLoadState::Loading)
			UIManager::LoadingAnimation();

		ScreenFlip();
	}

	// ソフトの終了 
	HandlerWaltan::End();

	return 0;
}