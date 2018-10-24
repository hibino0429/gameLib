#include "DirectPad.h"
#include "../../src/Utility/Utility.hpp"




//!@brief	押しているか判定
//!@return 押しているなら true 押していないなら false
bool	DirectPad::Press(const Pad& padNum, const Button& key)
{
	unsigned char input = this->joystick[static_cast<unsigned int>(padNum)].GetNowJoyState().rgbButtons[(unsigned int)key] & 0x80;
	return input != 0;
}
//!@brief	押したか判定
//!@return 押したなら true 押してないなら false
bool	DirectPad::Push(const Pad& padNum, const Button& key)
{
	unsigned char input = joystick[static_cast<unsigned int>(padNum)].GetNowJoyState().rgbButtons[static_cast<unsigned int>(key)] & 0x80;
	unsigned char preInput = joystick[static_cast<unsigned int>(padNum)].GetPreJoyState().rgbButtons[static_cast<unsigned int>(key)] & 0x80;
	return input != 0 && preInput == 0;
}
//!@brief	押されていないか判定
//!@return 押されていないなら true 押しているなら false
bool	DirectPad::Free(const Pad& padNum, const Button& key)
{
	unsigned char input = joystick[static_cast<unsigned int>(padNum)].GetNowJoyState().rgbButtons[static_cast<unsigned int>(key)] & 0x80;
	return input == 0;
}
//!@brief	離されたか判定
//!@return 離されたなら true 離されていないなら false
bool	DirectPad::Release(const Pad& padNum, const Button& key)
{
	unsigned char input = joystick[static_cast<unsigned int>(padNum)].GetNowJoyState().rgbButtons[static_cast<unsigned int>(key)] & 0x80;
	unsigned char preInput = joystick[static_cast<unsigned int>(padNum)].GetPreJoyState().rgbButtons[static_cast<unsigned int>(key)] & 0x80;
	return input == 0 && preInput != 0;
}

//!@brief	十字キーの位置を取得
//!@param[in]	padNo	パッド番号
//!@return	バイト型の位置
BYTE	DirectPad::GetPovPosition(const Pad& padNo)
{
	switch (joystick[static_cast<unsigned int>(padNo)].GetNowJoyState().rgbButtons[static_cast<unsigned int>(padNo)])
	{
	case 0:		return (BYTE)Axis::Up;
	case 4500:	return (BYTE)Axis::Up | (BYTE)Axis::Right;
	case 9000:	return (BYTE)Axis::Right;
	case 13500:	return (BYTE)Axis::Right | (BYTE)Axis::Down;
	case 18000:	return (BYTE)Axis::Down;
	case 22500:	return (BYTE)Axis::Down | (BYTE)Axis::Left;
	case 27000:	return (BYTE)Axis::Left;
	case 31500:	return (BYTE)Axis::Left | (BYTE)Axis::Up;
	}
	return (BYTE)0xffffffff;
}