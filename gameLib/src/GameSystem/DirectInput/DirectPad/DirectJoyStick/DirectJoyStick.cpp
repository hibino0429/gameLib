#include "DirectJoyStick.h"
#include "../../src/Utility/Utility.hpp"




//!@brief	�R���X�g���N�^
DirectJoyStick::DirectJoyStick()
{
	
}
//!@brief	�f�X�g���N�^
DirectJoyStick::~DirectJoyStick()
{

}

//!@brief	�W���C�X�e�B�b�N�f�o�C�X�̎擾
//!@return	joystickDevice
const LPDIRECTINPUTDEVICE8&	DirectJoyStick::GetJoystick() const
{
	return joystickDevice;
}

//!@brief	���݂̃W���C�X�e�B�b�N�̏�Ԃ̎擾
	//!@return	nowJoyState
const DIJOYSTATE&	DirectJoyStick::GetNowJoyState() const
{
	return nowJoyState;
}
//!@brief	1�O�̃W���C�X�e�B�b�N�̏�Ԃ̎擾
//!@return	preJoyState
const DIJOYSTATE&	DirectJoyStick::GetPreJoyState() const
{
	return preJoyState;
}

//!@brief	�f�o�C�X�̍쐬
bool	DirectJoyStick::CreateDevice()
{
	auto result = DirectInput::GetInstance()->CreateDevice(GUID_Joystick, &joystickDevice, nullptr);
	if (FAILED(result))
	{
		MessageBoxA(nullptr, "Joystick�̃f�o�C�X�쐬�Ɏ��s", "DirectJoyStick::CreateDevice()", MB_OK);
		return false;
	}
	return true;
}
//!@brief	���̓f�[�^�`���̐ݒ�
bool	DirectJoyStick::SetDataFormat()
{
	auto result = joystickDevice->SetDataFormat(&c_dfDIJoystick2);
	if (FAILED(result))
	{
		MessageBoxA(nullptr, "���̓f�[�^�`���̃Z�b�g�Ɏ��s", "DirectJoyStick::SetDataFormat()", MB_OK);
		joystickDevice->Release();
		return false;
	}
	return true;
}
//!@brief	�r������
bool	DirectJoyStick::SetCooperativeLevel(const HWND& hWnd)
{
	auto result = joystickDevice->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(result))
	{
		MessageBoxA(nullptr, "�r������Ɏ��s", "DirectJoyStick::SetCooperativeLevel()", MB_OK);
		joystickDevice->Release();
		return false;
	}
	return true;
}
//!@brief	����
void	DirectJoyStick::Run()
{
	//�p�b�h���擾���Ă��Ȃ���Ώ������s��Ȃ�
	if (!joystickDevice)
	{
		return;
	}
	auto result = joystickDevice->Acquire();
	if (result == DI_OK || S_FALSE)
	{
		if (SUCCEEDED(joystickDevice->Poll()))
		{
			preJoyState = nowJoyState;
			joystickDevice->GetDeviceState(sizeof(DIJOYSTATE), &nowJoyState);
		}
	}
}
//!@brief	�I������
void	DirectJoyStick::Finalize()
{
	Utility::SafeRelease(joystickDevice);
}

//!@brief	�W���C�X�e�B�b�N�̃f�o�C�X�̊m��
bool	DirectJoyStick::SetEnumDevice()
{
	auto result = DirectInput::GetInstance()->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumPadCallback, nullptr, DIEDFL_ATTACHEDONLY);
	if (FAILED(result))
	{
		MessageBoxA(nullptr, "Joystick��������܂���", "DirectJoyStick::CreateDevice()", MB_OK);
		return false;
	}
	return true;
}
//!@brief	�W���C�X�e�B�b�N�̓��͂��m�F
bool	DirectJoyStick::CheckEnumObjects(const HWND& hWnd)
{
	auto result = joystickDevice->EnumObjects(EnumAxisCallback, (void*)hWnd, DIDFT_ALL);
	if (FAILED(result))
	{
		MessageBoxA(nullptr, "�W���C�X�e�B�b�N�I�u�W�F�N�g�̊m�F�Ɏ��s", "DirectJoyStick::EnumObjects()", MB_OK);
		return false;
	}
	return true;
}

//!@brief �ڑ�����Ă���pad�����m����
//!@param[in]	instance	���̓f�o�C�X�̃C���X�^���X
//!@param[in]	context	�R���e�L�X�g�̃|�C���^
BOOL CALLBACK DirectJoyStick::EnumPadCallback(const DIDEVICEINSTANCE* instance,void* pContext)
{
	//�񋓂��ꂽ�W���C�X�e�B�b�N�ւ̃C���^�[�t�F�C�X���擾
	DirectJoyStick*	joystick = reinterpret_cast<DirectJoyStick*>(pContext);
	auto result = DirectInput::GetInstance()->CreateDevice(instance->guidInstance, &joystick->joystickDevice, nullptr);
	if (FAILED(result))
	{
		DirectInput::GetInstance()->Release();
		return DIENUM_CONTINUE;
	}
	
	//�W���C�X�e�B�b�N�̔\�͂��m�F
	joystick->deviceCaps.dwSize = sizeof(DIDEVCAPS);
	result = joystick->joystickDevice->GetCapabilities(&joystick->deviceCaps);
	if (FAILED(result))
	{
		DirectInput::GetInstance()->Release();
		return DIENUM_CONTINUE;
	}
	return DIENUM_STOP;
}
//!@brief	�p�b�h�̐ݒ�
//!@param[in]	objInstance �I�u�W�F�N�g�C���X�^���X
//!@param[in]	context	�R���e�L�X�g�̃|�C���^
BOOL CALLBACK DirectJoyStick::EnumAxisCallback(const DIDEVICEOBJECTINSTANCE* objInstance,void* pContext)
{
	//���͈͎w��
	DIPROPRANGE prg;
	prg.diph.dwSize = sizeof(prg);
	prg.diph.dwHeaderSize = sizeof(prg);
	prg.diph.dwHow = DIPH_BYID;
	prg.diph.dwObj = objInstance->dwType;
	prg.lMin = 0 - 1000;	//�X���ŏ��l
	prg.lMax = 0 + 1000;	//�X���ő�l

	auto result = reinterpret_cast<DirectJoyStick*>(pContext)->joystickDevice->SetProperty(
		DIPROP_RANGE,
		&prg.diph
	);
	if (FAILED(result))
	{
		return DIENUM_STOP;
	}
	return DIENUM_CONTINUE;
}

