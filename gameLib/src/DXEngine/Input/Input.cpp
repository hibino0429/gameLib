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

//!@brief	入力の生成
//!@param[in]	hWnd	ウィンドウハンドル
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

	//デバイスの取得
	result = directInput->CreateDevice(
		GUID_SysKeyboard,
		&key,
		nullptr
	);
	if (FAILED(result))
	{
		return false;
	}

	//入力データフォーマット
	result = key->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		return false;
	}

	//排他制御
	result = key->SetCooperativeLevel(
		hWnd,
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY
	);
	if (FAILED(result))
	{
		return false;
	}
	//動作開始
	key->Acquire();
	int	keyList[MaxKey] =
	{
		DIK_UP,				//↑				
		DIK_LEFT,			//←
		DIK_RIGHT,			//→			
		DIK_DOWN,			//↓
		DIK_ESCAPE,			//Esc
		DIK_RETURN,	        //Enter
		DIK_LSHIFT,	        //Shift(左)	
		DIK_RSHIFT,			//Shift(右)
		DIK_LCONTROL,	    //Ctrl(左)
		DIK_RCONTROL,	    //Ctrl(右)					
		DIK_LMENU,			//Alt(左)
		DIK_RMENU,			//Alt(右)
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

//!@brief	更新
void	Input::Run()
{
	for (int i = 0; i < 256; ++i)
	{
		preBuf[i] = buf[i];
	}

	auto result = key->GetDeviceState(sizeof(buf), &buf);
	if (FAILED(result))
	{
		//再設定
		key->Acquire();
		key->GetDeviceState(sizeof(buf), &buf);
	}
}


//!@brief	押したか判定
//!@return 押したなら true 押していないなら false
bool	Input::Press(const int key)
{
	unsigned char input = 0x00;
	unsigned char preInput = 0x00;
	input = buf[DIKeyCode[key]] & 0x80;
	preInput = preBuf[DIKeyCode[key]] & 0x80;

	return input != 0 && preInput == 0;
}

//!@brief	押しているか判定
//!@return 押しているなら true おしていないなら false
bool	Input::Push(const int key)
{
	unsigned char input = 0x00;
	input = buf[DIKeyCode[key]] & 0x80;
	return input != 0;
}

//!@brief	押されていないか判定
//!@return 押されていないなら true 押しているなら false
bool	Input::Free(const int key)
{
	unsigned char input = 0x00;
	input = buf[DIKeyCode[key]] & 0x80;
	return input == 0;
}

//!@brief	離されたか判定
//!@return 離されたなら true 離されていないなら false
bool	Input::Pull(const int key)
{
	unsigned char input = 0x00;
	unsigned char preInput = 0x00;
	input = buf[DIKeyCode[key]] & 0x80;
	preInput = preBuf[DIKeyCode[key]] & 0x80;

	return input == 0 && preInput != 0;
}

//!@brief	DirectInputを返す
//!@return DirectInputのポインタ
LPDIRECTINPUT8	Input::GetDirectInput() const
{
	return directInput;
}


//***********************************************************************************
PadInput	pad;

//static変数の実体
int PadInput::padNo = 0;
LPDIRECTINPUTDEVICE8	PadInput::pad[PadInput::padNum] =
{
	nullptr
};

//!@brief 接続されているpadを検知する
//!@param[in]	instance	入力デバイスのインスタンス
//!@param[in]	context	コンテキストのポインタ
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

//!@brief	パッドの設定
//!@param[in]	objInstance オブジェクトインスタンス
//!@param[in]	context	コンテキストのポインタ
BOOL CALLBACK PadInput::EnumAxisCallback(
	const DIDEVICEOBJECTINSTANCE* objInstance,
	void* pContext)
{
	//軸範囲指定
	DIPROPRANGE prg;
	prg.diph.dwSize = sizeof(prg);
	prg.diph.dwHeaderSize = sizeof(prg);
	prg.diph.dwHow = DIPH_BYID;
	prg.diph.dwObj = objInstance->dwType;
	prg.lMin = -1000;	//傾き最小値
	prg.lMax = 1000;	//傾き最大値

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

//!@brief	コンストラクタ
PadInput::PadInput()
	: DIDeviceCaps()
	, joyBuf()
	, preJoyBuf()
{

}

//!@breif	デストラクタ
PadInput::~PadInput()
{
	for (padNo = 0; padNo < padNum; ++padNo)
	{
		//パッドが接続されてなければ終了
		if (!pad[padNo])
		{
			continue;
		}
		//入力を受け付けない
		pad[padNo]->Unacquire();
		Utility::SafeRelease(pad[padNo]);
	}
}

//!@brief	入力パッドの作成
//!@param[in]	hWnd	ウィンドウハンドル
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
		//取得に失敗
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

//!@brief	更新
void	PadInput::Run()
{
	for (padNo = 0; padNo < padNum; ++padNo) {
		//パッドを取得していなければ処理を行わない
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

//!@brief	押したか判定
//!@param[in]	no	パッド番号
//!@param[in]	key	入力キー
bool	PadInput::Press(const int no, const int key)
{
	if (!pad[0]) { return false; }
	unsigned char input = joyBuf[no].rgbButtons[key] & 0x80;
	return input != 0;
}

//!@brief	祖されているか判定
//!@param[in]	no	パッド番号
//!@param[in]	key	入力キー
bool	PadInput::Push(const int no, const int key)
{
	if (!pad[0]) { return false; }
	unsigned char input = joyBuf[no].rgbButtons[key] & 0x80;
	unsigned char preInput = preJoyBuf[no].rgbButtons[key] & 0x80;
	return input != 0 && preInput == 0;
}

//!@brief	離されているか判定
//!@param[in]	no	パッド番号
//!@param[in]	key	入力キー
bool	PadInput::Free(const int no, const int key)
{
	unsigned char input = joyBuf[no].rgbButtons[key] & 0x80;
	return input == 0;
}

//!@brief	離されたか判定
//!@param[in]	no	パッド番号
//!@param[in]	key	入力キー
bool	PadInput::Pull(const int no, const int key)
{
	unsigned char input = joyBuf[no].rgbButtons[key] & 0x80;
	unsigned char preInput = preJoyBuf[no].rgbButtons[key] & 0x80;
	return input == 0 && preInput != 0;
}

//!@brief	十字キーの位置を取得
//!@param[in]	no	パッド番号
//!@return	バイト型の位置
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


//!@brief	入力マウスデバイスの作成
//!@param[in]	hWnd	ハンドル
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
	diprop.dwData = DIPROPAXISMODE_REL;	// 相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）
	if (FAILED(result))
	{
		return false;
	}

	DIMouse->Acquire();
	return true;
}

//!@brief	更新
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

//!@brief	押されているか判定
bool	DXMouse::LButtonPush()
{
	if (mouseState.rgbButtons[0] & 0x80)
	{
		return true;
	}
	return false;
}

//!@brief	押されているか判定
bool	DXMouse::RButtonPush()
{
	if (mouseState.rgbButtons[1] & 0x80)
	{
		return true;
	}
	return false;
}

//!@brief	マウスカーソルの位置の取得
//!@return	マウスカーソルの位置
POINT	DXMouse::GetMousePos()
{
	GetCursorPos(&mouse.position);
	ScreenToClient(hWnd, &mouse.position);
	return mouse.position;
}