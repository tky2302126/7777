/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneTitleの定義ファイル
*/

#pragma once
#include "SceneBase.h"
#include "MovieManager.h"
#include "UIManager.h"
#include "Board.h"
#include "Mouse.h"
#include "UDPConnection.h"

/**
 * @class	SceneTitle
 * @brief   タイトルシーン
 */
class SceneGame : public SceneBase
{
public:
	// メソッド

	/**
	 * @brief       コンストラクタ
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	SceneGame();

	/**
	 * @brief       デストラクタ
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	~SceneGame() override;

	/**
	 * @brief       ロード完遂時の関数
	 */
	void LoadComplete() override;

	/**
	 * @brief       キー入力時のコールバック
	 * @param[in]	コールバックコンテキスト
	 */
	void KeyInputCallback(InputAction::CallBackContext _c)override;

	/**
	 * @brief       毎F呼ばれるメソッド
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void Update() override;

	/**
	 * @brief       毎F呼ばれるメソッド
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void LateUpdate() override;


private:

	//! テキストのフォント
	int menuFont;

	//! 盤面
	std::shared_ptr<HWGameObject> board = nullptr;
	//! 盤面のコンポーネント
	Board* boardCp = nullptr;
	//! 直近のカード配置時間
	int lastPlacedTime = 0;
	// カウントダウン用のグラフィックハンドル
	int CountDouwnGH;

	Vector2Int countDownLeftTop;

	int alpha;
	
	int fadeSpeed = 9;

	bool isFade;

	bool isCountDown = false;

	int UDPSocketHandle[3];

	void CountDown();
};