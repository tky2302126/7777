﻿#include "UDPConnection.h"

int UDPConnection::sendCount = -1;

void UDPConnection::SendServer(Card& _card, int _score, const int& UDPSocketHandle)
{
#pragma pack(1)
	CardData data;
#pragma pack()

	//! 送信時刻
	int sendTime = GetNowCount();
	//! 送信データID
	static unsigned int sendDataId = 10000 * GameManager::playerId;
	sendDataId++;
	data.data = _card.suit * 13 + _card.number - 1;
	data.area = (int)_card.area;
	data.areaNumber = _card.areaNumber;

	unsigned char block[15];

	unsigned char* b = block;

	std::memcpy(b, &sendTime, sizeof(int));
	b += sizeof(int);
	std::memcpy(b, &sendDataId, sizeof(int));
	b += sizeof(int);
	std::memcpy(b, &_score, sizeof(int));
	b += sizeof(int);
	std::memcpy(b, &data, sizeof(data));

	// UDPで送信
	// クライアントのみ送信
	auto portNum = GameManager::portNum;
	auto Ip = GameManager::IPAdress[0];
	int ret = NetWorkSendUDP(UDPSocketHandle, Ip, portNum, block, 15);

	static std::ofstream outputfile("client_2.txt");
	outputfile << "送信 -> \n";
	outputfile << ret << "\n";
	outputfile << "score = " << _score << "\n";
}

void UDPConnection::SendClients(SendData& _sendData, int* UDPSocketHandle)
{
#pragma pack(1)
	CardData data[SUIT_NUM * DECK_RANGE];
#pragma pack()

	//! 送信データの種別
	SendDataType sendType = SendDataType::GameData;
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

	std::memcpy(b, &sendType, sizeof(SendDataType));
	b += sizeof(SendDataType);

	std::memcpy(b, &sendTime, sizeof(int));
	b += sizeof(int);
	std::memcpy(b, &sendDataId, sizeof(int));
	b += sizeof(int);

	std::memcpy(b, &GameManager::score[0], sizeof(int));
	b += sizeof(int);
	std::memcpy(b, &GameManager::score[1], sizeof(int));
	b += sizeof(int);
	std::memcpy(b, &GameManager::score[2], sizeof(int));
	b += sizeof(int);
	std::memcpy(b, &GameManager::score[3], sizeof(int));
	b += sizeof(int);

	std::memcpy(b, data, sizeof(data));


	static std::ofstream outputfile("sever_2.txt");
	outputfile << "送信 -> \n";

	for(int i  = 0; i < MAX_PLAYER - 1; ++i)
	{
		auto portNum = UDP_PORT_NUM - (i + 1);
		auto Ip = GameManager::IPAdress[i];
		int ret = NetWorkSendUDP(UDPSocketHandle[i], Ip, portNum, block, 250);

		outputfile << ret;
		outputfile << "\n";
		outputfile << " 送信先: " << (int)Ip.d1 << "." << (int)Ip.d2 << "."
			<< (int)Ip.d3 << "." << (int)Ip.d4 << ":" << portNum;
		outputfile << "\n";
		outputfile << "score" << GameManager::score[0] << " : " << 
			GameManager::score[1] << " : " << GameManager::score[2] << "\n";
		outputfile  << "SOCKET -> " << UDPSocketHandle[i] << "\n";
		outputfile << sizeof(block) << "\n\n";
	}
}

void UDPConnection::SendSyncData()
{
	static int sendTime = GetNowCount();
	static int ret = -9999;

	if ((GetNowCount() - sendTime) > 1000)
	{
		sendCount++;
		sendTime = GetNowCount();

		for (int i = 0; i < MAX_PLAYER - 1; ++i)
		{
			ret = NetWorkSendUDP(GameManager::syncUDPSocketHandle[i],
				GameManager::IPAdress[0], SYNC_UDP_PORT_NUM, &sendCount, sizeof(int));
		}
	}
	DrawFormatString(10, 20, GetColor(0, 255, 0), "sendCount : %d",sendCount);
}

void UDPConnection::RecvSyncData()
{
	int portNum = SYNC_UDP_PORT_NUM;
	IPDATA ip = GameManager::IPAdress[0];

	if(sendCount != -1)
		DrawFormatString(10, 20, GetColor(0, 255, 0), "SendCount : %d", sendCount);

	if (CheckNetWorkRecvUDP(GameManager::syncUDPSocketHandle[0]) == TRUE)
	{
		int buff;
		NetWorkRecvUDP(GameManager::syncUDPSocketHandle[0],
			&ip, &portNum, &buff, sizeof(int), FALSE);
		sendCount = buff;
	}
}

void UDPConnection::SendEventData(EventData& data, int* UDPSocketHandle)
{
	// 送信する情報
	//  SendDataType : 送信データの種別
	//  EventType    : イベントの種類
	//  data         : イベントごとで使うデータ

	SendDataType sendType = SendDataType::EventData;

	unsigned char block[3];

	unsigned char* b = block;

	std::memcpy(b, &sendType, sizeof(SendDataType));
	b += sizeof(SendDataType);
	std::memcpy(b, &data, sizeof(EventData));


	std::ofstream outputfile("sever_Event.txt");
	outputfile << "送信 -> \n";
	outputfile << (int)data.eventType << "\n";
	outputfile << (int)data.data << "\n\n";

	for (int i = 0; i < MAX_PLAYER - 1; ++i)
	{
		auto portNum = UDP_PORT_NUM - (i + 1);
		auto Ip = GameManager::IPAdress[i];
		int ret = NetWorkSendUDP(UDPSocketHandle[i], Ip, portNum, block, 3);

		outputfile << ret;
		outputfile << "\n";
		outputfile << " 送信先: " << (int)Ip.d1 << "." << (int)Ip.d2 << "."
			<< (int)Ip.d3 << "." << (int)Ip.d4 << ":" << portNum;
		outputfile << "\n";
	}
}

