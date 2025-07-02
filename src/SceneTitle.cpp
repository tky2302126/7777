#include "SceneTitle.h"

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneTitle�̎����t�@�C��
*/


SceneTitle::SceneTitle()
	: selectIndex(0), isSelect(false)
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
		if (it->keyCode == KEY_INPUT_RETURN)
		{
			SelectInput();
		}

		if (isSelect) continue;

		// �J�[�\���ړ��ƎQ�ƍ��ڈړ��̏���
		if (it->keyCode == KEY_INPUT_W)
		{
			if (selectIndex == 0)	selectIndex = 1;
			else if (selectIndex == 1)	selectIndex = 0;
		}

		if (it->keyCode == KEY_INPUT_S)
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
}



