#pragma once
#include "Utilities.h"


/**
* @author   NZ
* @date     24/08/25
* @note     ���O���o�͂���N���X�̒�`
*/


/**
 * @enum	LogLevel	
 * @brief	Syslog���x��
 */
enum class LogLevel
{
    //! �f�o�b�O(0)
    debug,
    //! ���(1)
    info,
    //! �G���[(2)
    err,
};


/**
 * @struct	
 * @brief	
 */
typedef struct
{
    //! �N
    int Year;
    //! ��
    int Mon;
    //! ��
    int Day;
    //! ����
    int Hour;
    //! ��
    int Min;
    //! �b
    int Sec;
    //! �~���b
    long long millisec;
}TimeData;

/**
 * @struct	LogInfo
 * @brief	Syslog�̏o�͂ɕK�v�ȏ��
 */
typedef struct
{
    //! Syslog���x��
    LogLevel loglevel;
    //! ���O���b�Z�[�W
    std::string logMessage;
    //! �o�͎���
    TimeData timeData;

}LogInfo;


/**
 * @class  	Syslog
 * @brief  	�w��̃��O���o�͂���N���X
 * @detail  �ÓI�N���X�Ő݌v����
 */
class Syslog final
{
private:

    /*     �����o�ϐ�     */

    /**
     * @brief		���O���b�Z�[�W�̃R���e�i
     * @History		24/08/25 �쐬(NZ)
     */
    static std::vector<LogInfo> logInfoVec;

    /**
     * @brief		�X���b�h�Z�[�t�Ńe�L�X�g�t�@�C���ɏ������ނ���
     * @History		24/09/11 �쐬(NZ)
     */
    static std::mutex mtx;

    /**
     * @brief		�X���b�h�Z�[�t�Ńe�L�X�g�t�@�C���ɏ������ނ���
     * @History		24/09/11 �쐬(NZ)
     */
    std::thread syslogThread;

public:

    /*     ���\�b�h     */

    static void Message(const LogLevel _loglevel, const std::string& _logMessage);

private:

    /**
     * @brief       �R���X�g���N�^�͍폜
     * @author      NZ
     * @date        24/08/25
     */
    Syslog() = delete;


    /**
     * @brief       ���O����ǉ�����
     * @author      NZ
     * @date        24/08/25
     */
    static void AddLogInfoAsymc(const LogLevel _loglevel, const std::string& _logMessage);
};