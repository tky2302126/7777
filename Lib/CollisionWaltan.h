#pragma once
#include "Utilities.h"
#include "HandlerWaltan.h"
#include "HWBoxCollider.h"
#include "HWSphereCollider.h"
#include "HWCapsuleCollider.h"
#include "HWModelCollider.h"


/**
* @author   NZ
* @date     24/08/09
* @note		ColliderWaltan�̒�`�t�@�C��
*/


/**
 * @class	ColliderWaltan
 * @brief   ��F�R���C�_�[�R���|�[�l���g�̂����蔻����Ď����A�����ɉ������n���h���[���Ăяo��
 */
class CollisionWaltan
{
	// ����̃N���X�ȊO����̃A�N�Z�X��h�����߂̃t�����h�錾
	friend class HandlerWaltan;
    friend class HWBoxCollider;
    friend class HWSphereCollider;
    friend class HWCapsuleCollider;
    friend class HWModelCollider;

    // �R���W�����`�F�b�N�Ɏg���\����

    /**
    * @struct	OBB
    * @brief	�����̂̓����蔻��
    */
    struct OBB {
        //! OBB�̒��S���W
        VECTOR c;      
        //! OBB�̊e��(���K�����ꂽ)
        VECTOR u[3];     
        //! �e�������̃n�[�t�T�C�Y
        VECTOR e;
    };

private:

    /*     �����o�ϐ�     */

    /**
     * @brief		�C���X�^���X������Ă���R���C�_�[
     * @History		24/09/17 �쐬(NZ)
     */
    std::vector<HWCollider*> ColVec;


private:

    /*     ���\�b�h     */

    /**
     * @brief       �C���X�^���X���擾����ÓI���\�b�h
     * @detail      ���߂̈�񂾂��C���X�^���X�𐶐�����
     * @return      CollisionWaltan& �V���O���g���C���X�^���X
     * @author      NZ
     * @date        24/07/19
     */
    static CollisionWaltan& Instance()
    {
        // �V���O���g���C���X�^���X�𐶐�
        static CollisionWaltan instance;
        return instance;
    }

    //�C���X�^���X�̃R�s�[�֎~
    //�f�t�H���g�̃R�s�[�R���X�g���N�^���폜
    CollisionWaltan(const CollisionWaltan&) = delete;
    //�f�t�H���g�̃R�s�[������Z�q���폜
    CollisionWaltan& operator=(const CollisionWaltan&) = delete;

    /**
     * @brief       �R���X�g���N�^
     * @author      NZ
     * @date        24/07/19
     */
    CollisionWaltan();

    /**
     * @brief       �f�X�g���N�^
     * @author      NZ
     * @date        24/07/19
     */
    ~CollisionWaltan();

    /**
      * @brief       �e�R���|�[�l���g��Update���\�b�h��S�ČĂяo��
      * @author      NZ
      * @date        24/08/22
      */
    void Update();

    /**
     * @brief       �o�^����Ă���R���C�_�[�����폜����
     * @param[in]   HWCollider* �폜����R���C�_�[���
     * @author      NZ
     * @date        24/09/17
     */
    void UnRegister(HWCollider* _collider);

    /**
      * @brief       �v�f1 ��BoxCollider�̏ꍇ�̃R���W�����`�F�b�N
      * @param[in]   HWBoxCollider* �����蔻��̏d�Ȃ�����闧���̌^Collider���1
      * @param[in]   HWCollider*    �����蔻��̏d�Ȃ������Collider���2
      * @author      NZ
      * @date        24/09/17
      */
    bool CollCheck_Box(HWBoxCollider* _boxCol1, HWCollider* _col2);

    /**
      * @brief       �v�f1 ��CapsuleCollider�̏ꍇ�̃R���W�����`�F�b�N
      * @param[in]   HWCapsuleCollider*  �����蔻��̏d�Ȃ������J�v�Z���^Collider���1
      * @param[in]   HWCollider*         �����蔻��̏d�Ȃ������Collider���2
      * @author      NZ
      * @date        24/09/17
      */
    bool CollCheck_Capsule(HWCapsuleCollider* _col1, HWCollider* _col2);

    /**
      * @brief       �v�f1 ��SphereCollider�̏ꍇ�̃R���W�����`�F�b�N
      * @param[in]   HWSphereCollider*   �����蔻��̏d�Ȃ�����鋅�̌^Collider���1
      * @param[in]   HWCollider*         �����蔻��̏d�Ȃ������Collider���2
      * @author      NZ
      * @date        24/09/17
      */
    bool CollCheck_Sphere(HWSphereCollider* _col1, HWCollider* _col2);

