#pragma once
#include <string>
#include "../../src/Device/Device.h"

//----------------------------------------------------------------
//追加のデバイスインクルード
#include "../../src/Device/DXDevice/DXDevice.h"
#include "../../src/Device/GLDevice/GLDevice.h"


//----------------------------------------------------------------
//!@class		DeviceFactory
//!@brief	デバイスの生成を担当
//!@brief	1:DXDevice	2:GLDevice
//----------------------------------------------------------------
class DeviceFactory
{
public:
	//!@brief	コンストラクタ
	DeviceFactory();
	//!@brief	デストラクタ
	~DeviceFactory();
	//!@brief	デバイスの作成
	//!@param[in]	deviceName	デバイス名
	//!@return	device	生成したデバイスを返す
	Device*	Create(const std::string& deviceName,Screen* screen);
};