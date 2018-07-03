#pragma once
#include "../../src/Device/Device.h"
#include "../../src/Device/DXDevice/DXDevice.h"
#include "../../src/Device/GLDevice/GLDevice.h"

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

//------------------------------------------------------
//追加エンジン
//template<> 
//class Engine<DXDevice>
//{
//public:
//	//!@brief	デストラクタ
//	virtual ~Engine() {  };
//
//	//!@brief	デバイスの取得
//	//!@return	device デバイスを返す
//	static DXDevice&	GetDevice()
//	{
//		return *device;
//	}
//	//!@brief	デバイスの登録
//	//!@param[in]	device
//	//!@return 登録に成功すると true 失敗すると false
//	static bool	RegistDevice(DXDevice* registDevice)
//	{
//		//すでにデバイスが登録されているなら、falseにする
//		//途中でデバイスを変更する場合があるため、ここは未定
//		if (device != nullptr) { return false; }
//		device = registDevice;
//		return true;
//	}
//
//private:
//	static DXDevice*	device;
//};
//
//template<>
//class Engine<GLDevice>
//{
//public:
//	//!@brief	デストラクタ
//	virtual ~Engine() {  };
//
//	//!@brief	デバイスの取得
//	//!@return	device デバイスを返す
//	static GLDevice&	GetDevice()
//	{
//		return *device;
//	}
//	//!@brief	デバイスの登録
//	//!@param[in]	device
//	//!@return 登録に成功すると true 失敗すると false
//	static bool	RegistDevice(GLDevice* registDevice)
//	{
//		//すでにデバイスが登録されているなら、falseにする
//		//途中でデバイスを変更する場合があるため、ここは未定
//		if (device != nullptr) { return false; }
//		device = registDevice;
//		return true;
//	}
//
//private:
//	static GLDevice*	device;
//};
//
//
//DXDevice*	Engine<DXDevice>::device = nullptr;
//GLDevice*	Engine<GLDevice>::device = nullptr;

