#include "DirectInput.h"
#include "../../src/Utility/Utility.hpp"



////////////////////////////////////////////////////////////////////////////
//static変数
LPDIRECTINPUT8 DirectInput::directInput = nullptr;



//!@brief	コンストラクタ
DirectInput::DirectInput()
{
	
}
//!@brief	デストラクタ
DirectInput::~DirectInput()
{
	Utility::SafeRelease(directInput);
}

//!@brief	IDirectInput8オブジェクトの作成
//!@return	true: 成功 false: 失敗
bool	DirectInput::CreateDirectInput(const HINSTANCE& hInstance)
{
	auto	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&directInput, nullptr);
	if (FAILED(result))
	{
		MessageBoxA(nullptr, "DirectInput8の作成に失敗しました", "CreateDirectInput()", MB_OK);
		return false;
	}
	return true;
}

//!@brief	DirectInput8オブジェクトの取得
//!@return	directInputオブジェクト
LPDIRECTINPUT8&	DirectInput::GetInstance()
{
	return  directInput;
}

