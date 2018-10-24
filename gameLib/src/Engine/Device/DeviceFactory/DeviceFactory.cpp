#include "DeviceFactory.h"


//�R���X�g���N�^
DeviceFactory::DeviceFactory()
{

}

//�f�X�g���N�^
DeviceFactory::~DeviceFactory()
{

}


//!@brief	�f�o�C�X�̍쐬
//!@param[in]	deviceName	�f�o�C�X��
//!@return	device	���������f�o�C�X��Ԃ�
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
	
	//�f�o�C�X�̐����Ɏ��s
	return nullptr;
}