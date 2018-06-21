#pragma once

//-------------------------------------------------------------
//�ǉ�����f�o�C�X�N���X



//-------------------------------------------------------------
//!@class		Device
//!@brief �f�o�C�X�̃C���^�[�t�F�C�X
//-------------------------------------------------------------
class Device
{
public:
	//!@brief �f�X�g���N�^
	virtual ~Device() {};

	virtual bool	Create() = 0;
	virtual bool	Run() = 0;
	virtual	bool	CleanUp() = 0;
	virtual bool	Remove() = 0;
	virtual Device*	GetDevice() = 0;
};
