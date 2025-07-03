#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <functional>
#include <chrono>
#include <thread>
#include <future>
#include <cstdio>
#include <cstdint>
#include <random>
#include <unordered_map>
#include "Syslog.h"
#include "EffekseerForDXLib.h"


//! �A�j���[�V�����̃u�����h���ω����x
constexpr float PLAYER_ANIM_BLEND_SPEED = 0.0166f;
// ���w�֌W.
constexpr float NEARLY_THRESHOLD = 0.000001f;			// 2�̐��l���߂��Ɣ��f���鍷�̋��e�l
// �R���W�����֌W.
constexpr float HIT_SLIDE_LENGTH = 5.0f;				// ��x�̕ǉ����o�������ŃX���C�h�����鋗��
// Pad
#define PAD_INPUT_DINPUT								(0x70000000)



//--------------------------------------------------------
// �I�y���[�^�[
//--------------------------------------------------------

inline VECTOR operator+(VECTOR a, VECTOR b) { return VAdd(a,b); }
inline VECTOR operator-(VECTOR a, VECTOR b) { return VSub(a,b); }
inline VECTOR operator*(VECTOR a, float b) { return VScale(a,b); }
inline VECTOR operator+=(VECTOR& a, VECTOR b) { return a = VAdd(a,b); }
inline VECTOR operator-=(VECTOR& a, VECTOR b) { return a = VSub(a,b); }
inline VECTOR operator*=(VECTOR a, float b) { return a = VScale(a,b); }
inline bool operator==(VECTOR a, VECTOR b) { return (a.x == b.x && a.y == b.y && a.z == b.z); }
inline bool operator==(VECTOR a, float b) { return (a.x == b && a.y == b && a.z == b); }



/**
 * @class	Utility
 * @brief	
 */
class HWUtility
{
public:
	static int ScreenSizeX;
	static int ScreenSizeY;
};


/**
* @author   NZ
* @date     24/07/20
* @note		�ėp�I�ȃN���X�̒�`���܂Ƃ߂��w�b�_�[�t�@�C��
*/


/**
 * @class	ReadOnly
 * @brief	�ǂݎ���p�ɂ��郉�b�p�[�N���X	
 */
template<class T>
class ReadOnly
{
private:

	/*     �����o�ϐ�     */

	/**
	 * @brief		�l��ۊǂ���I�u�W�F�N�g
	 * @History		24/09/14 �쐬(NZ)
	 */
	T obj;


public:

	/*     ���\�b�h     */

	/**
	 * @brief		�R���X�g���N�^
	 * @param[in]	T �����l
	 * @author		NZ
	 * @date		24/09/14
	 */
	ReadOnly(T _obj) : obj(_obj) {}

	/**
	 * @brief		�֐��Ăяo��operator�̒�`
	 * @param[in]	T �����l
	 * @author		NZ
	 * @date		24/09/14
	 */
	operator T() const { return obj; }

	// �l�̕ύX���֎~���邽�߁A���operator�͍폜
	ReadOnly& operator=(const T&) = delete;
};


/**
 * @class	PoolAllocator
 * @brief	�������Ǘ������������邽�߂̃������A���P�[�^�[
 */
template<class T, size_t MAXSIZE>
class PoolAllocator
{
private:

	/*     �����o�ϐ�     */

	union Block
	{
		char pool[sizeof(T)];
		Block* nextBlock;
	};

	/**
	 * @brief		�������v�[��
	 * @History		24/09/01 �쐬(NZ)
	 */
	Block block[MAXSIZE];

	/**
	 * @brief		�󂫃������u���b�N�̐퓬
	 * @History		24/09/01 �쐬(NZ)
	 */
	Block* freeBlockHead;


public:

	/*     ���\�b�h     */

	/**
	 * @brief		�R���X�g���N�^
	 * @author		NZ
	 * @date		24/09/01
	 */
	PoolAllocator()
	{
		// �������u���b�N���m��A������
		for (size_t i = 0; i < MAXSIZE - 1; ++i)
			block[i].nextBlock = &block[i + 1];
		// ������ nullptr
		block[MAXSIZE - 1].nextBlock = nullptr;

		// �󂫃������̐擪�̏����l�� block �̐擪
		freeBlockHead = block;
	}

	/**
	 * @brief		�f�X�g���N�^
	 * @author		NZ
	 * @date		24/09/01
	 */
	~PoolAllocator() {}

	/**
	 * @brief		���������m�ۂ���
	 * @return		�m�ۂ���������
	 * @author		NZ
	 * @date		24/09/01
	 */
	T* Alloc()
	{
		// �󂫃������u���b�N���Ȃ��ꍇ�Anullptr ��Ԃ�
		if (freeBlockHead == nullptr)
			return nullptr;

		//! �m�ۂ���������
		T* ret = reinterpret_cast<T*>(freeBlockHead);
		// �󂫃������u���b�N���X�V
		freeBlockHead = freeBlockHead->nextBlock;

		// ���I�ɃR���X�g���N�^���Ă�
		return new(ret) T();
	}

