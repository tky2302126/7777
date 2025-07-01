#pragma once
#include "HWComponent.h"
#include "HWGameObject.h"

class HWGameObject;

/**
* @author   NZ
* @date     24/07/16
* @note		���W�n�̏���ێ�����R���|�[�l���g�̒�`
*/


/**
 * @class	HWTransform
 * @brief	�I�u�W�F�N�g�̍��W���]�Ȃǂ�ێ�����R���|�[�l���g
 */
class HWTransform : public HWComponent
{
	// ����̃N���X�ȊO����̃A�N�Z�X��h�����߂̃t�����h�錾
	friend class HWGameObject;
	friend class CollisionWaltan;

public:

	/*     �����o�ϐ�     */

#pragma region �O���[�o��

	/**
	 * @brief		�O���[�o�����W
	 * @History		24/06/17 �쐬(NZ)
	 */
	VECTOR position = {0,0,0};

	/**
	 * @brief		�O���[�o����]
	 * @History		24/06/17 �쐬(NZ)
	 */

	VECTOR rotate = { 0,0,0 };

	/**
	 * @brief		�O���[�o���g�k
	 * @History		24/06/17 �쐬(NZ)
	 */
	VECTOR scale = { 1,1,1 };

	/**
	 * @brief		�O���[�o���ϊ��s��
	 * @History		24/09/15 �쐬(NZ)
	 */
	MATRIX globalMat;

#pragma endregion

#pragma region ���[�J��

	/**
	 * @brief		���[�J�����W
	 * @History		24/06/17 �쐬(NZ)
	 */
	VECTOR localPosition;

	/**
	 * @brief		���[�J����]
	 * @History		24/06/17 �쐬(NZ)
	 */

	VECTOR localRotate;

	/**
	 * @brief		���[�J���g�k
	 * @History		24/06/17 �쐬(NZ)
	 */
	VECTOR localScale;

#pragma endregion

	/**
	 * @brief		�ړ��x�N�g��
	 * @History		24/09/26 �쐬(NZ)
	 */
	VECTOR velocity = { 0,0,0 };

	/**
	 * @brief		���ʕ����̃x�N�g��
	 * @History		24/09/26 �쐬(NZ)
	 */
	VECTOR forward;

private:

	/**
	 * @brief		�OF�̍��W
	 * @History		24/10/12 �쐬(NZ)
	 */
	VECTOR previousPosition;


private:
	/*     ���\�b�h     */

	/**
	 * @brief		���s�ړ��A��]�A�g�k��ݒ肷��
	 * @author		NZ
	 * @date		24/09/15
	 */
	void SetMatrix();



public:

	/**
	 * @brief		�^�[�Q�b�g�̂ق��֌���
	 * @param[in]	const VECTOR&	�^�[�Q�b�g�̍��W
	 * @author		NZ
	 * @date		24/10/09
	 */
	void LookAt(const VECTOR& _target);

#pragma region �R���X�g���N�^

	/**
	 * @brief		�R���X�g���N�^
	 * @author		NZ
	 * @date		24/06/17
	 */
	HWTransform();

	/**
	 * @brief		�f�X�g���N�^
	 * @detail		�I�[�o�[���C�h�֐�
	 * @author		NZ
	 * @date		24/09/17
	 */
	~HWTransform(){}

#pragma endregion

protected:

#pragma region �I�[�o�[���C�h���\�b�h

	/**
	 * @brief		���t���[���Ă΂��
	 * @detail		�I�[�o�[���C�h�֐�
	 * @author		NZ
	 * @date		24/06/17
	 */
	void Update() override;

#pragma endregion
};