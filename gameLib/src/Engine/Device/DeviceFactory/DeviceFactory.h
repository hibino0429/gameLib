#pragma once
#include <string>
#include "../../src/Engine/Device/Device.h"

//----------------------------------------------------------------
//�ǉ��̃f�o�C�X�C���N���[�h
#include "../../src/DXEngine/DXDevice/DXDevice.h"
#include "../../src/GLEngine/GLDevice/GLDevice.h"


//----------------------------------------------------------------
//!@class		DeviceFactory
//!@brief	�f�o�C�X�̐�����S��
//!@brief	1:DXDevice	2:GLDevice
//----------------------------------------------------------------
class DeviceFactory
{
public:
	//!@brief	�R���X�g���N�^
	DeviceFactory();
	//!@brief	�f�X�g���N�^
	~DeviceFactory();
	//!@brief	�f�o�C�X�̍쐬
	//!@param[in]	deviceName	�f�o�C�X��
	//!@return	device	���������f�o�C�X��Ԃ�
	Device*	Create(const std::string& deviceName,Screen* screen);
};