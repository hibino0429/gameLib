#pragma once
#include "../../src/Device/Device.h"
#include <string>


//----------------------------------------------------------------------------------------
//!@class		Engine
//!@brief	ゲームエンジン部分を扱います
//!@brief	デバイスを利用して、描画等の操作を行います
//----------------------------------------------------------------------------------------
template <typename Type>
class Engine
{
public:
	//!@brief	デストラクタ
	virtual ~Engine() {  };

	//!@brief	デバイスの取得
	//!@return	device デバイスを返す
	static Type&	GetDevice()
	{
		return *device;
	}
	//!@brief	デバイスの登録
	//!@param[in]	device
	//!@return 登録に成功すると true 失敗すると false
	static bool	RegistDevice(Type* registDevice)
	{
		//すでにデバイスが登録されているなら、falseにする
		//途中でデバイスを変更する場合があるため、ここは未定
		if (device != nullptr) { return false; }
		device = registDevice;
		return true;
	}

private:
	static Type*	device;
};


template<typename Type>
Type*	Engine<Type>::device = nullptr;