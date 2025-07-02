#pragma once
#include "HWCollider.h"


/**
* @author   NZ
* @date     24/09/15
* @note		モデルのコライダーコンポーネントの定義
*/


/**
 * @class	HWModelCollider
 * @brief	モデルのコライダーコンポーネント
 */
class HWModelCollider: public HWCollider
{
	// 特定のクラス以外からのアクセスを防ぐためのフレンド宣言
	friend class HWGameObject;
	friend class CollisionWaltan;

public:

	/*     メンバ変数     */

	/**
	 * @brief		モデルハンドル
	 * @History		24/10/17 作成(NZ)
	 */
	int modelHandle;

	/**
	 * @brief		コリジョンの情報を更新するフレームの番号
	 * @History		24/10/17 作成(NZ)
	 */
	int frameIndex;


	 /*     メソッド     */

public:

	/**
	 * @brief		コンストラクタ
	 * @author		NZ
	 * @date		24/10/17
	 */
	HWModelCollider();

	/**
	 * @brief		デストラクタ
	 * @author		NZ
	 * @date		24/10/17
	 */
	‾HWModelCollider();

private:

#pragma region オーバーライドメソッド

	/**
	 * @brief		モデルのコライダーを描画する
	 * @detail		オーバライドメソッド
	 * @author		NZ
	 * @date		24/10/17
	 */
	void DrawCollider() override;

	/**
	 * @brief		モデルのコライダーを構成する
	 * @detail		オーバライドメソッド
	 * @author		NZ
	 * @date		24/10/17
	 */
	void SetCollider() override;

	/**
	 * @brief		HWGameObjectにアタッチされた瞬間に働く
	 * @detail		オーバライドメソッド
	 * @author		NZ
	 * @date		24/10/17
	 */
	void Awake()override;

	/**
	 * @brief		毎フレーム呼ばれる
	 * @detail		オーバーライドメソッド
	 * @author		NZ
	 * @date		24/10/17
	 */
	void Update() override;

#pragma endregion
};

