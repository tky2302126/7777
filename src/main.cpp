#pragma comment(lib,"Lib/MTd_Debug/MyLib_d.lib")
#pragma comment(lib,"Lib/MTd_Release/MyLib.lib")

// �����C�u�����ŕK�{�ɂȂ�C���N���[�h�t�@�C��
// "DxLib.h" ��include�����
#include "HandlerWaltanForDxLib.h"
#include"SceneManager.h"
#include <fstream>


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// DX���C�u�����̏��������������˂Ă���
	if (HandlerWaltan::Instance().Init() == -1)
	{
		return 0;
	}


#ifdef _DEBUG

	// ��: 1920, ����: 1080, �r�b�g�[�x: 32
	SetGraphMode(1920, 1080, 32);
	ChangeWindowMode(TRUE);
	// �f�o�b�O���[�h�ŋN��
	HandlerWaltan::debugMode = true;

#else

	// ��: 1920, ����: 1080, �r�b�g�[�x: 32
	SetGraphMode(1920, 1080, 32);
	// �E�C���h�E���[�h�ŋN��
	ChangeWindowMode(FALSE);
	// ��f�o�b�O���[�h�ŋN��
	HandlerWaltan::debugMode = false;

#endif // DEBUG


	SetUseZBuffer3D(TRUE);     // �f�v�X�o�b�t�@�iZ�o�b�t�@�j��L���ɂ���
	SetWriteZBuffer3D(TRUE);   // Z�o�b�t�@�ւ̏������݂�L���ɂ���

	//! �n���h���[�⃉�C�t�T�C�N���Ɋ�Â����^�C�~���O�Ń��\�b�h�������I�ɌĂяo���I�u�W�F�N�g
	//! �V���O���g���Ő݌v����Ă��邽�߁A�ȉ��̕��@�ȊO�ŃC���X�^���X���擾���邱�Ƃ͂ł��Ȃ�
	HandlerWaltan& HW = HandlerWaltan::Instance();

	UIManager::ManualInitialize();
	auto& sceneManager = SceneManager::Instance();
	sceneManager.SceneChangeSync(SceneTag::Title);

	HWDotween::DoDelay(30)->OnComplete([&] {
		sceneManager.SceneChangeAsync(SceneTag::Game);
		UIManager::FadeIn(20, 0, false);
		});

	//! �I�u�W�F�N�g�̐���(unity�ł����Ƃ����GameObject�̐���)
	HWGameObject* obj = new HWGameObject();


	VECTOR pos = VGet(200, 500, 0);
	VECTOR rot = VGet(0, 0, 0);
	VECTOR scale = VGet(1, 1, 1);

	HWDotween::TweenCallback* callback;

	callback = HWDotween::DoAction(&pos, pos + VGet(800, 0, 0), 240);
	
	HWDotween::DoDelay(60)->OnComplete([&] {
		HWDotween::DoAction(&scale, VGet(5, 5, 5), 60)->OnComplete([&] {
			HWDotween::DoAction(&scale, VGet(1, 1, 1), 60);
			//callback->tweenEvent->isCancel = true;
			});
		});

	// ���C�����[�v
	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();
		SetDrawScreen(DX_SCREEN_BACK);


		if (CheckHitKey(KEY_INPUT_ESCAPE))
			break;


		// �S�Ă�Update���\�b�h��S�ČĂяo��
		HW.Update();

		sceneManager.Update();


		DrawFormatString(0, 0, GetColor(255, 255, 255), "Escape key to exit");

		DrawCapsule3D(
			pos, pos + VGet(0,400,0), 50.0f * scale.x,
			12, 
			GetColor(255, 0, 0),GetColor(255, 0, 0), 
			FALSE);


		sceneManager.LateUpdate();
		UIManager::ManualLateUpdate();
		// �񓯊��ŃV�[����ǂݍ���ł���Œ�
		if (sceneManager.atomicLoadState.load() == SceneLoadState::Loading)
			UIManager::LoadingAnimation();


		ScreenFlip();
	}

	// �\�t�g�̏I�� 
	HandlerWaltan::End();

	return 0;
}