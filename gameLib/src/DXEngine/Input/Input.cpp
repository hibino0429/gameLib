#include "Input.h"
#include "../../src/Utility/Utility.hpp"


//**********************************************************************************
Input input;


Input::Input()
	: buf(), preBuf()
	, directInput(nullptr)
	, key(nullptr)
{

}
Input::~Input()
{
	if (key != nullptr)
	{
		key->Unacquire();
	}
	Utility::SafeRelease(directInput);
	Utility::SafeRelease(key);
}

//!@brief	���͂̐���
//!@param[in]	hWnd	�E�B���h�E�n���h��
bool	Input::CreateInput(const HWND& hWnd)
{
	auto result = DirectInput8Create(
		GetModuleHandle(nullptr),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(LPVOID*)&directInput,
		nullptr
	);
	if (FAILED(result))
	{
		return false;
	}

	//�f�o�C�X�̎擾
	result = directInput->CreateDevice(
		GUID_SysKeyboard,
		&key,
		nullptr
	);
	if (FAILED(result))
	{
		return false;
	}

	//���̓f�[�^�t�H�[�}�b�g
	result = key->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		return false;
	}

	//�r������
	result = key->SetCooperativeLevel(
		hWnd,
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY
	);
	if (FAILED(result))
	{
		return false;
	}
	//����J�n
	key->Acquire();
	int	keyList[MaxKey] =
	{
		DIK_UP,				//��				
		DIK_LEFT,			//��
		DIK_RIGHT,			//��			
		DIK_DOWN,			//��
		DIK_ESCAPE,			//Esc
		DIK_RETURN,	        //Enter
		DIK_LSHIFT,	        //Shift(��)	
		DIK_RSHIFT,			//Shift(�E)
		DIK_LCONTROL,	    //Ctrl(��)
		DIK_RCONTROL,	    //Ctrl(�E)					
		DIK_LMENU,			//Alt(��)
		DIK_RMENU,			//Alt(�E)
		DIK_SPACE,			//Space
		DIK_BACK,			//Back Space
		DIK_TAB,			//Tab
		DIK_1,     			//1
		DIK_2,     			//2
		DIK_3,     			//3
		DIK_4,     			//4
		DIK_5,     			//5
		DIK_6,     			//6
		DIK_7,     			//7
		DIK_8,     			//8
		DIK_9,     			//9
		DIK_0,     			//0
		DIK_Q,				//Q
		DIK_W,				//W
		DIK_E,				//E
		DIK_R,				//R
		DIK_T,				//T
		DIK_Y,				//Y
		DIK_U,				//U
		DIK_I,				//I
		DIK_O,				//O
		DIK_P,				//P
		DIK_A,				//A
		DIK_S,				//S
		DIK_D,				//D
		DIK_F,				//F
		DIK_G,				//G
		DIK_H,				//H
		DIK_J,				//J
		DIK_K,				//K
		DIK_L,				//L
		DIK_Z,				//Z
		DIK_X,				//X
		DIK_C,				//C
		DIK_V,				//V
		DIK_B,				//B
		DIK_N,				//N
		DIK_M,				//M			
		DIK_F1,				//F1
		DIK_F2,				//F2
		DIK_F3,				//F3
		DIK_F4,				//F4
		DIK_F5,				//F5
		DIK_F6,				//F6
		DIK_F7,				//F7
		DIK_F8,				//F8
		DIK_F9,				//F9
		DIK_F10,			//F10		
	};
	memcpy_s(DIKeyCode, sizeof(DIKeyCode), keyList, sizeof(keyList));
	return true;
}

//!@brief	�X�V
void	Input::Run()
{
	for (int i = 0; i < 256; ++i)
	{
		preBuf[i] = buf[i];
	}

	auto result = key->GetDeviceState(sizeof(buf), &buf);
	if (FAILED(result))
	{
		//�Đݒ�
		key->Acquire();
		key->GetDeviceState(sizeof(buf), &buf);
	}
}


//!@brief	������������
//!@return �������Ȃ� true �����Ă��Ȃ��Ȃ� false
bool	Input::Press(const int key)
{
	unsigned char input = 0x00;
	unsigned char preInput = 0x00;
	input = buf[DIKeyCode[key]] & 0x80;
	preInput = preBuf[DIKeyCode[key]] & 0x80;

	return input != 0 && preInput == 0;
}

//!@brief	�����Ă��邩����
//!@return �����Ă���Ȃ� true �����Ă��Ȃ��Ȃ� false
bool	Input::Push(const int key)
{
	unsigned char input = 0x00;
	input = buf[DIKeyCode[key]] & 0x80;
	return input != 0;
}

