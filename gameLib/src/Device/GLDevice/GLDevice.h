#pragma once


//-------------------------------------------------------------
//!@class		GLDevice
//!@brief	OpenGL�̃f�o�C�X��񋟂��܂�
//!@brief	�f�o�C�X�̍쐬��A�@�\�̒񋟂Ȃǂ��s���܂�
//-------------------------------------------------------------
class GLDevice
{
public:
	//!@brief �R���X�g���N�^
	GLDevice();
	//!@brief �f�X�g���N�^
	virtual ~GLDevice();

public:
	//!@brief	��������
	bool	Create();
	//!@brief	�������
	bool	Release();

};

