#pragma once
#include "HandlerWaltanForDxLib.h"



/**
 * @enum	Role
 */
enum class Role
{
	//! �z�X�g(�T�[�o�[�����˂Ă�)
	server,
	//! �N���C�A���g
	Client,
};


 
 /**
 * @class	GameManager
 * @brief   �Q�[���S�̂ŎQ�Ƃ���ÓI�N���X
 */
class GameManager
{
public:

	//! ���[��
	static Role role;
};