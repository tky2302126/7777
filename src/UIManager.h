/**
 * @file	UIManager.h
 * @brief	UI関係
 * @author	NS
 * @date	2024/1/29
 */

#pragma once
#include "VideoPlayer.h"

 // 前方宣言
class CharacterBase;

 /**
  * @class	UIManager
  * @brief  UI関係をまとめたクラス
  */
class UIManager : public HWComponent
{
public:
	
	/**
	 * @brief		デストラクタ
	 */
	~UIManager();

	/**
	 * @brief		初期化処理
	 */
	void Awake()override;

	/**
	 * @brief		フェードイン
	 * @param[in]	暗転に掛ける時間
	 * @param[in]	暗転している時間
	 */
	static void FadeIn(int _speed, int _frame, bool _autoFadeOut = true);

	/**
	 * @brief		フェードアウト
	 * @param[in]	暗転に掛ける時間
	 */
	static void FadeOut(int _speed);

	/**
	 * @brief		静的オブジェクトの初期化
	 */
	static void ManualInitialize();

	/**
	 * @brief		フェードイン、フェードアウト中の処理
	 */
	static void ManualLateUpdate();

	/**
	 * @brief		ロード中の処理
	 */
	static void LoadingAnimation();


private:

	//! フェードイン、フェードアウト用画像
	static int fadeGraphHandle;
	//! フェードイン、フェードアウト中
	static bool isFade;
	//! 画像のα値
	static int alpha;
	//! α値の加算値
	static int add;
	static int loadingGraphHandle;
	static int 	menuFont;
};

