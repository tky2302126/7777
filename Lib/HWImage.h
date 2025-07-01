#pragma once
#include "HWComponent.h"
#include "HWTransform.h"

/**
* @author   NZ
* @date     25/03/04
* @note		�摜�`��R���|�[�l���g�̒�`
*/


/**
 * @class	ImageRenderType
 * @brief	�摜�`��̃^�C�v
 */
enum class ImageRenderType
{
	//! �ʏ�`��
	Default,
	//! �J�X�^��
	Custom,
};


/**
 * @class	HWImage
 * @brief	�摜�`��R���|�[�l���g�̒�`
 */
class HWImage : public HWComponent
{
	//
	// �����o�ϐ�
	//

public:

	//! �`��^�C�v
	ImageRenderType renderType;
	//! �摜�n���h��
	int graphHandle;
	//! ���ߏ������s����
	bool isTrans;
	
private:
	
	std::function<void()> customRenderFunction;
 

	//
	// ���\�b�h
	//

public:

	/**
	 * @brief		�R���X�g���N�^
	 * @param[in]	�摜��Path
	 */
	HWImage(const std::string& _path, ImageRenderType _renderType = ImageRenderType::Default);

	/**
	 * @brief		�f�X�g���N�^
	 */
	~HWImage();

	/**
	 * @brief		�`����@���w��
	 * @param		�`��֐��̎w��
	 */
	void SetRenderFunction(std::function<void()> _customRenderFunction)
	{
		customRenderFunction = _customRenderFunction;
	}

	/**
	 * @brief		�X�V����
	 */
	void LateUpdate()override;
};


