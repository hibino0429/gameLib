#pragma once
#include <atlbase.h>

//---------------------------------------------------------------------------------
//!@class		FPS
//!@brief	Frame/Per/Second���v������N���X
//!@brief	FPS���Œ肳����
//---------------------------------------------------------------------------------
class FPS
{
public:
	//!@brief	�R���X�g���N�^
	FPS();
	//!@brief	�f�X�g���N�^
	~FPS();

	//!@brief	FPS�̓�����������
	void	Run();
	//!@brief	�A�v���P�[�V�����N��������̎��Ԃ�Ԃ�
	//!@return	����
	float	GetTime() const;
	//!@brief	�O�̃t���[���ƍ��̃t���[���̎��ԍ���Ԃ�
	//!@return ���ԍ�
	float	GetDeltaTime() const;
	//!@brief	���݂̃t���[�����[�g��Ԃ�
	//!@return �t���[�����[�g
	int		GetFrameRate() const;

private:
	LARGE_INTEGER GetCounter() const;
	LARGE_INTEGER GetCountFrequency() const;
private:
	float	time;
	float	deltaTime;
	int		frameRate;
	float	second;
	int		frameCount;
	LARGE_INTEGER preCount;
	LARGE_INTEGER frequency;

};