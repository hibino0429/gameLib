#pragma once
#include "../../src/Interface/Input/Input2.h"
#include <array>
#include <Windows.h>
#include <Xinput.h>

#pragma comment(lib,"xinput.lib")

//----------------------------------------------------------------------------------------
//!@class		XInput
//!@brief	Xinputを利用して、入力を扱うクラス
//----------------------------------------------------------------------------------------
class XInput : public InputDevice
{
public:
	//!@brief	パッドの番号
	enum class PadNum
	{
		Pad0,
		Pad1,
		Pad2,
		Pad3
	};
public:
	//!@brief	コンストラクタ
	//!@brief	0～3までの番号を割り当てる
	//!@param[in]	controllerNumber	コントローラ番号
	XInput(const PadNum& padNum);
	//!@brief	デストラクタ
	~XInput();
public:
	//!@brief	コントローラーの状態の取得
	//!@return	XINPUT_STATE型
	const XINPUT_STATE&	GetState();
	//!@brief	コントローラが接続されているか確認
	//!@return	true: 接続されている false: 接続されていない
	bool	IsConnect();
	//!@brief	コントローラを振動させる
	//!@param[in]	leftVal	左への振動値
	//!@param[in]	rightVal 右への振動値
	void	Vibrate(int leftVal = 0, int rightVal = 0);
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
	XINPUT_STATE	controllerState;	//Xbox360コントローラの状態
	PadNum			controllerNumber;	//コントローラの番号
};