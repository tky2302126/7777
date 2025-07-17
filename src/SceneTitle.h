/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneTitleの定義ファイル
*/

#pragma once
#include "SceneBase.h"
#include "MovieManager.h"
#include "UIManager.h"
#include "Cursor.h"
#include "GameManager.h"
#include "UDPConnection.h"
#include "AudioManager.h"

/**
 * @class	SceneTitle
 * @brief   タイトルシーン
 */
class SceneTitle : public SceneBase
{
public:

	/**
	 * @brief       コンストラクタ
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	SceneTitle();

	/**
	 * @brief       デストラクタ
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	~SceneTitle() override;

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

	AudioManager audio;
private:

	//! カーソル
	Cursor cursor;
	//! 選択項目
	int selectIndex;
	//! 項目を選択中
	bool isSelect;
	//! 入力ハンドル
	int inputHandle;
	//! 未入力の項目を判別するために、一度intを経由してからIPDATA型に変換する
	int ipBuffer[4];
	//! サーバーで使うクライアントのネットワークハンドル
	int NetWorkHandles[3];
	//! サーバーで使う受信データ
	//! 接続するサーバーのIPアドレスデータ
	IPDATA ipData;
	//! ポート番号
	int portId;
	//! 接続パラメータ
	ConnectParameter connectParameter = ConnectParameter::None;

	//! タイトル画面のグラフィックハンドル
	int gh_title;
	int gh_titleBack;
	int gh_titleLogo;

	int offsetX = 0;
	const int tileSize = 240;         // gh_titleの画像サイズ
	const int tilesX = 1920/tileSize; // gh_titleを何列描画するか
	const int tilesY = 5;             // gh_titleを何段描画するか (1080/tileSize を切り上げた数)

	/**
	 * @brief       決定キーを押した際の処理
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void SelectInput();

	/**
	 * @brief       serverの場合の入力フォームの表示
	 * @author      Suzuki N
	 * @date        25/07/03
	 */
	void ServerInputForm();

	/**
	 * @brief       clientの場合の入力フォームの表示
	 * @author      Suzuki N
	 * @date        25/07/03
	 */
	void ClientInputForm();

	/**
	 * @brief       一定時間ごとに指定のIPアドレスとポート番号で接続を試みる
	 * @author      Suzuki N
	 * @date        25/07/03
	 */
	void Connect();
};