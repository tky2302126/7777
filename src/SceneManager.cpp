#include "SceneManager.h"

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneManagerの実装ファイル
*/


InputSystem* SceneBase::input = nullptr;

SceneManager::SceneManager()
{
	// エラー値を入れておく
	crrSceneTag = SceneTag::NotFound;
	// ロードステータスの初期化
	atomicLoadState = SceneLoadState::Wait;

	crrScene = nullptr;
}


void SceneManager::Update()
{
	crrScene->Update();

	// 非同期の読み込みが完了した
	if (atomicLoadState.load() == SceneLoadState::Completed)
	{
		// シーンを上書き
		std::swap(crrScene, loadScene);
		// タグも変更
		crrSceneTag = crrScene->sceneTag;
		crrScene->nextSceneTagAsync = SceneTag::NotFound;
		//　読み込みデータを削除
		delete loadScene;
		// スレッドを開放
		sceneLoadThread.detach();
		// 読み込みステータスを変更
		atomicLoadState.store(SceneLoadState::Wait);

		// 読み込み完了時のメソッドの実行
		crrScene->LoadComplete();
	}

	// シーン内で遷移指示が来た場合
	if (!(crrScene->nextSceneTag == SceneTag::NotFound ||
		crrScene->nextSceneTag == crrSceneTag))
		SceneChangeSync(crrScene->nextSceneTag);

	// シーン内で非同期で行う遷移指示が来た場合
	if (!(crrScene->nextSceneTagAsync == SceneTag::NotFound ||
		crrScene->nextSceneTagAsync == crrSceneTag))
		SceneChangeAsync(crrScene->nextSceneTagAsync);

	// デバッグ用のシーン遷移
	if(HandlerWaltan::debugMode == true)
	{
		// SceneTitle
		if(CheckHitKey(KEY_INPUT_T) &&CheckHitKey(KEY_INPUT_LCONTROL))
		{
			crrScene->nextSceneTag = SceneTag::Title;
		}

		// SceneGame
		if(CheckHitKey(KEY_INPUT_G) && CheckHitKey(KEY_INPUT_LCONTROL))
		{
			SceneChangeAsync(SceneTag::Game);
		}

		// SceneResult
		if(CheckHitKey(KEY_INPUT_R) && CheckHitKey(KEY_INPUT_LCONTROL))
		{
			crrScene->nextSceneTag = SceneTag::Result;
		}
	}
}

void SceneManager::LateUpdate()
{
	crrScene->LateUpdate();
}


void SceneManager::SceneChangeSync(const SceneTag& _nextSceneTag)
{
	// 遷移指示の来たタグが実行中のシーンと同じか、NotFoundだった場合はそのまま終了
	if (_nextSceneTag == crrSceneTag || _nextSceneTag == SceneTag::NotFound)
		return;

	// ! 遷移先のシーンタグを記憶しておく(参照型で持っているため)
	const SceneTag nextSceneTag = _nextSceneTag;

	// 実行中のシーンを削除
	if(crrScene != nullptr)
		delete(crrScene);

	// タグによって遷移先のシーンを変更する
	switch (nextSceneTag)
	{

	case SceneTag::Title:
		crrScene = new SceneTitle();
		break;

	case SceneTag::Game:
		crrScene = new SceneGame();
		break;

	case SceneTag::Result:
		crrScene = new SceneResult();
		break;

	case SceneTag::MainMenu:
		//crrScene = new SceneMainMenu();
		break;

	case SceneTag::Option:
		//crrScene = new SceneOption();
		break;

		/*
		// Sceneを増やす際は、こことSceneBase.hにあるSceneTagに追加で記述する

	case SceneTag:: :
		crrScene = new 追加シーン();
		break;
		*/
	}

	// シーンタグを更新
	crrSceneTag = nextSceneTag;

	// 読み込み完了時のメソッドの実行
	crrScene->LoadComplete();
}


void SceneManager::SceneChangeAsync(const SceneTag& _nextSceneTag)
{
	// シーン読み込み中の場合、指示を無効
	if (sceneLoadThread.joinable() || atomicLoadState.load() != SceneLoadState::Wait) return;
	// 遷移指示の来たタグが実行中のシーンと同じか、NotFoundだった場合はそのまま終了
	if (_nextSceneTag == crrSceneTag || _nextSceneTag == SceneTag::NotFound) return;

	// シーン読み込み開始
	sceneLoadThread = std::thread(&SceneManager::SceneLoad, this, _nextSceneTag);
}


void SceneManager::SceneLoad(const SceneTag& _nextSceneTag)
{
	// シーン読み込み完了のフラグを折っておく
	atomicLoadState.store(SceneLoadState::Loading);

	//! 遷移先のシーンタグを記憶しておく(参照型で持っているため)
	const SceneTag nextSceneTag = _nextSceneTag;

	// タグによって遷移先のシーンを変更する
	switch (nextSceneTag)
	{
	case SceneTag::Title:
		loadScene = new SceneTitle();
		break;

	case SceneTag::Game:
		loadScene = new SceneGame();
		break;

	case SceneTag::Result:
		//loadScene = new SceneResult();
		break;

	case SceneTag::MainMenu:
		//loadScene = new SceneMainMenu();
		break;

	case SceneTag::Option:
		//loadScene = new SceneOption();
		break;
	}

	loadScene->AsyncAwake();

	// 読み込み完了
	atomicLoadState.store(SceneLoadState::Completed);
}


