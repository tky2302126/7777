#pragma once
#include "GameManager.h"
#include "Card.h"
# include<iostream>
# include<fstream>

/**
 * @struct	SendData
 * @brief  送受信するデータをパッケージングしたデータ群
 */
struct SendData                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
{
	//! スコア
	int score;
	//! カード情報(先頭アドレス)
	std::shared_ptr<Card>* cards;
};


#pragma pack(1)
/**
 * @class	CardData
 * @brief  データ送信用
 */
struct CardData
{
	unsigned char data;
	unsigned char area;
	unsigned char areaNumber;
};
#pragma pack()

/// <summary>
/// EventData
/// イベントデータ送信用の構造体
/// event type : 実行するイベントタイプ
/// data	   : イベントごとに使うデータ
/// </summary>
struct EventData
{
	unsigned char eventType;
	unsigned char data;
};

class UDPConnection
{
public:

	/**
	 * @brief		クライアントがサーバーにデータを送信する
	 * @param[in]	SendData 送信するデータ
	 */
	static void SendServer(Card&, const int&);

	/**
	 * @brief		サーバーがクライアントにデータを送信する
	 * @param[in]	SendData 送信するデータ
	 */
	static void SendClients(SendData&, int*);

	/// <summary>
	/// イベントデータをサーバーがクライアントに送信する
	/// </summary>
	/// <param name="">EventData 送信するデータ</param>
	static void SendEventData(EventData&);

private:
};

