#pragma once
#include "CollisionWaltan.h"
#include "HWAnimator.h"
#include "HWBoxCollider.h"
#include "HWCamera.h"
#include "HWEffect.h"
#include "HWCapsuleCollider.h"
#include "HWSphereCollider.h"
#include "HWGameObject.h"
#include "HWRenderer.h"
#include "HWTransform.h"
#include "InputSystem.h"
#include "HWDoTween.h"
#include "HWSceneManager.h"

/**
* @author   NZ
* @date     24/07/18
* @note		�����A�n���h���[�͂��ׂ�HandlerWaltan�ŌĂяo��
*/


/**
 * @class	HandlerWaltan
 * @brief   ���ׂẴn���h���[���Ǘ��A���s����N���X
 */
class HandlerWaltan
{
public:

    /*     �����o�ϐ�     */

    /**
     * @brief		�f�o�b�O���[�h�Ŏ��s���邩
     * @History		24/08/23 �쐬(NZ)
     */
    static bool debugMode;

private:


private:

    /*     ���\�b�h     */

    /**
     * @brief       �R���X�g���N�^
     * @author      NZ
     * @date        24/07/19
     */
    HandlerWaltan();

    /**
     * @brief       �f�X�g���N�^
     * @author      NZ
     * @date        24/07/19
     */
    ~HandlerWaltan();


public:

    /**
      * @brief       �S�Ă�Update���\�b�h��S�ČĂяo��
      * @author      NZ
      * @date        24/08/22
      */
    void Update();

    /**
     * @brief       �C���X�^���X���擾����ÓI���\�b�h
     * @detail      ���߂̈�񂾂��C���X�^���X�𐶐�����
     * @author      NZ
     * @date        24/07/19
     */
    static HandlerWaltan& Instance();


    //�C���X�^���X�̃R�s�[�֎~
    //�f�t�H���g�̃R�s�[�R���X�g���N�^���폜
    HandlerWaltan(const HandlerWaltan&) = delete;
    //�f�t�H���g�̃R�s�[������Z�q���폜
    HandlerWaltan& operator=(const HandlerWaltan&) = delete;


    /**
     * @brief       �C�j�V�����C�Y�p�̃��\�b�h
     * @detail      �C���X�^���X�𐶐������Ƃ��ɌĂ�
     * @return      int �����������̐���
     * @author      NZ
     * @date        24/07/29
     */
    static int Init(int _particle = 8000);

    /**
     * @brief       �I�����p�̃��\�b�h
     * @author      NZ
     * @date        24/07/29
     */
    static void End();
};
