#pragma once
#include "../../src/Interface/Input/Input2.h"
#include <array>
#include <Windows.h>

//----------------------------------------------------------------------------------------
//!@class		WindowsInput
//!@brief	ウィンドウズが用意している入力
//----------------------------------------------------------------------------------------
class WindowsInput : public InputDevice
{
public:
	//!@brief	コンストラクタ
	WindowsInput();
	//!@brief	デストラクタ
	~WindowsInput();
public:
	//!@brief	入力の生成
	bool	CreateInput() override;
	//!@brief	更新
	void	Run() override;
	//!@brief	押しているか判定
	//!@return 押しているなら true 押していないなら false
	bool	Press(const int key) override;
	//!@brief	押したか判定
	//!@return 押したなら true 押してないなら false
	bool	Push(const int key) override;
	//!@brief	押されていないか判定
	//!@return 押されていないなら true 押しているなら false
	bool	Free(const int key) override;
	//!@brief	離されたか判定
	//!@return 離されたなら true 離されていないなら false
	bool	Release(const int key) override;
private:
	std::array<BYTE, 256>	keyTable;
	BYTE					preKey;
	int						frameCnt;
};