	/**
	 * @brief		���������m�ۂ���
	 * @return		�m�ۂ���������
	 * @author		NZ
	 * @date		24/09/01
	 */
	template<typename... Args>
	T* Alloc(Args&&... args)
	{
		// �󂫃������u���b�N���Ȃ��ꍇ�Anullptr ��Ԃ�
		if (freeBlockHead == nullptr)
			return nullptr;

		// �������u���b�N���m��
		T* ret = reinterpret_cast<T*>(freeBlockHead);

		// �󂫃������u���b�N���X�V
		freeBlockHead = freeBlockHead->nextBlock;

		// �����t���R���X�g���N�^���Ăяo��
		return new(ret) T(std::forward<Args>(args)...);
	}

	/**
	 * @brief		���������������
	 * @param[in]	T* Alloc�Ŋm�ۂ���������
	 * @author		NZ
	 * @date		24/09/01
	 */
	void Free(T* _addr)
	{
		if (_addr == nullptr)
			return;

		// �����I�Ƀf�X�g���N�^���Ă�
		_addr->~T();

		//! �������A�h���X
		Block* freeBlock = reinterpret_cast<Block*>(_addr);

		// freeBlockHead��nullptr�̏ꍇ�ɑΉ�
		if (freeBlockHead == nullptr) {
			freeBlock->nextBlock = nullptr;
			freeBlockHead = freeBlock;
		}
		else {
			// ��������u���b�N�����X�g�̐擪�ɒǉ�
			freeBlock->nextBlock = freeBlockHead;
			freeBlockHead = freeBlock;
		}
	}
};


/**
 * @class	Time
 * @brief	���Ԋ֌W
 */
class Time 
{
	friend class HandlerWaltan;

public:
	// deltaTime��Ԃ��֐�
	static float DeltaTime() { return deltaTime; }

	// 1�b�o�߂����ꍇ�̓t���[������Ԃ�
	int GetCurrentFPS() { return frameCount; }

	// n�b��̃t���[�������v�Z
	int GetFrameCountInFuture(float seconds) { return static_cast<int>(seconds * Time::targetFPS); }

	// �Q�[�����[�v�Ŗ��t���[���Ăяo�����֐�
	static void Update()
	{
		float currentTime = GetNowCount() / 1000.0f;  // �b�ɕϊ�
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// �t���[�����ƌo�ߎ��Ԃ��X�V
		frameCount++;
		elapsedTime += deltaTime;

		// 1�b�o�߂�����FPS�����Z�b�g
		if (elapsedTime >= 1.0f) {
			elapsedTime = 0.0f;
			frameCount = 0;  // �t���[�����̃��Z�b�g
		}
	}

	// FPS�Œ艻�̂��߂̊֐�
	static void SetTargetFPS(int fps)
	{
		targetFPS = fps;
		targetFrameTime = 1.0f / static_cast<float>(fps);  // 1�t���[��������̎��Ԃ��v�Z
	}

	static void WaitForNextFrame()
	{
		float frameEndTime = GetNowCount() / 1000.0f;
		float frameDuration = frameEndTime - lastTime;
		if (frameDuration < targetFrameTime)
		{
			int sleepTime = static_cast<int>((targetFrameTime - frameDuration) * 1000);
			if (sleepTime > 0)
				std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
		}
	}

	static void ShowFPS()
	{
		DrawFormatString(HWUtility::ScreenSizeX / 2 - 30, 10, color, "%d FPS", frameCount);
	}

private:
	static float deltaTime;    // �O�t���[���Ƃ̎��ԍ�
	static float lastTime;     // �O�t���[���̎���
	static int targetFPS;      // �^�[�Q�b�gFPS
	static float targetFrameTime;  // �^�[�Q�b�g�̃t���[������ (�b)    
	static int frameCount;      // �t���[�������J�E���g����ϐ�
	static float elapsedTime;    // �o�ߎ��Ԃ�ێ�����ϐ�

public:
	static bool debugMode;
	static unsigned int color;

};


/**
 * @class	CsvLoader
 * @brief	csv�t�@�C�����J���}��؂�œǂݍ���
 * @detail	�ÓI�N���X
 */
class CsvLoader final
{
private:

	/*     �����o�ϐ�     */


public:

	/*     ���\�b�h     */

	// �ÓI�N���X�̂��߁A�R���X�g���N�^�ƃf�X�g���N�^���폜
	CsvLoader() = delete;
	~CsvLoader() = delete;


