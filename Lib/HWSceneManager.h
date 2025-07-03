#pragma once
#include "HWSceneBase.h"
#include <unordered_map>
#include <string>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>


enum class LoadParameter
{
	// �ҋ@��
	None,
	// �ǂݍ��ݒ�
	Loading,
	// �ǂݍ��݊���
	complete,
};


class HWSceneManager
{
	// �����o�ϐ�

private:

	//! ���s���̃V�[��
	static HWSceneBase* crrScene;
	//! �񓯊��œǂݍ��񂾃V�[���̃C���X�^���X
	static HWSceneBase* loadScene;
	//! �V�[�����[�h�p�̃X���b�h
	static std::thread loadThread;

public:

	//! �V�[�����[�h�̃p�����[�^
	static std::atomic<LoadParameter> loadParam;
	//! ���[�h���̃X���b�h�Z�[�t�ϐ�
	static std::mutex loadMutex;


	// ���\�b�h

private:

	/**
	 * @brief		�o�^����Ă���V�[���I�u�W�F�N�g���擾����
	 * @return		�o�^����Ă���V�[���I�u�W�F�N�g
	 */
	static std::unordered_map <std::string, std::function<HWSceneBase*()>>& GetRegistry();

public:

	/**
	 * @brief		�V�[���I�u�W�F�N�g��o�^����
	 * @detail		�}�N���ɂ���ēo�^����邽�߁A�蓮�ŌĂԕK�v�͂Ȃ�
	 * @param[in]	�V�[���� : �V�[�����C���X�^���X������R�[���o�b�N�֐�
	 */
	static void RegisterScene(const std::string& name, std::function<HWSceneBase*()> factory);

	/**
	 * @brief		�X�V����
	 */
	static void Update();

	/**
	 * @brief		�V�[����ύX����(�����ǂݍ���)
	 * @param[in]	�J�ڐ�̃V�[����
	 * @return		�J�ڌ�̃V�[���I�u�W�F�N�g�̃C���X�^���X
	 */
	static HWSceneBase* SceneChangeSync(const std::string& name);

	/**
	 * @brief		�V�[����ύX����(�񓯊��ǂݍ���)
	 * @param[in]	�J�ڐ�̃V�[����
	 */
	static void SceneChangeAsync(const std::string& name);
};