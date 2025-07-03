#pragma once
#include "HandlerWaltanForDxLib.h"



/**
 * @enum	Role
 */
enum class Role
{
	//! ホスト(サーバーも兼ねてる)
	server,
	//! クライアント
	Client,
};


 
 /**
 * @class	GameManager
 * @brief   ゲーム全体で参照する静的クラス
 */
class GameManager
{
public:

	//! ロール
	static Role role;
};