#pragma once
#define DIRECTINPUT_VERSION 0x0800
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#include <dinput.h>


//---------------------------------------------------------------------------------
//!@class		DirectInput
//!@brief	DirectInputを利用した入力処理を扱う
//!@brief	DirectInputを扱うためのデバイスを管理
//---------------------------------------------------------------------------------
class DirectInput
{
public:
	//!@brief	コンストラクタ
	DirectInput();
	//!@brief	デストラクタ
	~DirectInput();
public:
	//!@brief	IDirectInput8オブジェクトの作成
	//!@return	true: 成功 false: 失敗
	static bool	CreateDirectInput(const HINSTANCE& hInstance);
	//!@brief	DirectInput8オブジェクトの取得
	//!@return	directInputオブジェクト
	static LPDIRECTINPUT8&	GetInstance();
private:
	static LPDIRECTINPUT8			directInput;
};




//---------------------------------------------------------------------------------
//!@class		DirectInputDevice
//!@brief	DirectInputのデバイスの抽象的な処理
//---------------------------------------------------------------------------------
class DirectInputDevice
{
protected:
	//!@brief	デバイスの作成
	virtual bool	CreateDevice() = 0;
	//!@brief	入力データ形式の設定
	virtual bool	SetDataFormat() = 0;
	//!@brief	排他制御
	virtual bool	SetCooperativeLevel(const HWND& hWnd) = 0;
	//!@brief	動作
	virtual void	Run() = 0;
	//!@brief	終了処理
	virtual void	Finalize() = 0;
};



