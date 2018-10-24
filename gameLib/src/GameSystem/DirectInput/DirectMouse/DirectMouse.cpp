#include "DirectMouse.h"
#include "../../src/Utility/Utility.hpp"


//!@brief	コンストラクタ
//!@param[in]	hWnd	ウィンドウハンドル
DirectMouse::DirectMouse(const HWND& hWnd)
	: DIMouse(nullptr)
{
	position = { 0,0 };
	mouseState = { 0 };
	CreateMouseInput(hWnd);
}
//!@brief	デストラクタ
DirectMouse::~DirectMouse()
{
	Utility::SafeRelease(DIMouse);
}


//!@brief	入力マウスデバイスの作成
//!@param[in]	hWnd	ハンドル
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
	//デバイスの設定
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
	//入力制御開始
	DIMouse->Acquire();
	return true;
}

//!@brief	更新
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

//!@brief	押されているか判定
bool	DirectMouse::LButtonPush()
{
	if (mouseState.rgbButtons[static_cast<unsigned int>(Button::Left)] & 0x80)
	{
		return true;
	}
	return false;
}

//!@brief	押されているか判定
bool	DirectMouse::RButtonPush()
{
	if (mouseState.rgbButtons[static_cast<unsigned int>(Button::Right)] & 0x80)
	{
		return true;
	}
	return false;
}

//!@brief	マウスカーソルの位置の取得
//!@return	マウスカーソルの位置
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





