#include "WindowsInput.h"


//!@brief	コンストラクタ
WindowsInput::WindowsInput()
{
	preKey = -1;
	keyTable.fill(-1);
	frameCnt = 0;
}
//!@brief	デストラクタ
WindowsInput::~WindowsInput()
{

}
//!@brief	入力の生成
bool	WindowsInput::CreateInput()
{
	return true;
}
//!@brief	更新
void	WindowsInput::Run()
{
	GetKeyboardState(keyTable.data());
}

//!@brief	押しているか判定
//!@return 押しているなら true 押していないなら false
bool	WindowsInput::Press(const int key)
{
	if (keyTable[key] & 0x80)
	{
		preKey = keyTable[key];
		return true;
	}
	preKey = -1;
	return false;
}
//!@brief	押したか判定
//!@return 押したなら true 押してないなら false
bool	WindowsInput::Push(const int key)
{
	if (preKey == keyTable[key]) { return false; }
	if (keyTable[key] & 0x80)
	{
		preKey = keyTable[key];
		return true;
	}
	preKey = -1;
	return false;
}
//!@brief	押されていないか判定
//!@return 押されていないなら true 押しているなら false
bool	WindowsInput::Free(const int key)
{
	if (!Push(key) && !Press(key))
	{
		return true;
	}
	return false;
}
//!@brief	離されたか判定
//!@return 離されたなら true 離されていないなら false
bool	WindowsInput::Release(const int key)
{
	//前のキーと一致しなくなった
	//ボタンが押されているか
	if (preKey == keyTable[key]) { return false; }
	//未実装
	return false;
}