    /**
      * @brief       �v�f1 ��ModelCollider�̏ꍇ�̃R���W�����`�F�b�N
      * @param[in]   HWModelCollider*    �����蔻��̏d�Ȃ�����郂�f��Collider���1
      * @param[in]   HWCollider*         �����蔻��̏d�Ȃ������Collider���2
      * @author      NZ
      * @date        24/10/17
      */
    bool CollCheck_Model(HWModelCollider* _col1, HWCollider* _col2);


#pragma region BOX�^�C�v�̏Փ˔���

    /**
      * @brief       �J�v�Z���ƃ|���S���̂����蔻��
      * @param[in]   HWBoxCollider*      �����蔻��̏d�Ȃ������Collider���1
      * @param[in]   HWModelCollider*    �����蔻��̏d�Ȃ�����郂�f���n���h��
      * @author      NZ
      * @date        24/09/30
      */
    bool CollCheck_Box_Model(HWBoxCollider* _boxCol, HWModelCollider* _modelCol);

    /**
      * @brief       �{�b�N�X�ƃ{�b�N�X�̂����蔻��
      * @param[in]   HWBoxCollider*      �����蔻��̏d�Ȃ������Collider���1
      * @param[in]   HWBoxCollider*      �����蔻��̏d�Ȃ������Collider���2
      * @author      NZ
      * @date        24/09/17
      */
    bool CollCheck_Box_Box(HWBoxCollider* _boxCol, HWBoxCollider* _boxCol2);

    /**
      * @brief       �{�b�N�X�ƃJ�v�Z���̂����蔻��
      * @param[in]   HWBoxCollider*      �����蔻��̏d�Ȃ������Collider���1
      * @param[in]   HWCapsuleCollider*  �����蔻��̏d�Ȃ������Collider���2
      * @author      NZ
      * @date        24/09/17
      */
    bool CollCheck_Box_Capsule(HWBoxCollider* _boxCol, HWCapsuleCollider* _capsuleCol);

    /**
      * @brief       �{�b�N�X�ƃX�t�B�A�̂����蔻��
      * @param[in]   HWBoxCollider*      �����蔻��̏d�Ȃ������Collider���1
      * @param[in]   HWSphereCollider*   �����蔻��̏d�Ȃ������Collider���2
      * @author      NZ
      * @date        24/09/17
      */
    bool CollCheck_Box_Sphere(HWBoxCollider* _boxCol, HWSphereCollider* _sphereCol);

#pragma endregion

#pragma region CAPSULE�^�C�v�̏Փ˔���

    /**
      * @brief       �J�v�Z���ƃ|���S���̂����蔻��
      * @param[in]   HWCapsuleCollider*  �����蔻��̏d�Ȃ������Collider���1
      * @param[in]   HWModelCollider*    �����蔻��̏d�Ȃ�����郂�f���n���h��
      * @author      NZ
      * @date        24/09/30
      */
    bool CollCheck_Capsule_Model(HWCapsuleCollider* _capsuleCol, HWModelCollider* _modelCol);

    /**
      * @brief       �J�v�Z���ƃ{�b�N�X�̂����蔻��
      * @param[in]   HWCapsuleCollider*  �����蔻��̏d�Ȃ������Collider���1
      * @param[in]   HWBoxCollider*      �����蔻��̏d�Ȃ������Collider���2
      * @author      NZ
      * @date        24/09/17
      */
    bool CollCheck_Capsule_Box(HWCapsuleCollider* _capsuleCol, HWBoxCollider* _boxCol);

    /**
      * @brief       �J�v�Z���ƃJ�v�Z���̂����蔻��
      * @param[in]   HWCapsuleCollider*  �����蔻��̏d�Ȃ������Collider���1
      * @param[in]   HWCapsuleCollider*  �����蔻��̏d�Ȃ������Collider���2
      * @author      NZ
      * @date        24/09/17
      */
    bool CollCheck_Capsule_Capsule(HWCapsuleCollider* _capsuleCol, HWCapsuleCollider* _capsuleCol2);

    /**
      * @brief       �J�v�Z���ƃX�t�B�A�̂����蔻��
      * @param[in]   HWCapsuleCollider*  �����蔻��̏d�Ȃ������Collider���1
      * @param[in]   HWSphereCollider*   �����蔻��̏d�Ȃ������Collider���2
      * @author      NZ
      * @date        24/09/17
      */
    bool CollCheck_Capsule_Sphere(HWCapsuleCollider* _capsuleCol, HWSphereCollider* _sphereCol);

#pragma endregion

#pragma region SPHERE�^�C�v�̏Փ˔���

    /**
      * @brief       �X�t�B�A�ƃ|���S���̂����蔻��
      * @param[in]   HWSphereCollider*   �����蔻��̏d�Ȃ������Collider���1
      * @param[in]   HWModelCollider*    �����蔻��̏d�Ȃ�����郂�f���n���h��
      * @author      NZ
      * @date        24/09/30
      */
    bool CollCheck_Sphere_Model(HWSphereCollider* _sphereCol, HWModelCollider* _modelCol);


