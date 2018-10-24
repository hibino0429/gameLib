#pragma once
#define DIRECTINPUT_VERSION 0x0800
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#include <dinput.h>


//---------------------------------------------------------------------------------
//!@class		DirectInput
//!@brief	DirectInput�𗘗p�������͏���������
//!@brief	DirectInput���������߂̃f�o�C�X���Ǘ�
//---------------------------------------------------------------------------------
class DirectInput
{
public:
	//!@brief	�R���X�g���N�^
	DirectInput();
	//!@brief	�f�X�g���N�^
	~DirectInput();
public:
	//!@brief	IDirectInput8�I�u�W�F�N�g�̍쐬
	//!@return	true: ���� false: ���s
	static bool	CreateDirectInput(const HINSTANCE& hInstance);
	//!@brief	DirectInput8�I�u�W�F�N�g�̎擾
	//!@return	directInput�I�u�W�F�N�g
	static LPDIRECTINPUT8&	GetInstance();
private:
	static LPDIRECTINPUT8			directInput;
};




//---------------------------------------------------------------------------------
//!@class		DirectInputDevice
//!@brief	DirectInput�̃f�o�C�X�̒��ۓI�ȏ���
//---------------------------------------------------------------------------------
class DirectInputDevice
{
protected:
	//!@brief	�f�o�C�X�̍쐬
	virtual bool	CreateDevice() = 0;
	//!@brief	���̓f�[�^�`���̐ݒ�
	virtual bool	SetDataFormat() = 0;
	//!@brief	�r������
	virtual bool	SetCooperativeLevel(const HWND& hWnd) = 0;
	//!@brief	����
	virtual void	Run() = 0;
	//!@brief	�I������
	virtual void	Finalize() = 0;
};



