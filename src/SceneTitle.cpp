#include "SceneTitle.h"

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneTitle�̎����t�@�C��
*/


SceneTitle::SceneTitle()
	: selectIndex(0), isSelect(false), inputHandle(-1),portId(-1),
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

	inputHandle = MakeKeyInput(3, TRUE, FALSE, TRUE);

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
			if (--selectIndex < 0)
			{
				if (ipBuffer[3] == -1 || portId == -1)
				{
					selectIndex = 2;
				}
				else
				{
					selectIndex = 3;
				}
			}
		}

		if (it->keyCode == PAD_INPUT_DOWN)
		{
			++selectIndex;

			if ((ipBuffer[3] == -1 || portId == -1) &&
				selectIndex > 2) 
			{
				selectIndex = 0;
			}
			else if ((ipBuffer[3] != -1 && portId != -1) &&
				selectIndex > 3)
			{
				selectIndex = 0;
			}
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
		"Role       : ");
	if (GameManager::role == Role::server)
		DrawFormatString(450, 300 - GetFontSize() / 2,GetColor(0, 0, 0),"Sever");
	else
		DrawFormatString(450, 300 - GetFontSize() / 2,GetColor(0, 0, 0),"Client");


	if (GameManager::role == Role::server)
		ServerInputForm();
	if (GameManager::role == Role::Client)
		ClientInputForm();
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

	if(selectIndex == 0)
	{
		GameManager::role == Role::server ? GameManager::role = Role::Client : GameManager::role = Role::server;
		isSelect = false;
		cursor.SetColor(GetColor(100, 100, 255));
		cursor.SetTargetScale({ 100,20,0 });
		return;
	}
	else if(selectIndex == 1)
	{
		for (int i = 0; i < 4; ++i)
			ipBuffer[i] = -1;
		SetActiveKeyInput(inputHandle);
		SetKeyInputString("", inputHandle);
	}
	else if(selectIndex == 2)
	{
		SetActiveKeyInput(inputHandle);
		SetKeyInputString("", inputHandle);
	}
}

void SceneTitle::ServerInputForm()
{
}

void SceneTitle::ClientInputForm()
{
	if (selectIndex == 1)
	{
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

			for (int i = 0; i < inputIndex; ++i)
			{
				DrawFormatString(100 + GetFontSize() * 3 * i,
					250, GetColor(0, 0, 0),
					"%d.", ipBuffer[i]);
			}

			DrawKeyInputString(100 + GetFontSize() * 3 * inputIndex, 250, inputHandle);


			// IP�A�h���X�̓��͏���
			if (CheckKeyInput(inputHandle))
			{
				// ���͂��ꂽ������𐔗�ɕϊ�
				int num = GetKeyInputNumber(inputHandle);
				ipBuffer[inputIndex] = num;

				// ���͂����������ꍇ
				if (ipBuffer[3] != -1)
				{
					ipData.d1 = ipBuffer[0];
					ipData.d2 = ipBuffer[1];
					ipData.d3 = ipBuffer[2];
					ipData.d4 = ipBuffer[3];

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
	else if (selectIndex == 2)
	{
		if (isSelect)
		{
			DrawKeyInputString(100, 350, inputHandle);

			// �|�[�g�ԍ��̓��͏���
			if (CheckKeyInput(inputHandle))
			{
				// ���͂��ꂽ������𐔗�ɕϊ�
				portId = GetKeyInputNumber(inputHandle);
				SetKeyInputString("", inputHandle);

				isSelect = false;
				cursor.SetColor(GetColor(100, 100, 255));
				cursor.SetTargetScale({ 100,20,0 });
			}
		}
	}


	DrawFormatString(300, 400 - GetFontSize() / 2,
		GetColor(0, 0, 0),
		"IP�A�h���X : ");
	if (ipBuffer[3] != -1)
	{
		DrawFormatString(450, 400 - GetFontSize() / 2,
			GetColor(0, 0, 0),
			"%d.%d.%d.%d", ipData.d1, ipData.d2, ipData.d3, ipData.d4);
	}

	DrawFormatString(300, 500 - GetFontSize() / 2,
		GetColor(0, 0, 0),
		"�|�[�g�ԍ� : ");
	if (portId != -1)
	{
		DrawFormatString(450, 500 - GetFontSize() / 2,
			GetColor(0, 0, 0),
			"%d", portId);
	}

	// IP�A�h���X�ƃ|�[�g�ԍ��̓��͂��I�����Ă���ꍇ

	if (ipBuffer[3] != -1 && portId != -1)
	{
		DrawFormatString(300, 600 - GetFontSize() / 2,
			GetColor(0, 0, 0),
			"�ڑ�");
	}
}