	/**
	 * @brief		csv�t�@�C����ǂݍ��݁A�s��؂�A�J���}��؂�ŕ������Ԃ�
	 * @param[in]	std::string	�ǂݍ���csv�t�@�C���̃p�X
	 * @return		std::vector<std::vector<std::string>> �ǂݍ��񂾕������Ԃ�(1���� = �s, 2���� = �J���}��؂�)
	 * @author		NZ
	 * @date		24/09/14
	 */
	static std::vector<std::vector<std::string>> Load(const std::string _filePath)
	{
		//! �߂�l
		std::vector<std::vector<std::string>> ret;

		// �t�@�C����ǂݍ���
		std::ifstream file(_filePath);
		// �t�@�C���ǂݍ��݂Ɏ��s�����ꍇ�A���̂܂܏I��
		if (!file)
			return ret;

		//! �s��؂�œǂݍ��񂾕�����
		std::string line;

		// 1�s���ǂݍ���
		while (std::getline(file, line))
		{
			//! �J���}��؂�œǂݍ��񂾕�����
			std::vector<std::string> comma;
			//! �m�F�ς݂̕������index
			size_t confirmed = 0;
			//! �J���}��������index
			size_t commaPos = 0;
			
			// �J���}��؂�œǂݍ���
			do
			{
				// �O��J���}��������index����J���}��������
				commaPos = line.find_first_of(',', confirmed);
				// �J���}��������Ȃ������ꍇ�͂��̂܂܏I��
				if (commaPos == std::string::npos)
				{
					// �O��̃R���}�̈ʒu����R�s�[
					comma.push_back(line.substr(confirmed));
					break;
				}

				// �O��̃R���}�̈ʒu���玟�̃R���}�̈ʒu�܂ł̕�������R�s�[
				comma.push_back(line.substr(confirmed, commaPos - confirmed));

				// �m�F�ς݂̕�������X�V
				confirmed = commaPos + 1;
			} while (commaPos != std::string::npos);

			// �J���}���Ȃ��Ȃ����猋�ʂ�ǉ�
			ret.push_back(comma);
		}

		return ret;
	}
};


/**
 * @class	Random
 * @brief	�����֌W
 * @detail	�ÓI�N���X
 */
class Random
{
public:
	// �����̃����_���Ȓl�𐶐����郁�\�b�h
	static int GetRandomInt(int min, int max) {
		std::uniform_int_distribution<> dist(min, max);
		return dist(GetGenerator());
	}

	// float�^�̃����_���Ȓl�𐶐����郁�\�b�h
	static float GetRandomFloat(float min, float max) {
		std::uniform_real_distribution<float> dist(min, max);
		return dist(GetGenerator());
	}

	// �V�[�h��ݒ肷�郁�\�b�h�i����Ō���I�ȗ����𐶐��ł���j
	static void SetSeed(unsigned int seed) {
		GetGenerator(seed);
	}

private:
	// �����������Ԃ����\�b�h�i�V�[�h�t���o�[�W�����j
	static std::mt19937& GetGenerator(unsigned int seed = 0) {
		static std::mt19937 gen;  // ����������i�ÓI�ɕێ��j
		static bool seeded = false; // �V�[�h���ݒ肳�ꂽ���ǂ����̃t���O

		// �V�[�h��0�łȂ��A���܂��V�[�h����Ă��Ȃ��ꍇ�̂ݐݒ�
		if (seed != 0 || !seeded) {
			if (seed == 0) {
				// �񌈒�I�ȃV�[�h�i�f�t�H���g����j
				std::random_device rd;
				gen.seed(rd());
			}
			else {
				// ����I�ȃV�[�h��ݒ�
				gen.seed(seed);
			}
			seeded = true; // �V�[�h���ݒ肳�ꂽ���Ƃ��L�^
		}
		return gen;
	}

	// �R���X�g���N�^�͍폜
	Random() = delete;
};


//--------------------------------------------------------
// �֐�
//--------------------------------------------------------

/**
 * @brief		�x���@ -> �ʓx�@ �ɕϊ�
 * @param[in]	double �p�x
 * @return		double �ϊ��������W�A���l
 * @author		NZ
 * @date		24/09/23
 */
inline double Deg2Rad(const double _angle)
{
	return _angle * DX_PI / 180.f;
}

/**
 * @brief		�ʓx�@ -> �x���@ �ɕϊ�
 * @param[in]	double ���W�A���l
 * @return		double �ϊ������p�x
 * @author		NZ
 * @date		24/09/23
 */
inline double Rad2Deg(const double _radian)
{
	return _radian * 180 / DX_PI;
}

/**
 * @brief		�Q�_�Ԃ̋������擾����
 * @param[in]	VECTOR ���W1
 * @param[in]	VECTOR ���W2
 * @return		float ����
 * @author		NZ
 * @date		24/10/21
 */
inline float Distance(VECTOR v1, VECTOR v2)
{
	return sqrt((v2.x - v1.x) * (v2.x - v1.x) +
		(v2.y - v1.y) * (v2.y - v1.y) +
		(v2.z - v1.z) * (v2.z - v1.z));
}


// ���`��Ԋ֐�
inline float Lerp(float start, float end, float t)
{
	return start + t * (end - start);
}

/**
 * @brief		���`��Ԋ֐�
 * @param[in]	VECTOR ���W1
 * @param[in]	VECTOR ���W2
 * @return		float 
 * @author		NZ
 * @date		24/10/21
 */
inline VECTOR Lerp(VECTOR start, VECTOR end, float t)
{
	VECTOR result;
	result.x = Lerp(start.x, end.x, t);
	result.y = Lerp(start.y, end.y, t);
	result.z = Lerp(start.z, end.z, t);
	return result;
}


// �lA��0����1�̊Ԃɒ�������֐�
inline float Normalize(float A, float min, float max) {
	return (A - min) / (max - min);
}
