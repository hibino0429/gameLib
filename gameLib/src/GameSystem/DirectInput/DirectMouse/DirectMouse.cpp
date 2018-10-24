#include "DirectMouse.h"
#include "../../src/Utility/Utility.hpp"


//!@brief	�R���X�g���N�^
//!@param[in]	hWnd	�E�B���h�E�n���h��
DirectMouse::DirectMouse(const HWND& hWnd)
	: DIMouse(nullptr)
{
	position = { 0,0 };
	mouseState = { 0 };
	CreateMouseInput(hWnd);
}
//!@brief	�f�X�g���N�^
DirectMouse::~DirectMouse()
{
	Utility::SafeRelease(DIMouse);
}


//!@brief	���̓}�E�X�f�o�C�X�̍쐬
//!@param[in]	hWnd	�n���h��
bool	DirectMouse::CreateMouseInput(const HWND& hWnd)
{
	this->hWnd = hWnd;
	auto result = DirectInput::GetInstance()->CreateDevice(GUID_SysMouse, &DIMouse, nullptr);
	if (FAILED(result))
	{
		return false;
	}
	result = DIMouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
	{
		return false;
	}
	result = DIMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(result))
	{
		return false;
	}
	//�f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j
	if (FAILED(result))
	{
		return false;
	}
	//���͐���J�n
	DIMouse->Acquire();
	return true;
}

//!@brief	�X�V
void	DirectMouse::Run()
{
	DIMOUSESTATE	diMouseState;
	memcpy(&diMouseState, &mouseState, sizeof(diMouseState));
	auto result = DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState);

	if (FAILED(result))
	{
		while (DIMouse->Acquire() == DIERR_INPUTLOST);
	}
}

//!@brief	������Ă��邩����
bool	DirectMouse::LButtonPush()
{
	if (mouseState.rgbButtons[static_cast<unsigned int>(Button::Left)] & 0x80)
	{
		return true;
	}
	return false;
}

//!@brief	������Ă��邩����
bool	DirectMouse::RButtonPush()
{
	if (mouseState.rgbButtons[static_cast<unsigned int>(Button::Right)] & 0x80)
	{
		return true;
	}
	return false;
}

//!@brief	�}�E�X�J�[�\���̈ʒu�̎擾
//!@return	�}�E�X�J�[�\���̈ʒu
POINT	DirectMouse::GetMousePos()
{
	GetCursorPos(&position);
	ScreenToClient(hWnd, &position);
	return position;
}

bool DirectMouse::WheelRotation()
{
	if (mouseState.lZ == 0)
	{
		return false;
	}
	return true;
}

bool DirectMouse::UpWheelRotation()
{
	if (!WheelRotation()) { return false; }
	if (mouseState.lZ < 0)
	{
		return false;
	}
	return true;
}

bool DirectMouse::DownWheelRotation()
{
	if (!WheelRotation()) { return false; }
	if (mouseState.lZ > 0)
	{
		return false;
	}
	return true;
}





