/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneBaseの定義ファイル
*/

#pragma once
#include "HandlerWaltanForDxLib.h"

/**
 * @enum	SceneTag
 * @brief   シーンのタグ
 */
enum class SceneTag
{
	//! タイトルシーン(0)
	Title,
	//! ゲームシーン(1)
	Game,
	//! リザルトシーン(2)
	Result,
	//! メインメニュー
	MainMenu,
	//! オプション
	Option,

	/*
		追加する場合は、ここにタグを追加し、SceneManagerのSceneChangeメソッドに追記する
	*/

	//! 未使用 (常に末尾)
	NotFound = -1,
};


/**
 * @enum	SceneLoadState
 * @brief   シーンロードのステータス
 */
enum class SceneLoadState
{
	//! 待機中(0)
	Wait,
	//! ロード中(1)
	Loading,
	//! ロード完了(2)
	Completed,
};


/**
 * @class	SceneBase
 * @brief   各シーンのもとになる基底クラス
 * @detail	仮想クラスのため、インスタンスを作成できない
 */
class SceneBase
{
	friend class SceneManager;


public:

	/**
	 * @brief       最初のUodateの直前に働くメソッド
	 */
	virtual void LoadComplete() {};

	/**
	 * @brief       非同期ロードの中で呼ばれる処理
	 */
	virtual void AsyncAwake() {};

	/**
	 * @brief       デストラクタ
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	virtual ‾SceneBase() {};

	/**
	 * @brief       毎F呼ばれるメソッド
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	virtual void Update() {};

	/**
	 * @brief       優先度の低い、毎F呼ばれるメソッド
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	virtual void LateUpdate() {};


protected:

	//! シーンのタグ
	SceneTag sceneTag;
	//! 遷移先のシーンタグ
	SceneTag nextSceneTag;
	//! 非同期で読み込む遷移先のシーンタグ
	SceneTag nextSceneTagAsync;
	//! シーン遷移のコールバック関数のID
	int callBackId;
	//! 全シーン共通の操作系
	static InputSystem* input;
	//! ロード中
	bool isLoad = true;


	/**
	 * @brief       コンストラクタ
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	SceneBase() : nextSceneTag(SceneTag::NotFound), nextSceneTagAsync(SceneTag::NotFound)
	{
		//
		// 操作系の初期設定
		//

		if (input != nullptr)
			return;

		input = new InputSystem();
		input->AddKeyCode("cursor", { PAD_INPUT_DOWN,PAD_INPUT_UP,PAD_INPUT_2 }, InputType::Key_Pad1);
		input->AddKeyCode("cursor", { KEY_INPUT_W,KEY_INPUT_S,KEY_INPUT_Z }, InputType::Key);
	}

	/**
	 * @brief       キー入力時のコールバック
	 * @param[in]	コールバックコンテキスト
	 */
	virtual void KeyInputCallback(InputAction::CallBackContext _c) = 0;

	/**
	 * @brief       シーン内からシーンを変更する
	 * @param[in]	const SceneTag 変更先のシーンタグ
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void SceneChangeSync(const SceneTag _nextSceneTag)
	{
		nextSceneTag = _nextSceneTag;
	}
	/**
	 * @brief       非同期でシーン内からシーンを変更する
	 * @param[in]	const SceneTag 変更先のシーンタグ
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void SceneChangeAsync(const SceneTag _nextSceneTag)
	{
		nextSceneTagAsync = _nextSceneTag;
	}
};
