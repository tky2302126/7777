/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneTitle�̒�`�t�@�C��
*/

#pragma once
#include "SceneBase.h"
#include "MovieManager.h"
#include "UIManager.h"
#include "Cursor.h"


/**
 * @class	SceneTitle
 * @brief   �^�C�g���V�[��
 */
class SceneTitle : public SceneBase
{
public:

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


private:

	//! �J�[�\��
	Cursor cursor;
	//! �I������
	int selectIndex;
	//! ���ڂ�I��
	bool isSelect;
	//! ���̓n���h��(ip/�|�[�g�ԍ�)
	int inputHandle;
	//! �����͂̍��ڂ𔻕ʂ��邽�߂ɁA��xint���o�R���Ă���IPDATA�^�ɕϊ�����
	int ipBuffer[4];


	/**
	 * @brief       ����L�[���������ۂ̏���
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void SelectInput();
};