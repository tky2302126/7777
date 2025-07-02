/**
 * @file	MovieManager.h
 * @brief	動画再生関係
 * @author	NS
 * @date	2024/1/29
 */

#pragma once
#include "VideoPlayer.h"
#include "SceneBase.h"


 /**
  * @class	MovieManager
  * @brief	動画再生
  */

class MovieManager : public HWComponent
{
public:

	/**
	 * @brief		初期化処理
	 */
	void Awake()override;

	/**
	 * @brief		更新処理
	 */
	void LateUpdate()override;

	/**
	 * @brief		自身のインスタンスを返す
	 * @return		自身のインスタンスの参照
	 */
	static MovieManager& Instance();

	/**
	 * @brief		動画再生
	 * @param[in]	キー
	 * @param[in]	再生中の場合、再生をリセットするか
	 */
	void Play(const std::string& _key, bool _isReset = false);

	/**
	 * @brief		動画再生
	 * @param[in]	キー
	 * @param[in]	再生中の場合、再生をリセットするか
	 */
	void Play(const std::string& _key, SceneTag _tag, bool _isReset = false);

	/**
	 * @brief		再生停止
	 * @param[in]	キー
	 * @param[in]	再生中の場合、再生をリセットするか
	 */
	void Stop(const std::string& _key, bool _isReset = false);

	/**
	 * @brief		再生停止
	 * @param[in]	キー
	 * @param[in]	再生中の場合、再生をリセットするか
	 */
	void Stop(const std::string& _key, SceneTag _tag, bool _isReset = false);

	/**
	 * @brief		動画のインスタンスを返す
	 * @param[in]	キー
	 * @return		動画のインスタンス
	 */
	std::unique_ptr<VideoPlayer>& GetMovie(const std::string& _key);

	/**
	* @brief		動画データの読み込み
	* @param[in]	シーンタグ
	*/
	void LoadMovie(SceneTag _sceneTag);


private:

	//! 自身のインスタンス
	static MovieManager* instance;

	//! 現在のシーン
	SceneTag crrSceneTag;

	//! Titleシーンで使用する動画
	std::unordered_map <std::string, std::unique_ptr<VideoPlayer>> movie_title;
	//! MainMenuシーンで使用する動画
	std::unordered_map <std::string, std::unique_ptr<VideoPlayer>> movie_MainMenu;
	//! Gameシーンで使用する動画
	std::unordered_map <std::string, std::unique_ptr<VideoPlayer>> movie_game;


	/**
	 * @brief		CSVファイルからデータの読み込み
	 * @param[in]	読み込むCSVファイルのパス
	 * @param[out]	読みこんだデータのアウトプット先
	 */
	void LoadCSV(const std::string& _path, std::unordered_map <std::string, std::unique_ptr<VideoPlayer>>& _output);
};

