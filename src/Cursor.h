/**
* @note		Cursor�̒�`�t�@�C��
*/

#pragma once
#include "HandlerWaltanForDxLib.h"


/**
 * @class	Cursor
 * @brief   �J�[�\���Ǘ�
 */
class Cursor
{
public:

	/**
	 * @brief       �������֐�
	 */
	void ManualInitialize(const VECTOR& _pos, const VECTOR& _scale)
	{
		position = _pos;
		targetScale = scale = _scale;

		color = GetColor(100, 100, 255);
		//color = GetColor(255, 255, 255);
	}

	/**
	 * @brief       �ړ�������
	 */
	void SetTargetPosition(const VECTOR& _target)
	{
		targetPos = _target;
	}

	/**
	 * @brief       �T�C�Y�ύX
	 */
	void SetTargetScale(const VECTOR& _target)
	{
		targetScale = _target;
	}

	/**
	 * @brief       �J���[�ύX
	 */
	void SetColor(const unsigned int _color)
	{
		color = _color;
	}

	/**
	 * @brief       ��F�Ă΂�郁�\�b�h
	 */
	void ManualUpdate()
	{
		DrawBox((int)position.x - (int)scale.x, (int)position.y - (int)scale.y,
				(int)position.x + (int)scale.x, (int)position.y + (int)scale.y,
			color, TRUE);

		//DrawTriangle((int)position.x + (int)scale.x, (int)position.y - (int)scale.y,
		//			 (int)position.x + (int)scale.x, (int)position.y + (int)scale.y,
		//			 (int)position.x + (int)scale.x + 50, (int)position.y,
		//	color, TRUE);

		//DrawTriangle((int)position.x - (int)scale.x, (int)position.y - (int)scale.y,
		//			 (int)position.x - (int)scale.x, (int)position.y + (int)scale.y,
		//			 (int)position.x - (int)scale.x - 50, (int)position.y,
		//	color, TRUE);


		// �ړ�����
		VECTOR dir = (targetPos - position) * 0.3f;
		position += dir;

		// �g�k����
		dir = (targetScale - scale) * 0.3f;
		scale += dir;
	}


private:

	//! ���W
	VECTOR position;
	//! �ڕW�n�_
	VECTOR targetPos;
	//! �T�C�Y
	VECTOR scale;
	//! �ڕW�T�C�Y
	VECTOR targetScale;
	//! �J���[
	unsigned int color;
};