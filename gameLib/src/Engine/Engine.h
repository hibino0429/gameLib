#pragma once
#include "../../src/Device/Device.h"
#include <string>


//----------------------------------------------------------------------------------------
//!@class		Engine
//!@brief	�Q�[���G���W�������������܂�
//!@brief	�f�o�C�X�𗘗p���āA�`�擙�̑�����s���܂�
//----------------------------------------------------------------------------------------
template <typename Type>
class Engine
{
public:
	//!@brief	�f�X�g���N�^
	virtual ~Engine() {  };

	//!@brief	�f�o�C�X�̎擾
	//!@return	device �f�o�C�X��Ԃ�
	static Type&	GetDevice()
	{
		return *device;
	}
	//!@brief	�f�o�C�X�̓o�^
	//!@param[in]	device
	//!@return �o�^�ɐ�������� true ���s����� false
	static bool	RegistDevice(Type* registDevice)
	{
		//���łɃf�o�C�X���o�^����Ă���Ȃ�Afalse�ɂ���
		//�r���Ńf�o�C�X��ύX����ꍇ�����邽�߁A�����͖���
		if (device != nullptr) { return false; }
		device = registDevice;
		return true;
	}

private:
	static Type*	device;
};


template<typename Type>
Type*	Engine<Type>::device = nullptr;