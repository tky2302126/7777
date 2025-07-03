#pragma once
#include "HandlerWaltan.h"

/**
* @author   NZ
* @date     25/02/19
* @note		����Dotween�̒�`
*/

/**
 * @class	Dotween
 * @brief	����Dotween
 */
class HWDotween
{
	friend class HandlerWaltan;

	//
	// �N���X
	//

public:

	/**
	 * @class	Dotween
	 * @brief	����Dotween
	 */
	class TweenEvent
	{
		friend class HWDotween;
	private:
		//! �������̃R�[���o�b�N
		std::function<void(TweenEvent*,int)> function;
		//! �o�ߎ���
		int elapsedTime = 0;
		//! �����܂ł̃t���[��
		int duration;
		//! �A�j���[�V����������Transform
		HWTransform* transform;
		//! �A�j���[�V����������VECTOR
		VECTOR* animPtr;
		//! �A�j���[�V�����O��VECTOR
		VECTOR prev;
		//! �ڕW��VECTOR
		VECTOR target;
	public:
		// �X�e�[�^�X
		bool complete = false;
		// �L�����Z���p�̃t���O
		bool isCancel = false;

	public:
		TweenEvent() {};

		void Subscribe_Move(std::function<void(TweenEvent*, int)> _function, HWTransform* _transform, const VECTOR& _target, int _duration)
		{
			function = _function;
			duration = _duration;
			transform = _transform;
			target = _target;
			prev = _transform->position;
		}
		
		void Subscribe_Rot(std::function<void(TweenEvent*, int)> _function, HWTransform* _transform, const VECTOR& _target, int _duration)
		{
			function = _function;
			duration = _duration;
			transform = _transform;
			target = _target;
			prev = _transform->rotate;
		}

		void Subscribe_Scale(std::function<void(TweenEvent*, int)> _function, HWTransform* _transform, const VECTOR& _target, int _duration)
		{
			function = _function;
			duration = _duration;
			transform = _transform;
			target = _target;
			prev = _transform->scale;
		}

		void Subscribe_Action(std::function<void(TweenEvent*, int)> _function, VECTOR* _scalePtr, const VECTOR& _target, int _duration)
		{
			function = _function;
			duration = _duration;
			animPtr = _scalePtr;
			target = _target;
			prev = *_scalePtr;
		}

		void Subscribe_Delay(std::function<void(TweenEvent*, int)> _function, int _duration)
		{
			function = _function;
			duration = _duration;
		}

		void Execute()
		{
			function(this, elapsedTime++);
		}
	};

	/**
	 * @class	Dotween
	 * @brief	����Dotween
	 */
	class TweenCallback
	{
		friend class HWDotween;

	public:
		// �R�Â��Ă���TweenEvent
		TweenEvent* tweenEvent = nullptr;

	private:
		// �������̃R�[���o�b�N
		std::function<void()> onComplete;

	public:
		TweenCallback() {};

		void OnComplete(std::function<void()> _onComplete)
		{
			onComplete = _onComplete;
		}
	};


	//
	// �����o�ϐ�
	//

private:

	//! �o�^���ꂽDotween
	static std::unordered_map<TweenEvent*, TweenCallback*> tweens;


	//
	// ���\�b�h
	//

private:

	/**
	 * @brief		�X�V����
	 */
	static void Update();

public:

	/**
	 * @brief		�I�u�W�F�N�g���ړ�������
	 * @param[in]	�ړ�������I�u�W�F�N�g
	 * @param[in]	�ړ���̍��W
	 * @param[in]	�ړ��ɂ����鎞��(�t���[��)
	 * @return		TweenEvent�̃w���p�[�N���X
	 */
	static TweenCallback* DoMove(HWTransform* _transform, const VECTOR& _targetPos, int _duration);

	/**
	 * @brief		�I�u�W�F�N�g����]������
	 * @param[in]	��]������I�u�W�F�N�g
	 * @param[in]	��]��̍��W
	 * @param[in]	��]�ɂ����鎞��(�t���[��)
	 * @return		TweenEvent�̃w���p�[�N���X
	 */
	static TweenCallback* DoRotate(HWTransform* _transform, const VECTOR& _targetRot, int _duration);

	/**
	 * @brief		�I�u�W�F�N�g���g�k������
	 * @param[in]	�g�k������I�u�W�F�N�g
	 * @param[in]	�g�k��̍��W
	 * @param[in]	�g�k�ɂ����鎞��(�t���[��)
	 * @return		TweenEvent�̃w���p�[�N���X
	 */
	static TweenCallback* DoScale(HWTransform* _transform, const VECTOR& _targetScale, int _duration);

	/**
	 * @brief		�I�u�W�F�N�g���g�k������
	 * @param[in]	�g�k������VEVTOR�ϐ�
	 * @param[in]	�g�k��̍��W
	 * @param[in]	�g�k�ɂ����鎞��(�t���[��)
	 * @return		TweenEvent�̃w���p�[�N���X
	 */
	static TweenCallback* DoAction(VECTOR* _scalePtr, const VECTOR& _targetScale, int _duration);

	/**
	 * @brief		��莞�ԑҋ@
	 * @param[in]	�ړ��ɂ����鎞��(�t���[��)
	 * @return		TweenEvent�̃w���p�[�N���X
	 */
	static TweenCallback* DoDelay(int _duration);
};