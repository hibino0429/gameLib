#include "DirectKey.h"
#include "../../src/Utility/Utility.hpp"


LPDIRECTINPUTDEVICE8 DirectKey::KeyBoardDevice::keyDevice = nullptr;
unsigned char DirectKey::KeyBoardDevice::nowKey[256] = { 0 };
unsigned char DirectKey::KeyBoardDevice::preKey[256] = { 0 };

DirectKey::KeyBoardDevice::KeyBoardDevice(const HWND& hWnd)
{
	CreateDevice();
	SetDataFormat();
	SetCooperativeLevel(hWnd);
	keyDevice->Acquire();
	std::memset(&nowKey, 0, sizeof(nowKey));
}

DirectKey::KeyBoardDevice::~KeyBoardDevice()
{
	Finalize();
}


bool	DirectKey::KeyBoardDevice::CreateDevice()
{
	auto result = DirectInput::GetInstance()->CreateDevice(GUID_SysKeyboard, &keyDevice, nullptr);
	if (FAILED(result))
	{
		MessageBoxA(nullptr, "�L�[�{�[�h�f�o�C�X�̍쐬�Ɏ��s", "DirectKey::CreateDevice()", MB_OK);
		DirectInput::GetInstance()->Release();
		return false;
	}
	return true;
}

bool	DirectKey::KeyBoardDevice::SetDataFormat()
{
	auto result = keyDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		MessageBoxA(nullptr, "���̓f�[�^�`���̃Z�b�g�Ɏ��s", "DirectKey::SetDataFormat()", MB_OK);
		keyDevice->Release();
		DirectInput::GetInstance()->Release();
		return false;
	}
	return true;
}

bool	DirectKey::KeyBoardDevice::SetCooperativeLevel(const HWND& hWnd)
{
	auto result = keyDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	if (FAILED(result))
	{
		MessageBoxA(nullptr, "�r������̃Z�b�g�Ɏ��s", "DirectKey::SetCooperativeLevel()", MB_OK);
		keyDevice->Release();
		DirectInput::GetInstance()->Release();
		return false;
	}
	return true;
}

void	DirectKey::KeyBoardDevice::Finalize()
{
	if (keyDevice) { keyDevice->Unacquire(); }
	Utility::SafeRelease(keyDevice);
}

//!@brief	����
void	DirectKey::KeyBoardDevice::Run()
{
	std::memcpy(preKey, nowKey, sizeof(nowKey));
	std::memset(nowKey, 0, sizeof(nowKey));
	auto result = keyDevice->GetDeviceState(sizeof(nowKey), nowKey);

	if (FAILED(result))
	{
		//���s������A������x�擾�����݂�
		//keyDevice->Acquire();
		while (keyDevice->Acquire() == DIERR_INPUTLOST);
		result = keyDevice->GetDeviceState(sizeof(nowKey), nowKey);
	}
}

bool	DirectKey::KeyBoardDevice::Press(const unsigned char& key)
{
	//�O�̓��͂ƌ��݂̓��͂��قȂ�Ȃ�A�p�������ł͂Ȃ�
	unsigned char input = 0x00;
	input = nowKey[static_cast<unsigned char>(key)] & 0x80;
	return input != 0;
}

bool	DirectKey::KeyBoardDevice::Push(const unsigned char& key)
{
	//�O�̓��͂����݂̓��͂Ɠ����Ȃ�A�p�������Ȃ��߁A1�񔻒�ł͂Ȃ�
	unsigned char nowInput = 0x00;
	unsigned char preInput = 0x00;
	nowInput = nowKey[static_cast<unsigned char>(key)] & 0x80;
	preInput = preKey[static_cast<unsigned char>(key)] & 0x80;
	return nowInput != 0 && preInput == 0;
}
bool	DirectKey::KeyBoardDevice::Free(const unsigned char& key)
		{
	unsigned char input = 0x00;
	input = nowKey[static_cast<unsigned char>(key)] & 0x80;
	return input == 0;
		}

bool	DirectKey::KeyBoardDevice::Release(const unsigned char& key)
{
	unsigned char nowInput = 0x00;
	unsigned char preInput = 0x00;
	nowInput = nowKey[static_cast<unsigned char>(key)] & 0x80;
	preInput = preKey[static_cast<unsigned char>(key)] & 0x80;
	return nowInput == 0 && preInput != 0;
}



//!@brief	�R���X�g���N�^
DirectKey::DirectKey(const HWND& hWnd)
	:keyDevice(hWnd)
{
	
}
//!@brief	�f�X�g���N�^
DirectKey::~DirectKey()
{
	
}


//!@brief	����
void	DirectKey::Run()
{
	keyDevice.Run();
}


//!@brief	�����Ă��邩����
//!@param[in]	key	�L�[
bool	DirectKey::Press(const Key& key)
{
	return keyDevice.Press(static_cast<unsigned char>(key));
}
//!@brief	�����ꂽ������
//!@param[in]	key	�L�[
bool	DirectKey::Push(const Key& key)
{
	return keyDevice.Push(static_cast<unsigned char>(key));
}
//!@brief	������Ă��邩
//!@param[in]	key	�L�[
bool	DirectKey::Free(const Key& key)
{
	return keyDevice.Free(static_cast<unsigned char>(key));
}
//!@brief	�����ꂽ������
//!@param[in]	key	�L�[
bool	DirectKey::Release(const Key& key)
{
	return keyDevice.Release(static_cast<unsigned char>(key));
}