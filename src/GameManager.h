#pragma once
#include "HandlerWaltanForDxLib.h"
#include "define.h"



/**
 * @enum	Role
 */
enum class Role
{
	//! ホスト(サーバーも兼ねてる)
	Server,
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
 *			通信のみ管理
 */
class GameManager
{
public:

	//! ロール
	static Role role;
	//! 接続しているネットワークハンドル
	//! クライアントの場合、0番目にserverのハンドルが入る
	static int networkHandle[3];
	// 接続しているIPアドレス インゲームで使う
	// クライアントは[0]だけ使う	
	static IPDATA IPAdress[3];
	// マッチングで使用するポート番号
	// インゲームのudp通信で使用
	static int portNum;

	
	//! 接続人数
	static int connectNum;
	//! 自身のプレイヤーID
	static int playerId;
};