//!@brief	������Ă��Ȃ�������
//!@return ������Ă��Ȃ��Ȃ� true �����Ă���Ȃ� false
bool	Input::Free(const int key)
{
	unsigned char input = 0x00;
	input = buf[DIKeyCode[key]] & 0x80;
	return input == 0;
}

//!@brief	�����ꂽ������
//!@return �����ꂽ�Ȃ� true ������Ă��Ȃ��Ȃ� false
bool	Input::Pull(const int key)
{
	unsigned char input = 0x00;
	unsigned char preInput = 0x00;
	input = buf[DIKeyCode[key]] & 0x80;
	preInput = preBuf[DIKeyCode[key]] & 0x80;

	return input == 0 && preInput != 0;
}

//!@brief	DirectInput��Ԃ�
//!@return DirectInput�̃|�C���^
LPDIRECTINPUT8	Input::GetDirectInput() const
{
	return directInput;
}


//***********************************************************************************
PadInput	pad;

//static�ϐ��̎���
int PadInput::padNo = 0;
LPDIRECTINPUTDEVICE8	PadInput::pad[PadInput::padNum] =
{
	nullptr
};

//!@brief �ڑ�����Ă���pad�����m����
//!@param[in]	instance	���̓f�o�C�X�̃C���X�^���X
//!@param[in]	context	�R���e�L�X�g�̃|�C���^
BOOL CALLBACK PadInput::EnumPadCallback(
	const DIDEVICEINSTANCE* instance,
	void* pContext
)
{
	static GUID	padGuid[padNum];
	for (int no = 0; no < padNo; ++no)
	{
		if (instance->guidInstance == padGuid[no])
		{
			return DIENUM_CONTINUE;
		}
	}
	if (FAILED(input.GetDirectInput()->CreateDevice(
		instance->guidInstance,
		&pad[padNo],
		nullptr)))
	{
		return DIENUM_CONTINUE;
	}
	padGuid[padNo] = instance->guidInstance;
	return DIENUM_STOP;
}

//!@brief	�p�b�h�̐ݒ�
//!@param[in]	objInstance �I�u�W�F�N�g�C���X�^���X
//!@param[in]	context	�R���e�L�X�g�̃|�C���^
BOOL CALLBACK PadInput::EnumAxisCallback(
	const DIDEVICEOBJECTINSTANCE* objInstance,
	void* pContext)
{
	//���͈͎w��
	DIPROPRANGE prg;
	prg.diph.dwSize = sizeof(prg);
	prg.diph.dwHeaderSize = sizeof(prg);
	prg.diph.dwHow = DIPH_BYID;
	prg.diph.dwObj = objInstance->dwType;
	prg.lMin = -1000;	//�X���ŏ��l
	prg.lMax = 1000;	//�X���ő�l

	auto result = pad[padNo]->SetProperty(
		DIPROP_RANGE,
		&prg.diph
	);
	if (FAILED(result))
	{
		return DIENUM_STOP;
	}
	return DIENUM_CONTINUE;
}

//!@brief	�R���X�g���N�^
PadInput::PadInput()
	: DIDeviceCaps()
	, joyBuf()
	, preJoyBuf()
{

}

//!@breif	�f�X�g���N�^
PadInput::~PadInput()
{
	for (padNo = 0; padNo < padNum; ++padNo)
	{
		//�p�b�h���ڑ�����ĂȂ���ΏI��
		if (!pad[padNo])
		{
			continue;
		}
		//���͂��󂯕t���Ȃ�
		pad[padNo]->Unacquire();
		Utility::SafeRelease(pad[padNo]);
	}
}

//!@brief	���̓p�b�h�̍쐬
//!@param[in]	hWnd	�E�B���h�E�n���h��
void	PadInput::CreatePadInput(const HWND& hWnd)
{
	for (padNo = 0; padNo < padNum; ++padNo)
	{
		if (FAILED(input.GetDirectInput()->EnumDevices(
			DI8DEVCLASS_GAMECTRL,
			EnumPadCallback,
			nullptr, DIEDFL_ATTACHEDONLY
		)))
		{
			continue;
		}
		//�擾�Ɏ��s
		if (!pad[padNo])
		{
			continue;
		}
		if (FAILED(pad[padNo]->SetDataFormat(&c_dfDIJoystick)))
		{
			continue;
		}
		if (FAILED(pad[padNo]->SetCooperativeLevel(
			hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND
		)))
		{
			continue;
		}
		DIDeviceCaps[padNo].dwSize = sizeof(DIDEVCAPS);
		if (FAILED(pad[padNo]->GetCapabilities(&DIDeviceCaps[padNo])))
		{
			continue;
		}
		if (FAILED(pad[padNo]->EnumObjects(
			EnumAxisCallback,
			hWnd, DIDFT_AXIS
		)))
		{
			continue;
		}
		if (FAILED(pad[padNo]->Poll()))
		{
			while (pad[padNo]->Acquire() == DIERR_INPUTLOST);
		}
	}
}