    /**
      * @brief       �X�t�B�A�ƃ{�b�N�X�̂����蔻��
      * @param[in]   HWSphereCollider*   �����蔻��̏d�Ȃ������Collider���1
      * @param[in]   HWBoxCollider*      �����蔻��̏d�Ȃ������Collider���2
      * @author      NZ
      * @date        24/09/17
      */
    bool CollCheck_Sphere_Box(HWSphereCollider* _sphereCol, HWBoxCollider* _boxCol);

    /**
      * @brief       �X�t�B�A�ƃJ�v�Z���̂����蔻��
      * @param[in]   HWSphereCollider*   �����蔻��̏d�Ȃ������Collider���1
      * @param[in]   HWCapsuleCollider*  �����蔻��̏d�Ȃ������Collider���2
      * @author      NZ
      * @date        24/09/17
      */
    bool CollCheck_Sphere_Capsule(HWSphereCollider* _sphereCol, HWCapsuleCollider* _capsuleCol);

    /**
      * @brief       �X�t�B�A�ƃX�t�B�A�̂����蔻��
      * @param[in]   HWSphereCollider*   �����蔻��̏d�Ȃ������Collider���1
      * @param[in]   HWSphereCollider*   �����蔻��̏d�Ȃ������Collider���2
      * @author      NZ
      * @date        24/09/17
      */
    bool CollCheck_Sphere_Sphere(HWSphereCollider* _sphereCol, HWSphereCollider* _sphereCol2);

#pragma endregion

#pragma region MODEL�^�C�v�̏Փ˔���

    /**
      * @brief       �|���S���ƃ|���S���̂����蔻��
      * @param[in]   HWModelCollider*    �����蔻��̏d�Ȃ������Collider���1
      * @param[in]   HWModelCollider*    �����蔻��̏d�Ȃ�����郂�f���n���h��
      * @author      NZ
      * @date        24/09/30
      */
    bool CollCheck_Model_Model(HWModelCollider* _modelCol, HWModelCollider* _modelCol2);


    /**
      * @brief       �|���S���ƃ{�b�N�X�̂����蔻��
      * @param[in]   HWModelCollider*    �����蔻��̏d�Ȃ������Collider���1
      * @param[in]   HWBoxCollider*      �����蔻��̏d�Ȃ������Collider���2
      * @author      NZ
      * @date        24/09/17
      */
    bool CollCheck_Model_Box(HWModelCollider* _modelCol, HWBoxCollider* _boxCol);

    /**
      * @brief       �|���S���ƃJ�v�Z���̂����蔻��
      * @param[in]   HWModelCollider*    �����蔻��̏d�Ȃ������Collider���1
      * @param[in]   HWCapsuleCollider*  �����蔻��̏d�Ȃ������Collider���2
      * @author      NZ
      * @date        24/09/17
      */
    bool CollCheck_Model_Capsule(HWModelCollider* _modelCol, HWCapsuleCollider* _capsuleCol);

    /**
      * @brief       �|���S���ƃX�t�B�A�̂����蔻��
      * @param[in]   HWModelCollider*    �����蔻��̏d�Ȃ������Collider���1
      * @param[in]   HWSphereCollider*   �����蔻��̏d�Ȃ������Collider���2
      * @author      NZ
      * @date        24/09/17
      */
    bool CollCheck_Model_Sphere(HWModelCollider* _modelCol, HWSphereCollider* _sphereCol2);

#pragma endregion


    /**
      * @brief       �R���W����Hit���̃R�[���o�b�N�֐����Ăяo��
      * @author      NZ
      * @date        24/09/17
      */
    void ColliderHitCallBacks(std::vector<HWCollider*>::iterator colIt, HWCollider* _col1, HWCollider* _col2, bool _isTrigger);

    /**
      * @brief       �R���W�����ڐG���Ȃ��ꍇ�̏���
      * @author      NZ
      * @date        24/09/17
      */
    void ColliderAvoidCallBacks(std::vector<HWCollider*>::iterator colIt, HWCollider* _col1, HWCollider* _col2, bool _isTrigger);

    /**
      * @brief       OBB���m�̓����蔻��
      * @author      NZ
      * @date        24/09/24
      */
    int TestOBBOBB(OBB* a, OBB* b);


#pragma region MyMathf

    bool IsNearly(float lfs, float rhs)
    {
        return (fabsf(lfs - rhs) < NEARLY_THRESHOLD);
    }

    bool IsNearly(const VECTOR& lfs, const VECTOR& rhs)
    {
        return IsNearly(lfs.x, rhs.x) && IsNearly(lfs.y, rhs.y) && IsNearly(lfs.z, rhs.z);
    }

    bool IsNearlyZero(float x)
    {
        return IsNearly(x, 0.0f);
    }

    bool IsNearlyZero(const VECTOR& x)
    {
        return IsNearly(x, VGet(0.0f, 0.0f, 0.0f));
    }

#pragma endregion

};

