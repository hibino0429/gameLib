#include "DeviceFactory.h"


//コンストラクタ
DeviceFactory::DeviceFactory()
{

}

//デストラクタ
DeviceFactory::~DeviceFactory()
{

}


//!@brief	デバイスの作成
//!@param[in]	deviceName	デバイス名
//!@return	device	生成したデバイスを返す
Device*	DeviceFactory::Create(const std::string& deviceName, Screen* screen)
{
	if (deviceName == "DXDevice")
	{
		return new DXDevice(screen);
	}
	else if (deviceName == "GLDevice")
	{
		//return new GLDevice();
		return new DXDevice(screen);
	}
	
	//デバイスの生成に失敗
	return nullptr;
}