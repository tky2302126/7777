#pragma once
#include "GameManager.h"
#include "Card.h"

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


class UDPConnection
{
public:

	/**
	 * @brief		データを送信する
	 * @param[in]	SendData 送信するデータ
	 */
	static void Send(SendData&);

private:
};

