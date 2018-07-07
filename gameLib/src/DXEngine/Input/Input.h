#pragma once
#define DIRECTINPUT_VERSION 0x0800
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#include <dinput.h>


//------------------------------------------------------------------------------
//!@class		DirectInput
//!@brief	DirectInputを使用して入力処理を行う
//------------------------------------------------------------------------------
class Input
{
public:
	Input();
	~Input();

	//!@brief	入力の生成
	//!@param[in]	hWnd	ウィンドウハンドル
	bool	CreateInput(const HWND& hWnd);
	//!@brief	更新
	void	Run();
	//!@brief	押したか判定
	//!@return 押したなら true 押していないなら false
	bool	Press(const int key);
	//!@brief	押しているか判定
	//!@return 押しているなら true おしていないなら false
	bool	Push(const int key);
	//!@brief	押されていないか判定
	//!@return 押されていないなら true 押しているなら false
	bool	Free(const int key);
	//!@brief	離されたか判定
	//!@return 離されたなら true 離されていないなら false
	bool	Pull(const int key);

	//!@brief	DirectInputを返す
	//!@return DirectInputのポインタ
	LPDIRECTINPUT8	GetDirectInput() const;
	
private:
	LPDIRECTINPUT8			directInput;
	LPDIRECTINPUTDEVICE8	key;
	unsigned char buf[256];
	unsigned char preBuf[256];
	static const int MaxKey = 61;
	int	DIKeyCode[MaxKey];
};


//パッドの方向キー
#define PAD_UP	0x1
#define PAD_RIGHT 0x2
#define PAD_DOWN 0x4
#define PAD_LEFT 0x8


//------------------------------------------------------------------------------
//!@class		パッド
//!@brief	パッドを使用した入力を行う
//------------------------------------------------------------------------------
class PadInput
{
private:
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
	
public:
	PadInput();
	~PadInput();

	//!@brief	入力パッドの作成
	//!@param[in]	hWnd	ウィンドウハンドル
	void	CreatePadInput(const HWND& hWnd);
	//!@brief	更新
	void	Run();
	//!@brief	押したか判定
	//!@param[in]	no	パッド番号
	//!@param[in]	key	入力キー
	bool	Press(const int no, const int key);
	//!@brief	祖されているか判定
	//!@param[in]	no	パッド番号
	//!@param[in]	key	入力キー
	bool	Push(const int no, const int key);
	//!@brief	離されているか判定
	//!@param[in]	no	パッド番号
	//!@param[in]	key	入力キー
	bool	Free(const int no, const int key);
	//!@brief	離されたか判定
	//!@param[in]	no	パッド番号
	//!@param[in]	key	入力キー
	bool	Pull(const int no, const int key);

	//!@brief	十字キーの位置を取得
	//!@param[in]	no	パッド番号
	//!@return	バイト型の位置
	BYTE	GetPovPosition(const int no);

private:
	static int			padNo;
	static const int	padNum = 1;
	static LPDIRECTINPUTDEVICE8	pad[padNum];
	DIDEVCAPS			DIDeviceCaps[padNum];
	DIJOYSTATE			joyBuf[padNum];
	DIJOYSTATE			preJoyBuf[padNum];
};


//------------------------------------------------------------------------------
//!@class		DirectMouse
//!@brief	DirectXのマウスデバイスを使用し、マウス操作を行う
//------------------------------------------------------------------------------
class DXMouse
{
public:
	DXMouse();
	~DXMouse();

	//!@brief	入力マウスデバイスの作成
	//!@param[in]	hWnd	ハンドル
	bool	CreateMouseInput(const HWND& hWnd);
	//!@brief	更新
	void	Run();
	//!@brief	押されているか判定
	bool	LButtonPush();
	//!@brief	押されているか判定
	bool	RButtonPush();

	//!@brief	マウスカーソルの位置の取得
	//!@return	マウスカーソルの位置
	POINT	GetMousePos();

private:
	LPDIRECTINPUTDEVICE8	DIMouse;
	DIMOUSESTATE			mouseState;
	HWND					hWnd;
	POINT					position;
};


extern Input input;
extern PadInput pad;
extern DXMouse mouse;