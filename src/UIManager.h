/**
 * @file	UIManager.h
 * @brief	UI�֌W
 * @author	NS
 * @date	2024/1/29
 */

#pragma once
#include "VideoPlayer.h"

 // �O���錾
class CharacterBase;

 /**
  * @class	UIManager
  * @brief  UI�֌W���܂Ƃ߂��N���X
  */
class UIManager : public HWComponent
{
public:
	
	/**
	 * @brief		�f�X�g���N�^
	 */
	~UIManager();

	/**
	 * @brief		����������
	 */
	void Awake()override;

	/**
	 * @brief		�t�F�[�h�C��
	 * @param[in]	�Ó]�Ɋ|���鎞��
	 * @param[in]	�Ó]���Ă��鎞��
	 */
	static void FadeIn(int _speed, int _frame, bool _autoFadeOut = true);

	/**
	 * @brief		�t�F�[�h�A�E�g
	 * @param[in]	�Ó]�Ɋ|���鎞��
	 */
	static void FadeOut(int _speed);

	/**
	 * @brief		�ÓI�I�u�W�F�N�g�̏�����
	 */
	static void ManualInitialize();

	/**
	 * @brief		�t�F�[�h�C���A�t�F�[�h�A�E�g���̏���
	 */
	static void ManualLateUpdate();

	/**
	 * @brief		���[�h���̏���
	 */
	static void LoadingAnimation();


private:

	//! �t�F�[�h�C���A�t�F�[�h�A�E�g�p�摜
	static int fadeGraphHandle;
	//! �t�F�[�h�C���A�t�F�[�h�A�E�g��
	static bool isFade;
	//! �摜�̃��l
	static int alpha;
	//! ���l�̉��Z�l
	static int add;
	static int loadingGraphHandle;
	static int 	menuFont;
};

