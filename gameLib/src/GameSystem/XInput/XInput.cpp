#include "XInput.h"


//!@brief	コンストラクタ
	//!@brief	1～4までの番号を割り当てる
	//!@param[in]	controllerNumber	コントローラ番号
XInput::XInput(const PadNum& padNum)
{
	this->controllerNumber = padNum;
}
//!@brief	デストラクタ
XInput::~XInput()
{
	//XInputEnable(false);	//振動を消す
}

//!@brief	コントローラーの状態の取得
//!@return	XINPUT_STATE型
const XINPUT_STATE&	XInput::GetState()
{
	std::memset(&controllerState, 0, sizeof(XINPUT_STATE));
	XInputGetState(static_cast<DWORD>(controllerNumber), &controllerState);
	return controllerState;
}

//!@brief	コントローラが接続されているか確認
//!@return	true: 接続されている false: 接続されていない
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

//!@brief	コントローラを振動させる
//!@param[in]	leftVal	左への振動値
//!@param[in]	rightVal 右への振動値
void	XInput::Vibrate(int leftVal, int rightVal)
{
	XINPUT_VIBRATION	vibration;
	std::memset(&vibration, 0, sizeof(XINPUT_VIBRATION));
	vibration.wLeftMotorSpeed = leftVal;
	vibration.wRightMotorSpeed = rightVal;
	XInputSetState(static_cast<DWORD>(controllerNumber), &vibration);
}


//!@brief	入力の生成
bool	XInput::CreateInput()
{
	return true;
}
//!@brief	更新
void	XInput::Run()
{

}
//!@brief	押しているか判定
//!@return 押しているなら true 押していないなら false
bool	XInput::Press(const int key)
{
	if (this->GetState().Gamepad.wButtons & key)
	{
		return true;
	}
	return false;
}
//!@brief	押したか判定
//!@return 押したなら true 押してないなら false
bool	XInput::Push(const int key)
{
	return true;
}
//!@brief	押されていないか判定
//!@return 押されていないなら true 押しているなら false
bool	XInput::Free(const int key)
{
	return true;
}
//!@brief	離されたか判定
//!@return 離されたなら true 離されていないなら false
bool	XInput::Release(const int key)
{
	return true;
}