//!@brief	�X�V
void	PadInput::Run()
{
	for (padNo = 0; padNo < padNum; ++padNo) {
		//�p�b�h���擾���Ă��Ȃ���Ώ������s��Ȃ�
		if (!pad[padNo])
		{
			continue;
		}
		auto result = pad[padNo]->Acquire();

		if (result == DI_OK || S_FALSE)
		{
			if (SUCCEEDED(pad[padNo]->Poll()))
			{
				preJoyBuf[padNo] = joyBuf[padNo];
				pad[padNo]->GetDeviceState(sizeof(DIJOYSTATE), &joyBuf);
			}
		}
	}
}

//!@brief	������������
//!@param[in]	no	�p�b�h�ԍ�
//!@param[in]	key	���̓L�[
bool	PadInput::Press(const int no, const int key)
{
	if (!pad[0]) { return false; }
	unsigned char input = joyBuf[no].rgbButtons[key] & 0x80;
	return input != 0;
}

//!@brief	�c����Ă��邩����
//!@param[in]	no	�p�b�h�ԍ�
//!@param[in]	key	���̓L�[
bool	PadInput::Push(const int no, const int key)
{
	if (!pad[0]) { return false; }
	unsigned char input = joyBuf[no].rgbButtons[key] & 0x80;
	unsigned char preInput = preJoyBuf[no].rgbButtons[key] & 0x80;
	return input != 0 && preInput == 0;
}

//!@brief	������Ă��邩����
//!@param[in]	no	�p�b�h�ԍ�
//!@param[in]	key	���̓L�[
bool	PadInput::Free(const int no, const int key)
{
	unsigned char input = joyBuf[no].rgbButtons[key] & 0x80;
	return input == 0;
}

//!@brief	�����ꂽ������
//!@param[in]	no	�p�b�h�ԍ�
//!@param[in]	key	���̓L�[
bool	PadInput::Pull(const int no, const int key)
{
	unsigned char input = joyBuf[no].rgbButtons[key] & 0x80;
	unsigned char preInput = preJoyBuf[no].rgbButtons[key] & 0x80;
	return input == 0 && preInput != 0;
}

//!@brief	�\���L�[�̈ʒu���擾
//!@param[in]	no	�p�b�h�ԍ�
//!@return	�o�C�g�^�̈ʒu
BYTE	PadInput::GetPovPosition(const int no)
{
	if (!pad[0]) { return (BYTE)0xffffffff; }

	switch (joyBuf[no].rgbButtons[no])
	{
	case 0:		return PAD_UP;
	case 4500:	return PAD_UP | PAD_RIGHT;
	case 9000:	return PAD_RIGHT;
	case 13500:	return PAD_RIGHT | PAD_DOWN;
	case 18000:	return PAD_DOWN;
	case 22500:	return PAD_DOWN | PAD_LEFT;
	case 27000:	return PAD_LEFT;
	case 31500:	return PAD_LEFT | PAD_UP;
	}
	return (BYTE)0xffffffff;
}


//******************************************************************************
DXMouse	mouse;


DXMouse::DXMouse()
	: DIMouse(nullptr)
{
	position = { 0,0 };
	mouseState = { 0 };
}

DXMouse::~DXMouse()
{
	Utility::SafeRelease(DIMouse);
}


//!@brief	���̓}�E�X�f�o�C�X�̍쐬
//!@param[in]	hWnd	�n���h��
bool	DXMouse::CreateMouseInput(const HWND& hWnd)
{
	this->hWnd = hWnd;
	auto result = input.GetDirectInput()->CreateDevice(GUID_SysMouse, &DIMouse, nullptr);
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

	DIMouse->Acquire();
	return true;
}

//!@brief	�X�V
void	DXMouse::Run()
{
	DIMOUSESTATE	diMouseState;
	memcpy(&diMouseState, &mouseState, sizeof(diMouseState));
	auto result = DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState);
	if (result == DIERR_INPUTLOST)
	{
		DIMouse->Acquire();
		result = DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState);
	}
}

//!@brief	������Ă��邩����
bool	DXMouse::LButtonPush()
{
	if (mouseState.rgbButtons[0] & 0x80)
	{
		return true;
	}
	return false;
}

//!@brief	������Ă��邩����
bool	DXMouse::RButtonPush()
{
	if (mouseState.rgbButtons[1] & 0x80)
	{
		return true;
	}
	return false;
}

//!@brief	�}�E�X�J�[�\���̈ʒu�̎擾
//!@return	�}�E�X�J�[�\���̈ʒu
POINT	DXMouse::GetMousePos()
{
	GetCursorPos(&mouse.position);
	ScreenToClient(hWnd, &mouse.position);
	return mouse.position;
}