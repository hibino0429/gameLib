#include "Input2.h"


InputDevice* InputEngine::device = nullptr;

//!@brief	入力デバイスの登録
//!@param[in]	inputDevice	入力デバイス
void InputEngine::Regist(InputDevice* inputDevice)
{
	device = inputDevice;
}
//!@brief	入力デバイスの解除
void InputEngine::Release()
{
	if (device != nullptr)
	{
		delete device;
		device = nullptr;
	}
}

//!@brief	入力デバイスの取得
InputDevice&	InputEngine::GetDevice()
{
	return *device;
}




//!@brief	コンストラクタ
//!@param[in]	入力デバイスのポインタ
InputI::InputI(InputDevice* inputDevice)
{
	inputEngine->Regist(inputDevice);
}

//!@brief	デストラクタ
InputI::~InputI()
{
	inputEngine->Release();
}

//!@brief	入力エンジンの取得
//!@return	保持している入力エンジン
const InputEngine&	InputI::GetInputEngine() const
{
	return *inputEngine;
}
