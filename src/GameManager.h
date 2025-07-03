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
 * @enum	ConnectParameter
 */
enum class ConnectParameter
{
	//! 接続前
	None,
	//! 接続待機
	Wait,
	//! 接続完了
	Complete,
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