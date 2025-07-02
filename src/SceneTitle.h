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
#include <stack>


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
	//! �T�[�o�[�Ŏg���N���C�A���g�̃l�b�g���[�N�n���h��
	int NetWorkHandles[3];
	//! �T�[�o�[�Ŏg����M�f�[�^
	std::stack<char[256]> recvStack;
	

	/**
	 * @brief       ����L�[���������ۂ̏���
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void SelectInput();

	/**
	* @brief		�T�[�o�[���̃C�j�V�����C�Y
	* @author		Suzuki h
	* @date			25/7/2
	*/
	void ServerInit();

	/**
	* @brief		�T�[�o�[���̏���
	* @author		Suzuki h
	* @date			25/7/2
	*/
	void ServerUpdate();

	/**
	* @brief		�ڑ��ҋ@����
	* @author		Suzuki h
	* @date			25/7/2
	*/
	void Connect();

	/**
	* @brief		�ؒf����
	* @author		Suzuki h
	* @date			25/7/2
	*/
	void DisConnect();

	/**
	* @brief		��M�ҋ@����
	* @author		Suzuki h
	* @date			25/7/2
	*/
	void RecieveNetData();

};