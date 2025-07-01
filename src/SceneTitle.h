/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneTitle�̒�`�t�@�C��
*/

#pragma once
#include "SceneBase.h"
#include "MovieManager.h"
#include "UIManager.h"


/**
 * @class	SceneTitle
 * @brief   �^�C�g���V�[��
 */
class SceneTitle : public SceneBase
{
private:
	// �����o�ϐ�

	//! �e�L�X�g�̃t�H���g
	int menuFont;


public:
	// ���\�b�h

	/**
	 * @brief       �R���X�g���N�^
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	SceneTitle();

	/**
	 * @brief       �f�X�g���N�^
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	~SceneTitle() override;

	/**
	 * @brief       ���[�h�������̊֐�
	 */
	void LoadComplete() override;

	/**
	 * @brief       �L�[���͎��̃R�[���o�b�N
	 * @param[in]	�R�[���o�b�N�R���e�L�X�g
	 */
	void KeyInputCallback(InputAction::CallBackContext _c)override;

	/**
	 * @brief       ��F�Ă΂�郁�\�b�h
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void Update() override;

	/**
	 * @brief       ��F�Ă΂�郁�\�b�h
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void LateUpdate() override;
};