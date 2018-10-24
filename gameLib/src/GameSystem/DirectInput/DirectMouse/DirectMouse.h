#pragma once
#include "../../src/GameSystem/DirectInput/DirectInput.h"

//------------------------------------------------------------------------------
//!@class		DirectMouse
//!@brief	DirectXのマウスデバイスを使用し、マウス操作を行う
//------------------------------------------------------------------------------
class DirectMouse
{
private:
	//!@brief	マウスボタン
	enum class Button
	{
		Left,
		Right
	};
public:
	//!@brief	コンストラクタ
	//!@param[in]	hWnd	ウィンドウハンドル
	DirectMouse(const HWND& hWnd);
	//!@brief	デストラクタ
	~DirectMouse();
private:
	//!@brief	入力マウスデバイスの作成
	//!@param[in]	hWnd	ハンドル
	bool	CreateMouseInput(const HWND& hWnd);
public:
	//!@brief	更新
	void	Run();
	//!@brief	押されているか判定
	bool	LButtonPush();
	//!@brief	押されているか判定
	bool	RButtonPush();
	//!@brief	マウスカーソルの位置の取得
	//!@return	マウスカーソルの位置
	POINT	GetMousePos();
	//!@brief	ホイールが回転しているか
	bool	WheelRotation();
	//!@brief	上回転したかの判定
	bool	UpWheelRotation();
	//!@brief	下回転したかの判定
	bool	DownWheelRotation();
private:
	LPDIRECTINPUTDEVICE8	DIMouse;
	DIMOUSESTATE			mouseState;
	HWND					hWnd;
	POINT					position;
};

