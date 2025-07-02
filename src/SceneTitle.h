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
#include <stack>


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


private:

	//! カーソル
	Cursor cursor;
	//! 選択項目
	int selectIndex;
	//! 項目を選択中
	bool isSelect;
	//! 入力ハンドル(ip/ポート番号)
	int inputHandle;
	//! 未入力の項目を判別するために、一度intを経由してからIPDATA型に変換する
	int ipBuffer[4];
	//! サーバーで使うクライアントのネットワークハンドル
	int NetWorkHandles[3];
	//! サーバーで使う受信データ
	std::stack<char[256]> recvStack;
	

	/**
	 * @brief       決定キーを押した際の処理
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void SelectInput();

	/**
	* @brief		サーバー側のイニシャライズ
	* @author		Suzuki h
	* @date			25/7/2
	*/
	void ServerInit();

	/**
	* @brief		サーバー側の処理
	* @author		Suzuki h
	* @date			25/7/2
	*/
	void ServerUpdate();

	/**
	* @brief		接続待機処理
	* @author		Suzuki h
	* @date			25/7/2
	*/
	void Connect();

	/**
	* @brief		切断処理
	* @author		Suzuki h
	* @date			25/7/2
	*/
	void DisConnect();

	/**
	* @brief		受信待機処理
	* @author		Suzuki h
	* @date			25/7/2
	*/
	void RecieveNetData();

};