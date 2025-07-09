#include "UDPConnection.h"

void UDPConnection::Send(SendData& _sendData)
{
#pragma pack(1)
	CardData data[SUIT_NUM * DECK_RANGE];
#pragma pack()

	//! 送信時刻
	int sendTime = GetNowCount();
	//! 送信データID
	static unsigned int sendDataId = 10000 * GameManager::playerId;
	sendDataId++;
	// カード情報をパッケージング
	for (int i = 0; i < SUIT_NUM * DECK_RANGE; ++i)
	{
		data[i].data = _sendData.cards[i].suit * 13 + _sendData.cards[i].number - 1;
		data->area = (int)_sendData.cards[i].area;
		data->areaNumber = _sendData.cards[i].areaNumber;
	}

	unsigned char block[250];

	unsigned char* b = block;

	std::memcpy(b, &sendTime, sizeof(int));
	b += sizeof(int);
	std::memcpy(b, &sendDataId, sizeof(int));
	b += sizeof(int);
	std::memcpy(b, data, sizeof(data));
	

	// 送信するデータは "block" のほう
}
