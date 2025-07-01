/**
* @author   Suzuki N
* @date     24/2/25
* @note		VideoPlayer�̒�`�t�@�C��
*/

#pragma once
#include "HandlerWaltanForDxLib.h"


/**
 * @enum	PlayStatus
 * @brief   ����̍Đ���
 */
enum class PlayStatus
{
	//! �ҋ@��
	Wait,
	//! �Đ���
	Play,
	//! �Đ���~
	Stop,
};


/**
 * @class	VideoPlayer
 * @brief   ����Đ��p�N���X
 */
class VideoPlayer
{
	//
	// �����o�ϐ�
	//

private:

	//! ���ߏ������s���ۂɎg�p����X�N���[���n���h��
	int screenHandle = -1;

public:

	//! ����̃n���h��
	int movieHandle;
	//! �Đ����@
	int playType = DX_PLAYTYPE_BACK;
	//! ���ߏ������s����(�O���[���o�b�N)
	bool isTrans = true;
	//! �Đ���
	PlayStatus playStatus;
	//! ����̉���
	int wedth;
	//! ����̗���
	int height;
	//! �\�����W
	VECTOR position;


	//
	// ���\�b�h
	//

public:

	/**
	 * @brief       �R���X�g���N�^
	 * @param[in]	�t�@�C���̃p�X
	 * @param[in]	�Đ����@
	 * @param[in]	���ߏ������s����
	 */
	VideoPlayer(const std::string& _path, int _playType = DX_PLAYTYPE_BACK, bool _isTrans = true)
		: movieHandle(LoadGraph(_path.c_str())), playType(_playType), isTrans(_isTrans), playStatus(PlayStatus::Wait),
		position({ 0,0,0 })
	{
		// ���f�����[�h���s���̗�Oerror
		if (movieHandle == -1)
			throw std::runtime_error("Failed to load movie: " + _path);

		// ����T�C�Y���L�^
		GetGraphSize(movieHandle, &wedth, &height);

		if (!isTrans) return;

		//
		// ���ߏ������s���ꍇ�̏���
		//

		// ����Ɠ��T�C�Y�̃A���t�@�`�����l���t���̉摜���쐬
		screenHandle = MakeScreen(wedth, height, TRUE);
	}

	/**
	 * @brief       �����I�ȍX�V����
	 */
	void ManualUpdate()
	{
		// �Đ��󋵂̍X�V
		if (playStatus == PlayStatus::Stop) playStatus = PlayStatus::Wait;
		if (playStatus != PlayStatus::Play) return;

		//
		// ���ߏ������s��Ȃ��ꍇ
		//

		if (!isTrans)
		{
			DrawGraph((int)position.x, (int)position.y, movieHandle, TRUE);
		}
		else
		{
			// Screen �� Movie ��RGBA�̊e�`�����l����u���������蔽�]�����肵�ē]��
			GraphBlendBlt(movieHandle, movieHandle, screenHandle, 255, DX_GRAPH_BLEND_RGBA_SELECT_MIX,
				DX_RGBA_SELECT_SRC_R,
				DX_RGBA_SELECT_SRC_G,
				DX_RGBA_SELECT_SRC_B,
				DX_RGBA_SELECT_SRC_INV_G	// Screen �̓����x������ Movie �̗ΐ����𔽓]�������̂�]��
			);

			// Screen �̓��e����ʂɕ`��
			DrawGraph((int)position.x, (int)position.y, screenHandle, TRUE);
		}

		//
		// �Đ��󋵂��X�V
		//

		if (GetMovieStateToGraph(movieHandle) == 0)
			playStatus = PlayStatus::Stop;
	}

	/**
	 * @brief       �Đ�
	 * @param[in]	�Đ��󋵂����Z�b�g���邩
	 */
	void Play(bool _isReset = false)
	{
		if (!_isReset && playStatus == PlayStatus::Play) return;

		SeekMovieToGraph(movieHandle, 0);
		PlayMovieToGraph(movieHandle, playType);
		playStatus = PlayStatus::Play;
	}

	/**
	 * @brief       ��~
	 * @param[in]	�Đ��󋵂����Z�b�g���邩
	 */
	void Stop(bool _isReset = false)
	{
		PauseMovieToGraph(movieHandle, playType);
		if(_isReset)
			SeekMovieToGraph(movieHandle, 0);
		playStatus = PlayStatus::Stop;
	}
};