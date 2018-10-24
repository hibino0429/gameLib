#pragma once
#include "../../src/GameSystem/DirectInput/DirectInput.h"
#include <iostream>


//--------------------------------------------------------------------------------
//!@class		DirectKey
//!@brief	DirectInputを利用してキーボードを扱う
//--------------------------------------------------------------------------------
class DirectKey 
{
public:
	//!@brief	キー
	enum class Key
	{
		Up			= DIK_UP,			//↑				
		Left		= DIK_LEFT,			//←
		Right		= DIK_RIGHT,		//→			
		Down		= DIK_DOWN,			//↓
		Escape		= DIK_ESCAPE,		//Esc
		Return		= DIK_RETURN,	    //Enter
		LeftShift	= DIK_LSHIFT,	    //Shift(左)	
		RightShift	= DIK_RSHIFT,		//Shift(右)
		LeftCtrl	= DIK_LCONTROL,	    //Ctrl(左)
		RightCtrl	= DIK_RCONTROL,	    //Ctrl(右)					
		LeftAlt		= DIK_LMENU,		//Alt(左)
		RightAlt	= DIK_RMENU,		//Alt(右)
		Space		= DIK_SPACE,		//Space
		BackSpace	= DIK_BACK,			//Back Space
		Tab			= DIK_TAB,			//Tab
		Num1		= DIK_1,     		//1
		Num2		= DIK_2,     		//2
		Num3		= DIK_3,     		//3
		Num4		= DIK_4,     		//4
		Num5		= DIK_5,     		//5
		Num6		= DIK_6,     		//6
		Num7		= DIK_7,     		//7
		Num8		= DIK_8,     		//8
		Num9		= DIK_9,     		//9
		Num0		= DIK_0,     		//0
		Q			= DIK_Q,			//Q
		W			= DIK_W,			//W
		E			= DIK_E,			//E
		R			= DIK_R,			//R
		T			= DIK_T,			//T
		Y			= DIK_Y,			//Y
		U			= DIK_U,			//U
		I			= DIK_I,			//I
		O			= DIK_O,			//O
		P			= DIK_P,			//P
		A			= DIK_A,			//A
		S			= DIK_S,			//S
		D			= DIK_D,			//D
		F			= DIK_F,			//F
		G			= DIK_G,			//G
		H			= DIK_H,			//H
		J			= DIK_J,			//J
		K			= DIK_K,			//K
		L			= DIK_L,			//L
		Z			= DIK_Z,			//Z
		X			= DIK_X,			//X
		C			= DIK_C,			//C
		V			= DIK_V,			//V
		B			= DIK_B,			//B
		N			= DIK_N,			//N
		M			= DIK_M,			//M			
		F1			= DIK_F1,			//F1
		F2			= DIK_F2,			//F2
		F3			= DIK_F3,			//F3
		F4			= DIK_F4,			//F4
		F5			= DIK_F5,			//F5
		F6			= DIK_F6,			//F6
		F7			= DIK_F7,			//F7
		F8			= DIK_F8,			//F8
		F9			= DIK_F9,			//F9
		F10			= DIK_F10,			//F10
	};
private:
	class KeyBoardDevice
	{
	public:
		//!@brief	コンストラクタ
		KeyBoardDevice(const HWND& hWnd);
		//!@brief	デストラクタ
		~KeyBoardDevice();
	public:
		//!@brief	デバイスの作成
		static bool	CreateDevice();
		//!@brief	入力データ形式の設定
		static bool	SetDataFormat();
		//!@brief	排他制御
		static bool	SetCooperativeLevel(const HWND& hWnd);
		//!@brief	終了
		static void	Finalize();
	public:
		//!@brief	動作
		static void	Run();
	public:
		//!@brief	押しているか判定
		//!@param[in]	key	キー
		static bool	Press(const unsigned char& key);
		//!@brief	押されたか判定
		//!@param[in]	key	キー
		static bool	Push(const unsigned char& key);
		//!@brief	離されているか
		//!@param[in]	key	キー
		static bool	Free(const unsigned char& key);
		//!@brief	離されたか判定
		//!@param[in]	key	キー
		static bool	Release(const unsigned char& key);
	private:
		static LPDIRECTINPUTDEVICE8		keyDevice;
		static unsigned char			nowKey[256];
		static unsigned char			preKey[256];
	};
public:
	//!@brief	コンストラクタ
	DirectKey(const HWND& hWnd);
	//!@brief	デストラクタ
	~DirectKey();
public:
	//!@brief	動作
	void	Run();
	//!@brief	押しているか判定
	//!@param[in]	key	キー
	bool	Press(const Key& key);
	//!@brief	押されたか判定
	//!@param[in]	key	キー
	bool	Push(const Key& key);
	//!@brief	離されているか
	//!@param[in]	key	キー
	bool	Free(const Key& key);
	//!@brief	離されたか判定
	//!@param[in]	key	キー
	bool	Release(const Key& key);
private:
	KeyBoardDevice			keyDevice;
};




