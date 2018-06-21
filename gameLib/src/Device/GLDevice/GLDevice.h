#pragma once
#include "../../src/Device/Device.h"

//-------------------------------------------------------------
//!@class		GLDevice
//!@brief	OpenGL�̃f�o�C�X��񋟂��܂�
//!@brief	�f�o�C�X�̍쐬��A�@�\�̒񋟂Ȃǂ��s���܂�
//-------------------------------------------------------------
class GLDevice : public Device
{
public:
	//!@brief �R���X�g���N�^
	GLDevice();
	//!@brief �f�X�g���N�^
	virtual ~GLDevice();

public:
	//!@brief ����
	bool	Create();
	//!@brief �X�V
	void	Run();
	//!@brief �I��
	bool	CleanUp();
	//!@brief ����
	bool	Remove();

};

