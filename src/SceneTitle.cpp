#include "SceneTitle.h"

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneTitle�̎����t�@�C��
*/


SceneTitle::SceneTitle()
	: selectIndex(0), isSelect(false), inputHandle(-1), 
	ipBuffer{ -1, -1, -1, -1 }
{
	// ���s���̃V�[���^�O
	sceneTag = SceneTag::Title;

	// �w�i�F��ύX
	SetBackgroundColor(255, 255, 255);

	// �L�[���͂̃R�[���o�b�N��o�^
	callBackId = input->AddCallBack("cursor", std::bind(&SceneTitle::KeyInputCallback, this, std::placeholders::_1));

	// �Ó]����
	HWDotween::DoDelay(15)->OnComplete([&]
		{
			UIManager::FadeOut(20);
			isLoad = false;
		});

	cursor.ManualInitialize({300,300,0}, {100,20,0});
	cursor.SetTargetPosition({ 300,300,0 });

	inputHandle = MakeKeyInput(3, TRUE, FALSE, FALSE);

	SetKeyInputStringColor(inputHandle, 
		GetColor(0, 0, 0), GetColor(0, 0, 0),
		GetColor(0, 0, 0), GetColor(0, 0, 0),
		GetColor(0, 0, 0), GetColor(0, 0, 0)
		); // �J���[��ݒ�
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::LoadComplete()
{
}

void SceneTitle::KeyInputCallback(InputAction::CallBackContext _c)
{
	for (auto it = _c.key.begin(); it != _c.key.end(); ++it)
	{
		if (it->inputState != InputState::Started)
			continue;

		// ����L�[�������̏���
		if (it->keyCode == KEY_INPUT_Z)
		{
			SelectInput();
		}

		if (isSelect) continue;

		// �J�[�\���ړ��ƎQ�ƍ��ڈړ��̏���
		if (it->keyCode == PAD_INPUT_UP)
		{
			if (selectIndex == 0)	selectIndex = 1;
			else if (selectIndex == 1)	selectIndex = 0;
		}

		if (it->keyCode == PAD_INPUT_DOWN)
		{
			if (selectIndex == 0)	selectIndex = 1;
			else if (selectIndex == 1)	selectIndex = 0;
		}


		cursor.SetTargetPosition({ 300.0f, (300.0f + 100.0f * (float)selectIndex), 0.0f });
	}
}

void SceneTitle::Update()
{
}

void SceneTitle::LateUpdate()
{
	cursor.ManualUpdate();

	std::string text = "�X�^�[�g";

	// �e�L�X�g�\�����W
	float posX = 1920 / 2 - (50 * (text.size() / 4));

	DrawFormatString((int)posX, 900, GetColor(0, 0, 0),
		 text.c_str());


	DrawFormatString((int)posX, 500, GetColor(0, 0, 0),
		"Title");


	DrawFormatString(300, 300 - GetFontSize() / 2, 
		GetColor(0, 0, 0),
		"����1");

	DrawFormatString(300, 400 - GetFontSize() / 2,
		GetColor(0, 0, 0),
		"����2");


	if (isSelect)
	{
		// ���͒��̃O���[�v��ݒ�
		int inputIndex = 0;
		for (int i = 0; i < 4; ++i)
		{
			if (ipBuffer[i] != -1) continue;
			inputIndex = i;
			break;
		}

		for(int i = 0; i < inputIndex; ++i)
		{			
			DrawFormatString(100 + GetFontSize() * 3 * i,
				100, GetColor(0, 0, 0), 
				"%d.", ipBuffer[i]);
		}

		DrawKeyInputString(100 + GetFontSize() * 3 * inputIndex, 100, inputHandle);

		if (CheckKeyInput(inputHandle))
		{
			// ���͂��ꂽ������𐔗�ɕϊ�
			int num = GetKeyInputNumber(inputHandle);
			ipBuffer[inputIndex] = num;

			// ���͂����������ꍇ
			if (ipBuffer[3] != -1)
			{
				IPDATA ip;
				ip.d1 = ipBuffer[0];
				ip.d2 = ipBuffer[1];
				ip.d3 = ipBuffer[2];
				ip.d4 = ipBuffer[3];

				isSelect = false;
				cursor.SetColor(GetColor(100, 100, 255));
				cursor.SetTargetScale({ 100,20,0 });
			}
			else
			{
				SetActiveKeyInput(inputHandle);
				SetKeyInputString("", inputHandle);
			}
		}
	}
}

void SceneTitle::SelectInput()
{
	if (isSelect)
	{
		isSelect = false;
		cursor.SetColor(GetColor(100, 100, 255));
		cursor.SetTargetScale({ 100,20,0 });
		return;
	}

	isSelect = true;
	cursor.SetColor(GetColor(100, 100, 100));
	cursor.SetTargetScale({ 150,15,0 });

	SetActiveKeyInput(inputHandle);
	SetKeyInputString("", inputHandle);
}

void SceneTitle::ServerInit()
{
	int portNum = 7777;
	PreparationListenNetWork(portNum);
	for(auto N: NetWorkHandles)
	{
		N = -1;
	}
	
}

void SceneTitle::ServerUpdate()
{
	int ConnectedNum = 0;
	for(int NetHandle : NetWorkHandles)
	{
		if (NetHandle > 0) ConnectedNum++;
	}

	// �ڑ�
	if(ConnectedNum >=3)
	{
		StopListenNetWork();
	}
	else
	{
		Connect();
	}

	// ��M
	if(ConnectedNum >0)
	{
		DisConnect();
		RecieveNetData();
	}
}

void SceneTitle::Connect()
{
	int portNum = 7777;
	PreparationListenNetWork(portNum);
	for(int NetHandle : NetWorkHandles)
	{
		if (NetHandle != -1) continue;
		NetHandle = GetNewAcceptNetWork();
	}
}

void SceneTitle::DisConnect()
{
	int LostHandle = 0;
	LostHandle = GetLostNetWork();

	for(auto NetHandle: NetWorkHandles)
	{
		if(NetHandle == LostHandle)
		{
			NetHandle = -1;
		}
	}


}

void SceneTitle::RecieveNetData()
{
	for(auto NetHandle : NetWorkHandles)
	{
		if (NetHandle == -1) continue; // NetHandle ���o�^����Ă��Ȃ��Ƃ��A�X�L�b�v
		IPDATA Ip;            // �ڑ���h�o�A�h���X�f�[�^
		// �ڑ����Ă����}�V���̂h�o�A�h���X�𓾂�
		GetNetWorkIP(NetHandle, &Ip);
	
		// �擾���Ă��Ȃ���M�f�[�^�ʂ��O�̂Ƃ��͏I��
		if (GetNetWorkDataLength(NetHandle) == 0) continue;

		int DataLength;
		char StrBuf[256];

		// �f�[�^��M
		DataLength = GetNetWorkDataLength(NetHandle);    // �f�[�^�̗ʂ��擾
		NetWorkRecv(NetHandle, StrBuf, DataLength);    // �f�[�^���o�b�t�@�Ɏ擾
		// �o�b�t�@���X�^�b�N�ɒǉ�
		recvStack.push(StrBuf);
	}

}



