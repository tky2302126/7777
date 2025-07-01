#pragma once
#include "HWCollider.h"
#include "HandlerWaltan.h"
#include "CollisionWaltan.h"


/**
* @author   NZ
* @date     24/09/15
* @note		�J�v�Z���^�̃R���C�_�[�R���|�[�l���g�̒�`
*/


/**
 * @class	HWCapsuleCollider
 * @brief	�J�v�Z���^�̃R���C�_�[�R���|�[�l���g
 */
class HWCapsuleCollider : public HWCollider
{
	// ����̃N���X�ȊO����̃A�N�Z�X��h�����߂̃t�����h�錾
	friend class HWGameObject;
	friend class CollisionWaltan;

public:

	/*     �����o�ϐ�     */


	/**
	 * @brief		�R���C�_�[�̍��� (���g�Ŏn�_�ƏI�_��ݒ肵���ꍇ�A�����������)
	 * @History		24/09/16 �쐬(NZ)
	 */
	float height;

	/**
	 * @brief		�R���C�_�[�̔��a
	 * @History		24/09/16 �쐬(NZ)
	 */
	float radius;

	/**
	 * @brief		�R���C�_�[�̎n�_
	 * @History		24/09/16 �쐬(NZ)
	 */
	VECTOR UsStartPos;

	/**
	 * @brief		�R���C�_�[�̏I�_
	 * @History		24/09/16 �쐬(NZ)
	 */
	VECTOR UsEndPos;


private:

	/**
	 * @brief		�R���C�_�[�̎n�_
	 * @History		24/09/16 �쐬(NZ)
	 */
	VECTOR startPos;

	/**
	 * @brief		�R���C�_�[�̏I�_
	 * @History		24/09/16 �쐬(NZ)
	 */
	VECTOR endPos;


	 /*     ���\�b�h     */

public:

	/**
	 * @brief		�R���X�g���N�^
	 * @author		NZ
	 * @date		24/09/16
	 */
	HWCapsuleCollider();

	/**
	 * @brief		�f�X�g���N�^
	 * @author		NZ
	 * @date		24/09/16
	 */
	~HWCapsuleCollider();

private:



#pragma region �����o������

	/**
	 * @brief		�{�b�N�X�^�C�v�̃I�u�W�F�N�g�ƏՓ˂����ۂɂ߂荞�܂Ȃ����鏈��
	 * @author		NZ
	 * @date		24/09/26
	 */
	void PushOut_Capsule_Box(HWCollider& other);

	/**
	 * @brief		�J�v�Z���^�C�v�̃I�u�W�F�N�g�ƏՓ˂����ۂɂ߂荞�܂Ȃ����鏈��
	 * @author		NZ
	 * @date		24/09/26
	 */
	void PushOut_Capsule_Capsule(HWCapsuleCollider& other);

	/**
	 * @brief		�X�t�B�A�^�C�v�̃I�u�W�F�N�g�ƏՓ˂����ۂɂ߂荞�܂Ȃ����鏈��
	 * @author		NZ
	 * @date		24/09/26
	 */
	void PushOut_Capsule_Sphere(HWCollider& other);

#pragma endregion

#pragma region �I�[�o�[���C�h���\�b�h

	/**
	 * @brief		�����̂̃R���C�_�[��`�悷��
	 * @detail		�I�[�o���C�h���\�b�h
	 * @author		NZ
	 * @date		24/09/16
	 */
	void DrawCollider() override;

	/**
	 * @brief		�����̂̃R���C�_�[���\������
	 * @detail		�I�[�o���C�h���\�b�h
	 * @author		NZ
	 * @date		24/09/16
	 */
	void SetCollider() override;

	/**
	 * @brief		HWGameObject�ɃA�^�b�`���ꂽ�u�Ԃɓ���
	 * @detail		�I�[�o���C�h���\�b�h
	 * @author		NZ
	 * @date		24/09/15
	 */
	void Awake()override;

	/**
	 * @brief		���t���[���Ă΂��
	 * @detail		�I�[�o�[���C�h���\�b�h
	 * @author		NZ
	 * @date		24/09/16
	 */
	void Update() override;

	/**
	 * @brief		�R���C�_�[�Փˎ��ɓ������\�b�h
	 * @detail		�I�[�o�[���C�h���\�b�h
	 * @author		NZ
	 * @date		24/09/26
	 */
	void OnCollisionEnter(HWCollider& _collider)override;

#pragma endregion
};

