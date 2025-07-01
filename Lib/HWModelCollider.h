#pragma once
#include "HWCollider.h"


/**
* @author   NZ
* @date     24/09/15
* @note		���f���̃R���C�_�[�R���|�[�l���g�̒�`
*/


/**
 * @class	HWModelCollider
 * @brief	���f���̃R���C�_�[�R���|�[�l���g
 */
class HWModelCollider: public HWCollider
{
	// ����̃N���X�ȊO����̃A�N�Z�X��h�����߂̃t�����h�錾
	friend class HWGameObject;
	friend class CollisionWaltan;

public:

	/*     �����o�ϐ�     */

	/**
	 * @brief		���f���n���h��
	 * @History		24/10/17 �쐬(NZ)
	 */
	int modelHandle;

	/**
	 * @brief		�R���W�����̏����X�V����t���[���̔ԍ�
	 * @History		24/10/17 �쐬(NZ)
	 */
	int frameIndex;


	 /*     ���\�b�h     */

public:

	/**
	 * @brief		�R���X�g���N�^
	 * @author		NZ
	 * @date		24/10/17
	 */
	HWModelCollider();

	/**
	 * @brief		�f�X�g���N�^
	 * @author		NZ
	 * @date		24/10/17
	 */
	~HWModelCollider();

private:

#pragma region �I�[�o�[���C�h���\�b�h

	/**
	 * @brief		���f���̃R���C�_�[��`�悷��
	 * @detail		�I�[�o���C�h���\�b�h
	 * @author		NZ
	 * @date		24/10/17
	 */
	void DrawCollider() override;

	/**
	 * @brief		���f���̃R���C�_�[���\������
	 * @detail		�I�[�o���C�h���\�b�h
	 * @author		NZ
	 * @date		24/10/17
	 */
	void SetCollider() override;

	/**
	 * @brief		HWGameObject�ɃA�^�b�`���ꂽ�u�Ԃɓ���
	 * @detail		�I�[�o���C�h���\�b�h
	 * @author		NZ
	 * @date		24/10/17
	 */
	void Awake()override;

	/**
	 * @brief		���t���[���Ă΂��
	 * @detail		�I�[�o�[���C�h���\�b�h
	 * @author		NZ
	 * @date		24/10/17
	 */
	void Update() override;

#pragma endregion
};

