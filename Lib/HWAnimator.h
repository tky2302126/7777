#pragma once
#include "HWComponent.h"
#include "HWGameObject.h"
#include "HWRenderer.h"


/**
* @author   NZ
* @date     24/08/09
* @note		�A�j���[�V��������R���|�[�l���g�̒�`
*/


/**
 * @class	AnimInfo
 * @brief	�A�j���[�V�������
 */
class AnimInfo
{
	friend class HWAnimator;

public:

	/*     �����o�ϐ�     */

	/**
	 * @brief		�A�j���[�V�������A�^�b�`���郂�f��
	 * @History		24/09/24 �쐬(NZ)
	 */
	int modelHandle;

	/**
	 * @brief		�A�j���[�V�����̃n���h��
	 * @History		24/09/24 �쐬(NZ)
	 */
	int animHandle;

	/**
	 * @brief		animModel�̓o�^�����A�j���[�V�����̃C���f�b�N�X
	 * @History		24/09/24 �쐬(NZ)
	 */
	int animIndex;

	/**
	 * @brief		Model�ɃA�^�b�`�������̃C���f�b�N�X
	 * @History		24/09/24 �쐬(NZ)
	 */
	int attachIndex;

	/**
	 * @brief		�A�j���[�V�����t�@�C��
	 * @History		24/09/24 �쐬(NZ)
	 */
	std::string filePath;

	/**
	 * @brief		���[�v���邩
	 * @History		24/09/24 �쐬(NZ)
	 */
	bool isLoop;

	/**
	 * @brief		���f�\��
	 * @History		24/09/24 �쐬(NZ)
	 */
	bool interruption;

	/**
	 * @brief		�Đ����x
	 * @History		24/09/24 �쐬(NZ)
	 */
	double playSpeed;

	/**
	 * @brief		���Đ�����
	 * @History		24/09/24 �쐬(NZ)
	 */
	double totalTime;

private:

	/**
	 * @brief		����̍Đ����ԂɒB�����Ƃ��ɌĂ΂��R�[���o�b�N�֐�
	 * @History		24/10/12 �쐬(NZ)
	 */
	std::unordered_map<double, std::function<void()>> callbacks;

	/**
	 * @brief		�Đ��J�n���ɌĂ΂��R�[���o�b�N�֐�
	 * @History		24/10/12 �쐬(NZ)
	 */
	std::function<void()> startPlaybackCallback;

	/**
	 * @brief		�Đ��I�����ɌĂ΂��R�[���o�b�N�֐�
	 * @History		24/10/12 �쐬(NZ)
	 */
	std::function<void()> endPlaybackCallback;


public:
	/*     ���\�b�h     */

	/**
	 * @brief		�R���X�g���N�^
	 * @author		NZ
	 * @date		24/09/24
	 */
	AnimInfo() : modelHandle(-1), animHandle(-1), animIndex(-1), attachIndex(-1),
		filePath(""), isLoop(false), interruption(true), playSpeed(-1.f), totalTime(-1.f)
	{}

	/**
	 * @brief		����̍Đ����ԂɂȂ����Ƃ��ɌĂ΂��R�[���o�b�N��o�^����
	 * @param[in]	float �R�[���o�b�N�֐����Ăяo�������Đ�����
	 * @param[in]	std::function<void()> �o�^����R�[���o�b�N�֐�
	 * @author		NZ
	 * @date		24/10/12
	 */
	void AddCallBack(double _callTime, std::function<void()> _callback)
	{
		callbacks[_callTime] = _callback;
	}

	/**
	 * @brief		����̍Đ����ԂɂȂ����Ƃ��ɌĂ΂��R�[���o�b�N��o�^����
	 * @param[in]	float �R�[���o�b�N�֐����Ăяo�������Đ�����
	 * @param[in]	std::function<void()> �o�^����R�[���o�b�N�֐�
	 * @author		NZ
	 * @date		24/10/12
	 */
	void SubscribeStartPlaybackCallBack(std::function<void()> _callback)
	{
		startPlaybackCallback = _callback;
	}

	/**
	 * @brief		����̍Đ����ԂɂȂ����Ƃ��ɌĂ΂��R�[���o�b�N��o�^����
	 * @param[in]	float �R�[���o�b�N�֐����Ăяo�������Đ�����
	 * @param[in]	std::function<void()> �o�^����R�[���o�b�N�֐�
	 * @author		NZ
	 * @date		24/10/12
	 */
	void SubscribeEndPlaybackCallBack(std::function<void()> _callback)
	{
		endPlaybackCallback = _callback;
	}

	/**
	 * @brief		�o�^����Ă���R�[���o�b�N�֐����擾����
	 * @return		std::unordered_map<float, std::function<void()>>& 
	 * @author		NZ
	 * @date		24/10/12
	 */
	std::unordered_map<double, std::function<void()>>& GetCallBack()
	{
		return callbacks;
	}

};


/**
 * @class	HWAnimator
 * @brief	�A�j���[�V��������Ǘ��p�̃R���|�[�l���g
 */
class HWAnimator : public HWComponent
{
	// ����̃N���X�ȊO����̃A�N�Z�X��h�����߂̃t�����h�錾
	friend class HWGameObject;

private:

	/*     �����o�ϐ�     */

	/**
	 * @brief		�e�A�j���[�V�������
	 * @History		24/09/24 �쐬(NZ)
	 */
	std::vector<std::unique_ptr<AnimInfo>> animInfoVec;

