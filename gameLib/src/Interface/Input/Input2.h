#pragma once



//------------------------------------------------------------------------------
//!@class		InputDevice
//!@brief	入力デバイスを利用して、入力を行う
//!@brief	インターフェイスとして扱う
//------------------------------------------------------------------------------
class InputDevice
{
public:
	//!@brief	デストラクタ
	virtual ~InputDevice() {}
public:
	//!@brief	入力の生成
	virtual bool	CreateInput() = 0;
	//!@brief	更新
	virtual void	Run() = 0;
	//!@brief	押しているか判定
	//!@return 押しているなら true 押していないなら false
	virtual bool	Press(const int key) = 0;
	//!@brief	押したか判定
	//!@return 押したなら true 押してないなら false
	virtual bool	Push(const int key) = 0;
	//!@brief	押されていないか判定
	//!@return 押されていないなら true 押しているなら false
	virtual bool	Free(const int key) = 0;
	//!@brief	離されたか判定
	//!@return 離されたなら true 離されていないなら false
	virtual bool	Release(const int key) = 0;
};


//------------------------------------------
//!@class		InputEngine
//!@brief	入力処理の提供クラス
//------------------------------------------
class InputEngine
{
public:
	//!@brief	入力デバイスの登録
	//!@param[in]	inputDevice	入力デバイス
	static void Regist(InputDevice* inputDevice);
	//!@brief	入力デバイスの解除
	static void Release();

	//!@brief	入力デバイスの取得
	static InputDevice&	GetDevice();
private:
	static InputDevice*	device;
};


//------------------------------------------------------------------------------
//!@class		Input
//!@brief	入力を扱う
//------------------------------------------------------------------------------
class InputI
{
public:
	//!@brief	コンストラクタ
	//!@param[in]	入力デバイスのポインタ
	//!@detail
	//	Input* input = new Input(new XInput());
	//
	InputI(InputDevice* inputDevice);
	//!@brief	デストラクタ
	~InputI();
public:
	//!@brief	入力エンジンの取得
	//!@return	保持している入力エンジン
	const InputEngine&	GetInputEngine() const;
private:
	InputEngine*		inputEngine;
};


