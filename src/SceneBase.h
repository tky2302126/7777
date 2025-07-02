/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneBase�̒�`�t�@�C��
*/

#pragma once
#include "HandlerWaltanForDxLib.h"

/**
 * @enum	SceneTag
 * @brief   �V�[���̃^�O
 */
enum class SceneTag
{
	//! �^�C�g���V�[��(0)
	Title,
	//! �Q�[���V�[��(1)
	Game,
	//! ���U���g�V�[��(2)
	Result,
	//! ���C�����j���[
	MainMenu,
	//! �I�v�V����
	Option,

	/*
		�ǉ�����ꍇ�́A�����Ƀ^�O��ǉ����ASceneManager��SceneChange���\�b�h�ɒǋL����
	*/

	//! ���g�p (��ɖ���)
	NotFound = -1,
};


/**
 * @enum	SceneLoadState
 * @brief   �V�[�����[�h�̃X�e�[�^�X
 */
enum class SceneLoadState
{
	//! �ҋ@��(0)
	Wait,
	//! ���[�h��(1)
	Loading,
	//! ���[�h����(2)
	Completed,
};


/**
 * @class	SceneBase
 * @brief   �e�V�[���̂��ƂɂȂ���N���X
 * @detail	���z�N���X�̂��߁A�C���X�^���X���쐬�ł��Ȃ�
 */
class SceneBase
{
	friend class SceneManager;


public:

	/**
	 * @brief       �ŏ���Uodate�̒��O�ɓ������\�b�h
	 */
	virtual void LoadComplete() {};

	/**
	 * @brief       �񓯊����[�h�̒��ŌĂ΂�鏈��
	 */
	virtual void AsyncAwake() {};

	/**
	 * @brief       �f�X�g���N�^
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	virtual ~SceneBase() {};

	/**
	 * @brief       ��F�Ă΂�郁�\�b�h
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	virtual void Update() {};

	/**
	 * @brief       �D��x�̒Ⴂ�A��F�Ă΂�郁�\�b�h
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	virtual void LateUpdate() {};


protected:

	//! �V�[���̃^�O
	SceneTag sceneTag;
	//! �J�ڐ�̃V�[���^�O
	SceneTag nextSceneTag;
	//! �񓯊��œǂݍ��ޑJ�ڐ�̃V�[���^�O
	SceneTag nextSceneTagAsync;
	//! �V�[���J�ڂ̃R�[���o�b�N�֐���ID
	int callBackId;
	//! �S�V�[�����ʂ̑���n
	static InputSystem* input;
	//! ���[�h��
	bool isLoad = true;


	/**
	 * @brief       �R���X�g���N�^
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	SceneBase() : nextSceneTag(SceneTag::NotFound), nextSceneTagAsync(SceneTag::NotFound)
	{
		//
		// ����n�̏����ݒ�
		//

		if (input != nullptr)
			return;

		input = new InputSystem();
		input->AddKeyCode("cursor", { PAD_INPUT_DOWN,PAD_INPUT_UP,PAD_INPUT_2 }, InputType::Key_Pad1);
		input->AddKeyCode("cursor", { KEY_INPUT_W,KEY_INPUT_S,KEY_INPUT_RETURN }, InputType::Key);
	}

	/**
	 * @brief       �L�[���͎��̃R�[���o�b�N
	 * @param[in]	�R�[���o�b�N�R���e�L�X�g
	 */
	virtual void KeyInputCallback(InputAction::CallBackContext _c) = 0;

	/**
	 * @brief       �V�[��������V�[����ύX����
	 * @param[in]	const SceneTag �ύX��̃V�[���^�O
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void SceneChangeSync(const SceneTag _nextSceneTag)
	{
		nextSceneTag = _nextSceneTag;
	}
	/**
	 * @brief       �񓯊��ŃV�[��������V�[����ύX����
	 * @param[in]	const SceneTag �ύX��̃V�[���^�O
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void SceneChangeAsync(const SceneTag _nextSceneTag)
	{
		nextSceneTagAsync = _nextSceneTag;
	}
};
