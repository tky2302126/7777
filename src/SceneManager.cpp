#include "SceneManager.h"

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneManager�̎����t�@�C��
*/


InputSystem* SceneBase::input = nullptr;

SceneManager::SceneManager()
{
	// �G���[�l�����Ă���
	crrSceneTag = SceneTag::NotFound;
	// ���[�h�X�e�[�^�X�̏�����
	atomicLoadState = SceneLoadState::Wait;

	crrScene = nullptr;
}


void SceneManager::Update()
{
	crrScene->Update();

	// �񓯊��̓ǂݍ��݂���������
	if (atomicLoadState.load() == SceneLoadState::Completed)
	{
		// �V�[�����㏑��
		std::swap(crrScene, loadScene);
		// �^�O���ύX
		crrSceneTag = crrScene->sceneTag;
		crrScene->nextSceneTagAsync = SceneTag::NotFound;
		//�@�ǂݍ��݃f�[�^���폜
		delete loadScene;
		// �X���b�h���J��
		sceneLoadThread.detach();
		// �ǂݍ��݃X�e�[�^�X��ύX
		atomicLoadState.store(SceneLoadState::Wait);

		// �ǂݍ��݊������̃��\�b�h�̎��s
		crrScene->LoadComplete();
	}

	// �V�[�����őJ�ڎw���������ꍇ
	if (!(crrScene->nextSceneTag == SceneTag::NotFound ||
		crrScene->nextSceneTag == crrSceneTag))
		SceneChangeSync(crrScene->nextSceneTag);

	// �V�[�����Ŕ񓯊��ōs���J�ڎw���������ꍇ
	if (!(crrScene->nextSceneTagAsync == SceneTag::NotFound ||
		crrScene->nextSceneTagAsync == crrSceneTag))
		SceneChangeAsync(crrScene->nextSceneTagAsync);
}

void SceneManager::LateUpdate()
{
	crrScene->LateUpdate();
}


void SceneManager::SceneChangeSync(const SceneTag& _nextSceneTag)
{
	// �J�ڎw���̗����^�O�����s���̃V�[���Ɠ������ANotFound�������ꍇ�͂��̂܂܏I��
	if (_nextSceneTag == crrSceneTag || _nextSceneTag == SceneTag::NotFound)
		return;

	// ! �J�ڐ�̃V�[���^�O���L�����Ă���(�Q�ƌ^�Ŏ����Ă��邽��)
	const SceneTag nextSceneTag = _nextSceneTag;

	// ���s���̃V�[�����폜
	if(crrScene != nullptr)
		delete(crrScene);

	// �^�O�ɂ���đJ�ڐ�̃V�[����ύX����
	switch (nextSceneTag)
	{

	case SceneTag::Title:
		crrScene = new SceneTitle();
		break;

	case SceneTag::Game:
		crrScene = new SceneGame();
		break;

	case SceneTag::Result:
		//crrScene = new SceneResult();
		break;

	case SceneTag::MainMenu:
		//crrScene = new SceneMainMenu();
		break;

	case SceneTag::Option:
		//crrScene = new SceneOption();
		break;

		/*
		// Scene�𑝂₷�ۂ́A������SceneBase.h�ɂ���SceneTag�ɒǉ��ŋL�q����

	case SceneTag:: :
		crrScene = new �ǉ��V�[��();
		break;
		*/
	}

	// �V�[���^�O���X�V
	crrSceneTag = nextSceneTag;

	// �ǂݍ��݊������̃��\�b�h�̎��s
	crrScene->LoadComplete();
}


void SceneManager::SceneChangeAsync(const SceneTag& _nextSceneTag)
{
	// �V�[���ǂݍ��ݒ��̏ꍇ�A�w���𖳌�
	if (sceneLoadThread.joinable() || atomicLoadState.load() != SceneLoadState::Wait) return;
	// �J�ڎw���̗����^�O�����s���̃V�[���Ɠ������ANotFound�������ꍇ�͂��̂܂܏I��
	if (_nextSceneTag == crrSceneTag || _nextSceneTag == SceneTag::NotFound) return;

	// �V�[���ǂݍ��݊J�n
	sceneLoadThread = std::thread(&SceneManager::SceneLoad, this, _nextSceneTag);
}


void SceneManager::SceneLoad(const SceneTag& _nextSceneTag)
{
	// �V�[���ǂݍ��݊����̃t���O��܂��Ă���
	atomicLoadState.store(SceneLoadState::Loading);

	//! �J�ڐ�̃V�[���^�O���L�����Ă���(�Q�ƌ^�Ŏ����Ă��邽��)
	const SceneTag nextSceneTag = _nextSceneTag;

	// �^�O�ɂ���đJ�ڐ�̃V�[����ύX����
	switch (nextSceneTag)
	{
	case SceneTag::Title:
		loadScene = new SceneTitle();
		break;

	case SceneTag::Game:
		loadScene = new SceneGame();
		break;

	case SceneTag::Result:
		//loadScene = new SceneResult();
		break;

	case SceneTag::MainMenu:
		//loadScene = new SceneMainMenu();
		break;

	case SceneTag::Option:
		//loadScene = new SceneOption();
		break;
	}

	loadScene->AsyncAwake();

	// �ǂݍ��݊���
	atomicLoadState.store(SceneLoadState::Completed);
}


