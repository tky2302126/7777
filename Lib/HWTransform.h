#pragma once
#include "HWComponent.h"
#include "HWGameObject.h"

class HWGameObject;

/**
* @author   NZ
* @date     24/07/16
* @note		座標系の情報を保持するコンポーネントの定義
*/


/**
 * @class	HWTransform
 * @brief	オブジェクトの座標や回転などを保持するコンポーネント
 */
class HWTransform : public HWComponent
{
	// 特定のクラス以外からのアクセスを防ぐためのフレンド宣言
	friend class HWGameObject;
	friend class CollisionWaltan;

public:

	/*     メンバ変数     */

#pragma region グローバル

	/**
	 * @brief		グローバル座標
	 * @History		24/06/17 作成(NZ)
	 */
	VECTOR position = {0,0,0};

	/**
	 * @brief		グローバル回転
	 * @History		24/06/17 作成(NZ)
	 */

	VECTOR rotate = { 0,0,0 };

	/**
	 * @brief		グローバル拡縮
	 * @History		24/06/17 作成(NZ)
	 */
	VECTOR scale = { 1,1,1 };

	/**
	 * @brief		グローバル変換行列
	 * @History		24/09/15 作成(NZ)
	 */
	MATRIX globalMat;

#pragma endregion

#pragma region ローカル

	/**
	 * @brief		ローカル座標
	 * @History		24/06/17 作成(NZ)
	 */
	VECTOR localPosition;

	/**
	 * @brief		ローカル回転
	 * @History		24/06/17 作成(NZ)
	 */

	VECTOR localRotate;

	/**
	 * @brief		ローカル拡縮
	 * @History		24/06/17 作成(NZ)
	 */
	VECTOR localScale;

#pragma endregion

	/**
	 * @brief		移動ベクトル
	 * @History		24/09/26 作成(NZ)
	 */
	VECTOR velocity = { 0,0,0 };

	/**
	 * @brief		正面方向のベクトル
	 * @History		24/09/26 作成(NZ)
	 */
	VECTOR forward;

private:

	/**
	 * @brief		前Fの座標
	 * @History		24/10/12 作成(NZ)
	 */
	VECTOR previousPosition;


private:
	/*     メソッド     */

	/**
	 * @brief		平行移動、回転、拡縮を設定する
	 * @author		NZ
	 * @date		24/09/15
	 */
	void SetMatrix();



public:

	/**
	 * @brief		ターゲットのほうへ向く
	 * @param[in]	const VECTOR&	ターゲットの座標
	 * @author		NZ
	 * @date		24/10/09
	 */
	void LookAt(const VECTOR& _target);

#pragma region コンストラクタ

	/**
	 * @brief		コンストラクタ
	 * @author		NZ
	 * @date		24/06/17
	 */
	HWTransform();

	/**
	 * @brief		デストラクタ
	 * @detail		オーバーライド関数
	 * @author		NZ
	 * @date		24/09/17
	 */
	‾HWTransform(){}

#pragma endregion

protected:

#pragma region オーバーライドメソッド

	/**
	 * @brief		毎フレーム呼ばれる
	 * @detail		オーバーライド関数
	 * @author		NZ
	 * @date		24/06/17
	 */
	void Update() override;

#pragma endregion
};