	/**
	 * @brief		���f���n���h��
	 * @History		24/09/25 �쐬(NZ)
	 */
	int modelHandle;

	/**
	 * @brief		�Đ����̃A�j���[�V����1�C���f�b�N�X
	 * @History		24/09/24 �쐬(NZ)
	 */
	int playIndex1;

	/**
	 * @brief		�Đ����̃A�j���[�V����2�C���f�b�N�X
	 * @History		24/09/25 �쐬(NZ)
	 */
	int playIndex2;

	/**
	 * @brief		playAnimId1 �� playAnimId2 �̃u�����h��
	 * @History		24/09/25 �쐬(NZ)
	 */
	float animBlendRate;

	/**
	 * @brief		�A�j���[�V�����̍Đ����I�������Ƃ��ɍĐ�����Idle��ID
	 * @History		24/09/24 �쐬(NZ)
	 */
	int defaultAnimId = 0;


public:

	/**
	 * @brief		�Đ����~
	 * @History		24/09/24 �쐬(NZ)
	 */
	bool isStop;

	/**
	 * @brief		�u�����h�̃X�s�[�h
	 * @History		24/09/29 �쐬(NZ)
	 */
	float blendSpeed;

	/**
	 * @brief		�A�j���[�V�����̌��݂̍Đ�����
	 * @History		24/09/24 �쐬(NZ)
	 */
	double playTime;


public:
	/*     ���\�b�h     */

	/**
	 * @brief		�R���X�g���N�^
	 * @author		NZ
	 * @date		24/09/24
	 */
	HWAnimator(){}

	/**
	 * @brief		�f�X�g���N�^
	 * @author		NZ
	 * @date		24/09/24
	 */
	~HWAnimator();

	/**
	 * @brief		�A�j���[�V���������[�h���� �����[�h����A�j���[�V�����̓A�j���[�V��������������Ă��Ȃ�����
	 * @param[in]	const std::string& �A�j���[�V�����t�@�C���̃p�X
	 * @param[in]	const int		   �ǂݍ��ރA�j���[�V����ID
	 * @return		AnimInfo& �A�j���[�V�������(�߂�l����p�����[�^�𑀍삷��)
	 * @author		NZ
	 * @date		24/09/24
	 */
	AnimInfo* AnimLoad(const std::string& _filePath, const int _animId = 0);

	/**
	 * @brief		�Đ�����A�j���[�V�������w��
	 * @param[in]	const int �Đ�����A�j���[�V����ID
	 * @param[in]	bool	  �����I�ɐ؂�ւ��邩
	 * @author		NZ
	 * @date		24/09/24
	 */
	void AnimChange(const int _animId, bool forcedSwitchover = false);

#pragma region Setter�֐�

	/**
	 * @brief		�A�j���[�V�����̍Đ����I���������Ɏ����Đ������default�A�j���[�V����(Idol�A�j���[�V�����Ȃ�)
	 * @param[in]	const int �f�t�H���g�̃A�j���[�V����ID
	 * @author		NZ
	 * @date		24/09/24
	 */
	void SetDefaultAnimId(const int _defaultAnimId) { defaultAnimId = _defaultAnimId; }

#pragma endregion

#pragma region Getter�֐�

	/**
	 * @brief		�A�j���[�V���������i�[���Ă���R���e�i���擾����
	 * @return		std::vector<std::unique_ptr<AnimInfo>>&	�A�j���[�V���������i�[���Ă���R���e�i
	 * @author		NZ
	 * @date		24/09/29
	 */
	std::vector<std::unique_ptr<AnimInfo>>& GetAnimInfoVec() { return animInfoVec; }

	/**
	 * @brief		�Đ����̃A�j���[�V���������擾����
	 * @return		AnimInfo*	�A�j���[�V�������
	 * @author		NZ
	 * @date		24/09/29
	 */
	AnimInfo* GetPlayAnimInfo() { return animInfoVec[playIndex1].get(); }

	/**
	 * @brief		�Đ����Ă���A�j���[�V����1�̃C���f�b�N�X���擾����
	 * @return		const int �Đ����̃A�j���[�V�����C���f�b�N�X1
	 * @author		NZ
	 * @date		24/09/30
	 */
	const int GetPlayAnimId() { return playIndex1; };

	/**
	 * @brief		�u�����h���Ă���A�j���[�V����1�̃C���f�b�N�X���擾����
	 * @return		const int �u�����h���̃A�j���[�V�����C���f�b�N�X1
	 * @author		NZ
	 * @date		24/09/30
	 */
	const int GetBlendAnimId() { return playIndex2; };

#pragma endregion



private:

	/**
	 * @brief		�A�j���[�V�������Đ�����
	 * @author		NZ
	 * @date		24/09/24
	 */
	void AnimPlay();



protected:

#pragma region �I�[�o�[���C�h���\�b�h

	/**
	 * @brief		HWGameObject�ɃA�^�b�`���ꂽ�u�Ԃɓ���
	 * @detail		�I�[�o���C�h���\�b�h
	 * @author		NZ
	 * @date		24/09/25
	 */
	void Awake()override;

	/**
	 * @brief		���t���[���Ă΂��
	 * @detail		�I�[�o�[���C�h�֐�
	 * @author		NZ
	 * @date		24/09/25
	 */
	void Update() override;

#pragma endregion
};

