#include "UDPConnection.h"

void UDPConnection::SendServer(SendData& _sendData,const int& UDPSocketHandle)
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
		data[i].data = _sendData.cards[i]->suit * 13 + _sendData.cards[i]->number - 1;
		data[i].area = (int)_sendData.cards[i]->area;
		data[i].areaNumber = _sendData.cards[i]->areaNumber;
	}

	unsigned char block[250];

	unsigned char* b = block;

	std::memcpy(b, &sendTime, sizeof(int));
	b += sizeof(int);
	std::memcpy(b, &sendDataId, sizeof(int));
	b += sizeof(int);
	std::memcpy(b, data, sizeof(data));

	// 送信データのサイズを取得
	int dataSize = sizeof(int) * 2 + sizeof(data);
	
	// UDPで送信
	// クライアントのみ送信
	auto portNum = UDP_PORT_NUM;
	auto Ip = GameManager::IPAdress[0];
	int ret = NetWorkSendUDP(UDPSocketHandle, Ip, portNum, block, dataSize);

}
