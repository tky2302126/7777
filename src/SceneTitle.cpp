#include "SceneTitle.h"

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneTitle�̎����t�@�C��
*/


SceneTitle::SceneTitle()
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
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::LoadComplete()
{
}

void SceneTitle::KeyInputCallback(InputAction::CallBackContext _c)
{
}

void SceneTitle::Update()
{
}

void SceneTitle::LateUpdate()
{
	std::string text = "�X�^�[�g";

	// �e�L�X�g�\�����W
	float posX = 1920 / 2 - (50 * (text.size() / 4));

	DrawFormatString((int)posX, 900, GetColor(0, 0, 0),
		 text.c_str());


	DrawFormatString((int)posX, 500, GetColor(0, 0, 0),
		"Title");
}



