#include "DirectInput.h"
#include "../../src/Utility/Utility.hpp"



////////////////////////////////////////////////////////////////////////////
//static�ϐ�
LPDIRECTINPUT8 DirectInput::directInput = nullptr;



//!@brief	�R���X�g���N�^
DirectInput::DirectInput()
{
	
}
//!@brief	�f�X�g���N�^
DirectInput::~DirectInput()
{
	Utility::SafeRelease(directInput);
}

//!@brief	IDirectInput8�I�u�W�F�N�g�̍쐬
//!@return	true: ���� false: ���s
bool	DirectInput::CreateDirectInput(const HINSTANCE& hInstance)
{
	auto	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&directInput, nullptr);
	if (FAILED(result))
	{
		MessageBoxA(nullptr, "DirectInput8�̍쐬�Ɏ��s���܂���", "CreateDirectInput()", MB_OK);
		return false;
	}
	return true;
}

//!@brief	DirectInput8�I�u�W�F�N�g�̎擾
//!@return	directInput�I�u�W�F�N�g
LPDIRECTINPUT8&	DirectInput::GetInstance()
{
	return  directInput;
}

