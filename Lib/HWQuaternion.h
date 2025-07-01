#pragma once
#include "HWComponent.h"

/**
* @author   NZ
* @date     24/09/15
* @note		���̌^�̃R���C�_�[�R���|�[�l���g�̒�`
*/


/**
 * @class	HWSphereCollider
 * @brief	���̌^�̃R���C�_�[�R���|�[�l���g
 */
class HWQuaternion
{
public:

	/*     �����o�ϐ�     */

    //! �X�J���[����
    float w; 
    //! �x�N�g������
    float x, y, z;


public:
    // ���\�b�h


    /**
     * @brief   �R���X�g���N�^
     * @History 24/10/16 �쐬(NZ)
     */
    HWQuaternion();

    /**
     * @brief   �R���X�g���N�^
     * @History 24/10/16 �쐬(NZ)
     */
    HWQuaternion(float w, float x, float y, float z);


    /**
     * @brief   �N�H�[�^�j�I���̐��K��
     * @History 24/10/16 �쐬(NZ)
     */
    HWQuaternion Normalize() const;

    /**
     * @brief   �N�H�[�^�j�I���̋t���i�����j
     * @History 24/10/16 �쐬(NZ)
     */
    HWQuaternion Conjugate() const;

    /**
     * @brief   �N�H�[�^�j�I���̐ρi2�̃N�H�[�^�j�I������������j
     * @History 24/10/16 �쐬(NZ)
     */
    HWQuaternion operator*(const HWQuaternion& q) const;

    /**
     * @brief   �N�H�[�^�j�I���ƃx�N�g���̐ρi�x�N�g���ɃN�H�[�^�j�I����K�p�j
     * @History 24/10/16 �쐬(NZ)
     */
    VECTOR RotateVector(const VECTOR& v) const;

    /**
     * @brief   �N�H�[�^�j�I������]���Ɗp�x���琶��
     * @History 24/10/16 �쐬(NZ)
     */
    static HWQuaternion FromAxisAngle(const VECTOR& axis, float angle);

    /**
     * @brief   �N�H�[�^�j�I������]�s��ɕϊ�
     * @History 24/10/16 �쐬(NZ)
     */
    MATRIX ToMatrix() const;
};
