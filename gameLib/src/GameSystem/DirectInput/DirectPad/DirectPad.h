#pragma once
#include "../../src/GameSystem/DirectInput/DirectInput.h"
#include "../../src/GameSystem/DirectInput/DirectPad/DirectJoyStick/DirectJoyStick.h"

#define MaxPadNum 4
//------------------------------------------------------------------------------
//!@class		DirectPad
//!@brief	DirectJoystickを複数保有して、ジョイスティックを扱う
//------------------------------------------------------------------------------
class DirectPad
{
public:
	//!@brief	パッド番号
	enum class Pad
	{
		No0 = 0,
		No1,
		No2,
		No3
	};
	//!@brief	パッドボタン
	enum class Button
	{
		X,
		Y,
		A,
		B,
		R1,
		R2,
		R3,
		L1,
		L2,
		L3,
	};
	//!@brief	パッド軸
	enum class Axis
	{
		Up = 0x1,
		Right = 0x2,
		Down = 0x4,
		Left = 0x8
	};
public:
	//!@brief	押しているか判定
	//!@return 押しているなら true 押していないなら false
	bool	Press(const Pad& padNum,const Button& key);
	//!@brief	押したか判定
	//!@return 押したなら true 押してないなら false
	bool	Push(const Pad& padNum, const Button& key);
	//!@brief	押されていないか判定
	//!@return 押されていないなら true 押しているなら false
	bool	Free(const Pad& padNum, const Button& key);
	//!@brief	離されたか判定
	//!@return 離されたなら true 離されていないなら false
	bool	Release(const Pad& padNum, const Button& key);
	//!@brief	十字キーの位置を取得
	//!@param[in]	no	パッド番号
	//!@return	バイト型の位置
	BYTE	GetPovPosition(const Pad& padNo);
private:
	std::array<DirectJoyStick, MaxPadNum>	joystick;		//ジョイスティック
	Pad										nowPadNo;		//現在のパッド番号
};




