#include "XInput.h"


//!@brief	�R���X�g���N�^
	//!@brief	1�`4�܂ł̔ԍ������蓖�Ă�
	//!@param[in]	controllerNumber	�R���g���[���ԍ�
XInput::XInput(const PadNum& padNum)
{
	this->controllerNumber = padNum;
}
//!@brief	�f�X�g���N�^
XInput::~XInput()
{
	//XInputEnable(false);	//�U��������
}

//!@brief	�R���g���[���[�̏�Ԃ̎擾
//!@return	XINPUT_STATE�^
const XINPUT_STATE&	XInput::GetState()
{
	std::memset(&controllerState, 0, sizeof(XINPUT_STATE));
	XInputGetState(static_cast<DWORD>(controllerNumber), &controllerState);
	return controllerState;
}

//!@brief	�R���g���[�����ڑ�����Ă��邩�m�F
//!@return	true: �ڑ�����Ă��� false: �ڑ�����Ă��Ȃ�
bool	XInput::IsConnect()
{
	std::memset(&controllerState, 0, sizeof(XINPUT_STATE));
	DWORD result = XInputGetState(static_cast<DWORD>(controllerNumber), &controllerState);
	if (result == ERROR_SUCCESS)
	{
		return true;
	}
	return false;
}

//!@brief	�R���g���[����U��������
//!@param[in]	leftVal	���ւ̐U���l
//!@param[in]	rightVal �E�ւ̐U���l
void	XInput::Vibrate(int leftVal, int rightVal)
{
	XINPUT_VIBRATION	vibration;
	std::memset(&vibration, 0, sizeof(XINPUT_VIBRATION));
	vibration.wLeftMotorSpeed = leftVal;
	vibration.wRightMotorSpeed = rightVal;
	XInputSetState(static_cast<DWORD>(controllerNumber), &vibration);
}


//!@brief	���͂̐���
bool	XInput::CreateInput()
{
	return true;
}
//!@brief	�X�V
void	XInput::Run()
{

}
//!@brief	�����Ă��邩����
//!@return �����Ă���Ȃ� true �����Ă��Ȃ��Ȃ� false
bool	XInput::Press(const int key)
{
	if (this->GetState().Gamepad.wButtons & key)
	{
		return true;
	}
	return false;
}
//!@brief	������������
//!@return �������Ȃ� true �����ĂȂ��Ȃ� false
bool	XInput::Push(const int key)
{
	return true;
}
//!@brief	������Ă��Ȃ�������
//!@return ������Ă��Ȃ��Ȃ� true �����Ă���Ȃ� false
bool	XInput::Free(const int key)
{
	return true;
}
//!@brief	�����ꂽ������
//!@return �����ꂽ�Ȃ� true ������Ă��Ȃ��Ȃ� false
bool	XInput::Release(const int key)
{
	return true;
}