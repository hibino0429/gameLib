#include "WindowsInput.h"


//!@brief	�R���X�g���N�^
WindowsInput::WindowsInput()
{
	preKey = -1;
	keyTable.fill(-1);
	frameCnt = 0;
}
//!@brief	�f�X�g���N�^
WindowsInput::~WindowsInput()
{

}
//!@brief	���͂̐���
bool	WindowsInput::CreateInput()
{
	return true;
}
//!@brief	�X�V
void	WindowsInput::Run()
{
	GetKeyboardState(keyTable.data());
}

//!@brief	�����Ă��邩����
//!@return �����Ă���Ȃ� true �����Ă��Ȃ��Ȃ� false
bool	WindowsInput::Press(const int key)
{
	if (keyTable[key] & 0x80)
	{
		preKey = keyTable[key];
		return true;
	}
	preKey = -1;
	return false;
}
//!@brief	������������
//!@return �������Ȃ� true �����ĂȂ��Ȃ� false
bool	WindowsInput::Push(const int key)
{
	if (preKey == keyTable[key]) { return false; }
	if (keyTable[key] & 0x80)
	{
		preKey = keyTable[key];
		return true;
	}
	preKey = -1;
	return false;
}
//!@brief	������Ă��Ȃ�������
//!@return ������Ă��Ȃ��Ȃ� true �����Ă���Ȃ� false
bool	WindowsInput::Free(const int key)
{
	if (!Push(key) && !Press(key))
	{
		return true;
	}
	return false;
}
//!@brief	�����ꂽ������
//!@return �����ꂽ�Ȃ� true ������Ă��Ȃ��Ȃ� false
bool	WindowsInput::Release(const int key)
{
	//�O�̃L�[�ƈ�v���Ȃ��Ȃ���
	//�{�^����������Ă��邩
	if (preKey == keyTable[key]) { return false; }
	//������
	return false;
}