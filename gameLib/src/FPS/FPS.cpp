#include "FPS.h"


//!@brief	�R���X�g���N�^
FPS::FPS()
	: frameCount(0)
	,frameRate(0)
	,deltaTime(0)
	,second(0)
{
	preCount = GetCounter();
	frequency = GetCountFrequency();
}

//!@brief	�f�X�g���N�^
FPS::~FPS()
{

}

//!@brief	FPS�̓�����������
void	FPS::Run()
{
	LARGE_INTEGER count = GetCounter();
	deltaTime = static_cast<float>(count.QuadPart - preCount.QuadPart) / frequency.QuadPart;
	preCount = GetCounter();

	time += deltaTime;
	frameCount++;
	if (second >= 1.0f)
	{
		frameRate = frameCount;
		frameCount = 0;
		second -= 1.0f;
	}
}

//!@brief	�A�v���P�[�V�����N��������̎��Ԃ�Ԃ�
//!@return	����
float	FPS::GetTime() const
{
	return time;
}

//!@brief	�O�̃t���[���ƍ��̃t���[���̎��ԍ���Ԃ�
//!@return ���ԍ�
float	FPS::GetDeltaTime() const
{
	return deltaTime;
}

//!@brief	���݂̃t���[�����[�g��Ԃ�
//!@return �t���[�����[�g
int		FPS::GetFrameRate() const
{
	return frameRate;
}



LARGE_INTEGER FPS::GetCounter() const
{
	LARGE_INTEGER	counter;
	QueryPerformanceCounter(&counter);
	return counter;
}

LARGE_INTEGER FPS::GetCountFrequency() const
{
	LARGE_INTEGER	frequency;
	QueryPerformanceFrequency(&frequency);
	return frequency;
}