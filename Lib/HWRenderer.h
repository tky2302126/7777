#pragma once
#include "HWComponent.h"
#include "HWGameObject.h"


/**
* @author   NZ
* @date     24/08/25
* @note		���f���`��R���|�[�l���g�̒�`
*/


/**
 * @class	HWRenderer
 * @brief	���f���`��p�̃R���|�[�l���g
 */
class HWRenderer : public HWComponent
{
	// ����̃N���X�ȊO����̃A�N�Z�X��h�����߂̃t�����h�錾
	friend class HWGameObject;

private:

	/*     �����o�ϐ�     */

	/**
	 * @brief		���f���n���h��
	 * @History		24/08/25 �쐬(NZ)
	 */
	int modelHandle;


public:

	/*     ���\�b�h     */

	/**
	 * @brief		HWRenderer�̃R���X�g���N�^
	 * @detail		�����Ń��f���t�@�C���̃p�X���A���f���n���h�����w���
	 * @author		NZ
	 * @date		24/08/25
	 */
	HWRenderer() : modelHandle(-1) {}

	/**
	 * @brief		HWRenderer�̃R���X�g���N�^
	 * @detail		���f���t�@�C���̃p�X�ł���
	 * @param[in]	int ���f���n���h��
	 * @author		NZ
	 * @date		24/08/25
	 */
	HWRenderer(const int _modelHandle);

	/**
	 * @brief		HWRenderer�̃R���X�g���N�^
	 * @detail		���f���t�@�C���̃p�X�ł���
	 * @param[in]	std::string �ǂݍ��ރ��f����MV1�t�@�C���̃p�X
	 * @author		NZ
	 * @date		24/08/25
	 */
	HWRenderer(const std::string& _pass);

	/**
	 * @brief		�f�X�g���N�^
	 * @author		NZ
	 * @date		24/07/19
	 */
	virtual ~HWRenderer();


#pragma region Getter�֐�

	/**
	 * @brief		���f���n���h�����擾����
	 * @return		int ���f���n���h��
	 * @author		NZ
	 * @date		24/08/25
	 */
	int GetModelHandle() { return modelHandle; }

#pragma endregion

#pragma region Setter�֐�

	 /**
	  * @brief		���f���n���h����ύX����(���f���̊O����ύX���鎞�Ȃ�)
	  * @param[in]	int �V���ȃ��f���n���h�� 
	  * @author		NZ
	  * @date		24/08/25
	  */
	void SetModelHandle(const int _modelHandle) { modelHandle = _modelHandle; }

#pragma endregion

protected:

#pragma region �I�[�o�[���C�h���\�b�h

	/**
	 * @brief		�ŏ���Update���\�b�h�̒��O�ɓ���
	 * @detail		���z�֐�
	 * @author		NZ
	 * @date		24/06/17
	 */
	void Start() override;

	/**
	 * @brief		���t���[���Ă΂��
	 * @detail		�I�[�o�[���C�h�֐�
	 * @author		NZ
	 * @date		24/09/01
	 */
	void LateUpdate() override;

#pragma endregion
};

