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
 * @enum	ConnectParameter
 */
enum class ConnectParameter
{
	//! �ڑ��O
	None,
	//! �ڑ��ҋ@
	Wait,
	//! �ڑ�����
	Complete,
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