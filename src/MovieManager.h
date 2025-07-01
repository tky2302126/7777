/**
 * @file	MovieManager.h
 * @brief	����Đ��֌W
 * @author	NS
 * @date	2024/1/29
 */

#pragma once
#include "VideoPlayer.h"
#include "SceneBase.h"


 /**
  * @class	MovieManager
  * @brief	����Đ�
  */

class MovieManager : public HWComponent
{
	//
	// �����o�ϐ�
	//

private:

	//! ���g�̃C���X�^���X
	static MovieManager* instance;
	
	//! ���݂̃V�[��
	SceneTag crrSceneTag;

	//! Title�V�[���Ŏg�p���铮��
	std::unordered_map <std::string, std::unique_ptr<VideoPlayer>> movie_title;
	//! MainMenu�V�[���Ŏg�p���铮��
	std::unordered_map <std::string, std::unique_ptr<VideoPlayer>> movie_MainMenu;
	//! Game�V�[���Ŏg�p���铮��
	std::unordered_map <std::string, std::unique_ptr<VideoPlayer>> movie_game;


	//
	// ���\�b�h
	//

public:

	/**
	 * @brief		����������
	 */
	void Awake()override;

	/**
	 * @brief		�X�V����
	 */
	void LateUpdate()override;

	/**
	 * @brief		���g�̃C���X�^���X��Ԃ�
	 * @return		���g�̃C���X�^���X�̎Q��
	 */
	static MovieManager& Instance();

	/**
	 * @brief		����Đ�
	 * @param[in]	�L�[
	 * @param[in]	�Đ����̏ꍇ�A�Đ������Z�b�g���邩
	 */
	void Play(const std::string& _key, bool _isReset = false);
	 
	/**
	 * @brief		����Đ�
	 * @param[in]	�L�[
	 * @param[in]	�Đ����̏ꍇ�A�Đ������Z�b�g���邩
	 */
	void Play(const std::string& _key, SceneTag _tag, bool _isReset = false);
	 
	/**
	 * @brief		�Đ���~
	 * @param[in]	�L�[
	 * @param[in]	�Đ����̏ꍇ�A�Đ������Z�b�g���邩
	 */
	void Stop(const std::string& _key, bool _isReset = false);
	 
	/**
	 * @brief		�Đ���~
	 * @param[in]	�L�[
	 * @param[in]	�Đ����̏ꍇ�A�Đ������Z�b�g���邩
	 */
	void Stop(const std::string& _key, SceneTag _tag, bool _isReset = false);
	 
	/**
	 * @brief		����̃C���X�^���X��Ԃ�
	 * @param[in]	�L�[
	 * @return		����̃C���X�^���X
	 */
	std::unique_ptr<VideoPlayer>& GetMovie(const std::string& _key);
	 
	 /**
	 * @brief		����f�[�^�̓ǂݍ���
	 * @param[in]	�V�[���^�O
	 */
	void LoadMovie(SceneTag _sceneTag);

private:

	/**
	 * @brief		CSV�t�@�C������f�[�^�̓ǂݍ���
	 * @param[in]	�ǂݍ���CSV�t�@�C���̃p�X
	 * @param[out]	�ǂ݂��񂾃f�[�^�̃A�E�g�v�b�g��	
	 */
	void LoadCSV(const std::string& _path, std::unordered_map <std::string, std::unique_ptr<VideoPlayer>>& _output);
};

