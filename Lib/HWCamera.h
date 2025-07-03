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
 * @brief   �J��������p��
 */
class HWCamera : public HWComponent
{
public:

	/*     �����o�ϐ�     */

	/**
	 * @brief		�����_
	 * @History		24/09/20 �쐬(NZ)
	 */
	VECTOR target;	


public:
	/*     ���\�b�h     */

	/**
	 * @brief		�R���X�g���N�^
	 * @author		NZ
	 * @date		24/09/20
	 */
	HWCamera();


#pragma region �I�[�o�[���C�h���\�b�h

	/**
	 * @brief		HWGameObject�ɃA�^�b�`���ꂽ�u�Ԃɓ���
	 * @detail		�I�[�o�[���C�h�֐�
	 * @author		NZ
	 * @date		24/06/17
	 */
	void Awake() override;

	/**
	 * @brief		���t���[���Ă΂��
	 * @detail		�I�[�o�[���C�h�֐�
	 * @author		NZ
	 * @date		24/09/01
	 */
	void LateUpdate() override;

#pragma endregion
};

