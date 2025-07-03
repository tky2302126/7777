#pragma once
#include "HWComponent.h"
#include "HWTransform.h"


/**
* @author   NZ
* @date     24/09/20
* @note		
*/


/**
 * @class	HWCamera
 * @brief   カメラ操作用の
 */
class HWCamera : public HWComponent
{
public:

	/*     メンバ変数     */

	/**
	 * @brief		注視点
	 * @History		24/09/20 作成(NZ)
	 */
	VECTOR target;	


public:
	/*     メソッド     */

	/**
	 * @brief		コンストラクタ
	 * @author		NZ
	 * @date		24/09/20
	 */
	HWCamera();


#pragma region オーバーライドメソッド

	/**
	 * @brief		HWGameObjectにアタッチされた瞬間に働く
	 * @detail		オーバーライド関数
	 * @author		NZ
	 * @date		24/06/17
	 */
	void Awake() override;

	/**
	 * @brief		毎フレーム呼ばれる
	 * @detail		オーバーライド関数
	 * @author		NZ
	 * @date		24/09/01
	 */
	void LateUpdate() override;

#pragma endregion
};

