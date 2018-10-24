#include "DirectJoyStick.h"
#include "../../src/Utility/Utility.hpp"




//!@brief	コンストラクタ
DirectJoyStick::DirectJoyStick()
{
	
}
//!@brief	デストラクタ
DirectJoyStick::~DirectJoyStick()
{

}

//!@brief	ジョイスティックデバイスの取得
//!@return	joystickDevice
const LPDIRECTINPUTDEVICE8&	DirectJoyStick::GetJoystick() const
{
	return joystickDevice;
}

//!@brief	現在のジョイスティックの状態の取得
	//!@return	nowJoyState
const DIJOYSTATE&	DirectJoyStick::GetNowJoyState() const
{
	return nowJoyState;
}
//!@brief	1つ前のジョイスティックの状態の取得
//!@return	preJoyState
const DIJOYSTATE&	DirectJoyStick::GetPreJoyState() const
{
	return preJoyState;
}

//!@brief	デバイスの作成
bool	DirectJoyStick::CreateDevice()
{
	auto result = DirectInput::GetInstance()->CreateDevice(GUID_Joystick, &joystickDevice, nullptr);
	if (FAILED(result))
	{
		MessageBoxA(nullptr, "Joystickのデバイス作成に失敗", "DirectJoyStick::CreateDevice()", MB_OK);
		return false;
	}
	return true;
}
//!@brief	入力データ形式の設定
bool	DirectJoyStick::SetDataFormat()
{
	auto result = joystickDevice->SetDataFormat(&c_dfDIJoystick2);
	if (FAILED(result))
	{
		MessageBoxA(nullptr, "入力データ形式のセットに失敗", "DirectJoyStick::SetDataFormat()", MB_OK);
		joystickDevice->Release();
		return false;
	}
	return true;
}
//!@brief	排他制御
bool	DirectJoyStick::SetCooperativeLevel(const HWND& hWnd)
{
	auto result = joystickDevice->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(result))
	{
		MessageBoxA(nullptr, "排他制御に失敗", "DirectJoyStick::SetCooperativeLevel()", MB_OK);
		joystickDevice->Release();
		return false;
	}
	return true;
}
//!@brief	動作
void	DirectJoyStick::Run()
{
	//パッドを取得していなければ処理を行わない
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
//!@brief	終了処理
void	DirectJoyStick::Finalize()
{
	Utility::SafeRelease(joystickDevice);
}

//!@brief	ジョイスティックのデバイスの確保
bool	DirectJoyStick::SetEnumDevice()
{
	auto result = DirectInput::GetInstance()->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumPadCallback, nullptr, DIEDFL_ATTACHEDONLY);
	if (FAILED(result))
	{
		MessageBoxA(nullptr, "Joystickが見つかりません", "DirectJoyStick::CreateDevice()", MB_OK);
		return false;
	}
	return true;
}
//!@brief	ジョイスティックの入力を確認
bool	DirectJoyStick::CheckEnumObjects(const HWND& hWnd)
{
	auto result = joystickDevice->EnumObjects(EnumAxisCallback, (void*)hWnd, DIDFT_ALL);
	if (FAILED(result))
	{
		MessageBoxA(nullptr, "ジョイスティックオブジェクトの確認に失敗", "DirectJoyStick::EnumObjects()", MB_OK);
		return false;
	}
	return true;
}

//!@brief 接続されているpadを検知する
//!@param[in]	instance	入力デバイスのインスタンス
//!@param[in]	context	コンテキストのポインタ
BOOL CALLBACK DirectJoyStick::EnumPadCallback(const DIDEVICEINSTANCE* instance,void* pContext)
{
	//列挙されたジョイスティックへのインターフェイスを取得
	DirectJoyStick*	joystick = reinterpret_cast<DirectJoyStick*>(pContext);
	auto result = DirectInput::GetInstance()->CreateDevice(instance->guidInstance, &joystick->joystickDevice, nullptr);
	if (FAILED(result))
	{
		DirectInput::GetInstance()->Release();
		return DIENUM_CONTINUE;
	}
	
	//ジョイスティックの能力を確認
	joystick->deviceCaps.dwSize = sizeof(DIDEVCAPS);
	result = joystick->joystickDevice->GetCapabilities(&joystick->deviceCaps);
	if (FAILED(result))
	{
		DirectInput::GetInstance()->Release();
		return DIENUM_CONTINUE;
	}
	return DIENUM_STOP;
}
//!@brief	パッドの設定
//!@param[in]	objInstance オブジェクトインスタンス
//!@param[in]	context	コンテキストのポインタ
BOOL CALLBACK DirectJoyStick::EnumAxisCallback(const DIDEVICEOBJECTINSTANCE* objInstance,void* pContext)
{
	//軸範囲指定
	DIPROPRANGE prg;
	prg.diph.dwSize = sizeof(prg);
	prg.diph.dwHeaderSize = sizeof(prg);
	prg.diph.dwHow = DIPH_BYID;
	prg.diph.dwObj = objInstance->dwType;
	prg.lMin = 0 - 1000;	//傾き最小値
	prg.lMax = 0 + 1000;	//傾き最大値

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

