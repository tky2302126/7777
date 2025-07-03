/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneManager�̒�`�t�@�C��
*/

#pragma once
#include "SceneTitle.h"
#include "SceneGame.h"


/**
 * @class	SceneManager
 * @brief   �V�[���̎��s�A�J�ڂ��s���N���X
 * @detail	�V���O���g���Ő݌v����Ă��邽�߁A�C���X�^���X���쐬�ł��܂���
 */
class SceneManager
{
public:

	//! �V�[�����[�h���������Ă��邩
	std::atomic<SceneLoadState> atomicLoadState;


	/**
	 * @brief       �V���O���g���C���X�^���X���擾����
	 * @detail		�C���X�^���X���������̏ꍇ�A�V���ɍ쐬����
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	static SceneManager& Instance()
	{
		static SceneManager* instance = new SceneManager();
		return *instance;
	}

	/**
	 * @brief       ���s���̃V�[���^�O���擾����
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	const SceneTag& GetCrrSceneTag()const { return crrSceneTag; }

	/**
	 * @brief       ���s���̃V�[�����擾����
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	const SceneBase& GetCrrScene()const { return *crrScene; }

	/**
	 * @brief       �����I�ɌĂяo���K�v�̂���Update����
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void Update();

	/**
	 * @brief       �����I�ɌĂяo���K�v�̂���Update����
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void LateUpdate();

	/**
	 * @brief       ���������ŃV�[����ύX����
	 * @param[in]	const SceneTag& �J�ڐ�̃V�[���^�O
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void SceneChangeSync(const SceneTag& _nextSceneTag);

	/**
	 * @brief       �񓯊������ŃV�[����ύX����
	 * @param[in]	const SceneTag& �J�ڐ�̃V�[���^�O
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void SceneChangeAsync(const SceneTag& _nextSceneTag);


private:

	//! ���s���̃V�[���^�O
	SceneTag crrSceneTag;
	//! ���s���̃V�[���̃C���X�^���X
	SceneBase* crrScene;
	//! �񓯊��ŃV�[���̓ǂݍ��݂��s���X���b�h
	std::thread sceneLoadThread;
	//! �񓯊��œǂݍ��񂾃V�[���̃C���X�^���X
	SceneBase* loadScene;
	//! ���[�h���ɍĐ����铮��̃n���h��
	int loadMovieHandle;


	/**
	 * @brief       �V�[���ǂݍ���
	 * @param[in]	const SceneTag& �J�ڐ�̃V�[���^�O
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void SceneLoad(const SceneTag& _nextSceneTag);

	// �R���X�g���N�^�͖����I�ɍ폜
	SceneManager();
};

