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

	//! ゲーム開始フラグ
	bool isGame = false;
	std::ofstream outputfile_c;
	std::ofstream outputfile_s;
	//! 扇形ゲージの画像ハンドル
	int gaugeHandle;


	/**
	 * @brief       イベントの告知をクライアントに送信する
	 * @param[in]	送信データ
	 */
	void SendEventData(EventData&);

	/**
	 * @brief       カウントダウン
	 */
	void CountDown();

	/**
	 * @brief       マウス操作を見て、カードの配置を行う
	 */
	void CheckMouseInput();

	/**
	 * @brief       serverからカードの初期配置を受信する
	 * @detail		client限定
	 * @return		初期配置を受信した場合、以降true
	 */
	int ReceiveInitData();

	/**
	 * @brief       Update前に最初のカードデータを送る
	 * @detail		サーバー側でゲーム開始時に最初のカードデータを全プレイヤーに送信する
	 */
	void SendInitData();

	/**
	 * @brief       clientからカードの更新要素を受信する
	 * @return		0 = 受信なし, 1 = 受信あり, -1 = 問題発生
	 */
	int ReceiveUpdateData_Client();

	/**
	 * @brief       serverからカードの更新要素を受信する
	 * @return		0 = 受信なし, 1 = 受信あり, -1 = 問題発生
	 */
	int ReceiveUpdateData_Server();

	/**
	 * @brief       受信したデータがゲームデータの場合
	 * @param[in]	受信データ
	 */
	void ReceivingGameData(unsigned char* _recvData);

	/**
	 * @brief       受信したデータがイベントデータの場合
	 * @param[in]	受信データ
	 */
	void ReceivingEventData(unsigned char* _recvData);
};