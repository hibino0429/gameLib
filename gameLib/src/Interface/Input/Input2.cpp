#include "Input2.h"


InputDevice* InputEngine::device = nullptr;

//!@brief	���̓f�o�C�X�̓o�^
//!@param[in]	inputDevice	���̓f�o�C�X
void InputEngine::Regist(InputDevice* inputDevice)
{
	device = inputDevice;
}
//!@brief	���̓f�o�C�X�̉���
void InputEngine::Release()
{
	if (device != nullptr)
	{
		delete device;
		device = nullptr;
	}
}

//!@brief	���̓f�o�C�X�̎擾
InputDevice&	InputEngine::GetDevice()
{
	return *device;
}




//!@brief	�R���X�g���N�^
//!@param[in]	���̓f�o�C�X�̃|�C���^
InputI::InputI(InputDevice* inputDevice)
{
	inputEngine->Regist(inputDevice);
}

//!@brief	�f�X�g���N�^
InputI::~InputI()
{
	inputEngine->Release();
}

//!@brief	���̓G���W���̎擾
//!@return	�ێ����Ă�����̓G���W��
const InputEngine&	InputI::GetInputEngine() const
{
	return *inputEngine;
}
