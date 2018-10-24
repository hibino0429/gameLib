#pragma once
#include "../../src/GameSystem/DirectInput/DirectInput.h"
#include <array>



//------------------------------------------------------------------------------
//!@class		DirectJoyStick
//!@brief	DirectInputを利用してJoyStickでの操作を扱う
//!@brief	扱うのはジョイスティック1つ
//------------------------------------------------------------------------------
class DirectJoyStick : private DirectInputDevice
{
public:
	//!@brief	コンストラクタ
	DirectJoyStick();
	//!@brief	デストラクタ
	~DirectJoyStick();
public:
	//!@brief	ジョイスティックデバイスの取得
	//!@return	joystickDevice
	const LPDIRECTINPUTDEVICE8&	GetJoystick() const;
	//!@brief	現在のジョイスティックの状態の取得
	//!@return	nowJoyState
	const DIJOYSTATE&	GetNowJoyState() const;
	//!@brief	1つ前のジョイスティックの状態の取得
	//!@return	preJoyState
	const DIJOYSTATE&	GetPreJoyState() const;
private:
	//!@brief	デバイスの作成
	bool	CreateDevice() override;
	//!@brief	入力データ形式の設定
	bool	SetDataFormat() override;
	//!@brief	排他制御
	bool	SetCooperativeLevel(const HWND& hWnd) override;
	//!@brief	動作
	void	Run() override;
	//!@brief	終了処理
	void	Finalize() override;
	//!@brief	ジョイスティックのデバイスの確保
	bool	SetEnumDevice();
	//!@brief	ジョイスティックの入力を確認
	bool	CheckEnumObjects(const HWND& hWnd);

	//!@brief 接続されているpadを検知する
	//!@param[in]	instance	入力デバイスのインスタンス
	//!@param[in]	context	コンテキストのポインタ
	static BOOL CALLBACK EnumPadCallback(
		const DIDEVICEINSTANCE* instance,
		void* pContext
	);
	//!@brief	パッドの設定
	//!@param[in]	objInstance オブジェクトインスタンス
	//!@param[in]	context	コンテキストのポインタ
	static BOOL CALLBACK EnumAxisCallback(
		const DIDEVICEOBJECTINSTANCE* objInstance,
		void* pContext);

private:
	LPDIRECTINPUTDEVICE8	joystickDevice;
	DIDEVCAPS				deviceCaps;		//ジョイスティックの能力
	DIJOYSTATE				nowJoyState;	//現在のジョイスティックの状態
	DIJOYSTATE				preJoyState;	//１つ前のジョイスティックの状態
};


