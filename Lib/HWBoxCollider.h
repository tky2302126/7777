#pragma once
#include "HWCollider.h"
#include "HandlerWaltan.h"
#include "CollisionWaltan.h"


/**
* @author   NZ
* @date     24/09/15
* @note		�����^�̃R���C�_�[�R���|�[�l���g�̒�`
*/


/**
 * @class	HWBoxCollider
 * @brief	�����^�̃R���C�_�[�R���|�[�l���g
 */
class HWBoxCollider : public HWCollider
{
	// ����̃N���X�ȊO����̃A�N�Z�X��h�����߂̃t�����h�錾
	friend class HWGameObject;
	friend class CollisionWaltan;

public:

	/*     �����o�ϐ�     */

	/**
	 * @brief		�R���C�_�[�̃T�C�Y
	 * @History		24/09/16 �쐬(NZ)
	 */
	VECTOR size;

	/**
	 * @brief		��]�s��
	 * @History		24/09/16 �쐬(NZ)
	 */
	MATRIX mRotate;

	/**
	 * @brief		�R���C�_�[�̊e���_���W
	 * @History		24/09/18 �쐬(NZ)
	 */
	VECTOR vertex[2][4];

	/*     ���\�b�h     */

public:

	/**
	 * @brief		�R���X�g���N�^
	 * @detail		�����ŃR���C�_�[�̃T�C�Y���w���
	 * @author		NZ
	 * @date		24/09/16
	 */
	HWBoxCollider();

	/**
	 * @brief		�R���X�g���N�^
	 * @detail		�����ŃR���C�_�[�̃T�C�Y���w���
	 * @author		NZ
	 * @date		24/09/16
	 */
	HWBoxCollider(const VECTOR& _size);

	/**
	 * @brief		�R���X�g���N�^
	 * @detail		�����ŃR���C�_�[�̃T�C�Y���w���
	 * @author		NZ
	 * @date		24/09/16
	 */
	HWBoxCollider(const float& _sizeX, const float& _sizeY, const float& _sizeZ);

	/**
	 * @brief		�f�X�g���N�^
	 * @author		NZ
	 * @date		24/09/16
	 */
	~HWBoxCollider();

protected:

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

