/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneManagerの定義ファイル
*/

#pragma once
#include "SceneTitle.h"
#include "SceneGame.h"


/**
 * @class	SceneManager
 * @brief   シーンの実行、遷移を行うクラス
 * @detail	シングルトンで設計されているため、インスタンスを作成できません
 */
class SceneManager
{
public:

	//! シーンロードが完了しているか
	std::atomic<SceneLoadState> atomicLoadState;


	/**
	 * @brief       シングルトンインスタンスを取得する
	 * @detail		インスタンスが未生成の場合、新たに作成する
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	static SceneManager& Instance()
	{
		static SceneManager* instance = new SceneManager();
		return *instance;
	}

	/**
	 * @brief       実行中のシーンタグを取得する
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	const SceneTag& GetCrrSceneTag()const { return crrSceneTag; }

	/**
	 * @brief       実行中のシーンを取得する
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	const SceneBase& GetCrrScene()const { return *crrScene; }

	/**
	 * @brief       明示的に呼び出す必要のあるUpdate処理
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void Update();

	/**
	 * @brief       明示的に呼び出す必要のあるUpdate処理
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void LateUpdate();

	/**
	 * @brief       同期処理でシーンを変更する
	 * @param[in]	const SceneTag& 遷移先のシーンタグ
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void SceneChangeSync(const SceneTag& _nextSceneTag);

	/**
	 * @brief       非同期処理でシーンを変更する
	 * @param[in]	const SceneTag& 遷移先のシーンタグ
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void SceneChangeAsync(const SceneTag& _nextSceneTag);


private:

	//! 実行中のシーンタグ
	SceneTag crrSceneTag;
	//! 実行中のシーンのインスタンス
	SceneBase* crrScene;
	//! 非同期でシーンの読み込みを行うスレッド
	std::thread sceneLoadThread;
	//! 非同期で読み込んだシーンのインスタンス
	SceneBase* loadScene;
	//! ロード中に再生する動画のハンドル
	int loadMovieHandle;


	/**
	 * @brief       シーン読み込み
	 * @param[in]	const SceneTag& 遷移先のシーンタグ
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void SceneLoad(const SceneTag& _nextSceneTag);

	// コンストラクタは明示的に削除
	SceneManager();
};

