#include "DirectPad.h"
#include "../../src/Utility/Utility.hpp"




//!@brief	�����Ă��邩����
//!@return �����Ă���Ȃ� true �����Ă��Ȃ��Ȃ� false
bool	DirectPad::Press(const Pad& padNum, const Button& key)
{
	unsigned char input = this->joystick[static_cast<unsigned int>(padNum)].GetNowJoyState().rgbButtons[(unsigned int)key] & 0x80;
	return input != 0;
}
//!@brief	������������
//!@return �������Ȃ� true �����ĂȂ��Ȃ� false
bool	DirectPad::Push(const Pad& padNum, const Button& key)
{
	unsigned char input = joystick[static_cast<unsigned int>(padNum)].GetNowJoyState().rgbButtons[static_cast<unsigned int>(key)] & 0x80;
	unsigned char preInput = joystick[static_cast<unsigned int>(padNum)].GetPreJoyState().rgbButtons[static_cast<unsigned int>(key)] & 0x80;
	return input != 0 && preInput == 0;
}
//!@brief	������Ă��Ȃ�������
//!@return ������Ă��Ȃ��Ȃ� true �����Ă���Ȃ� false
bool	DirectPad::Free(const Pad& padNum, const Button& key)
{
	unsigned char input = joystick[static_cast<unsigned int>(padNum)].GetNowJoyState().rgbButtons[static_cast<unsigned int>(key)] & 0x80;
	return input == 0;
}
//!@brief	�����ꂽ������
//!@return �����ꂽ�Ȃ� true ������Ă��Ȃ��Ȃ� false
bool	DirectPad::Release(const Pad& padNum, const Button& key)
{
	unsigned char input = joystick[static_cast<unsigned int>(padNum)].GetNowJoyState().rgbButtons[static_cast<unsigned int>(key)] & 0x80;
	unsigned char preInput = joystick[static_cast<unsigned int>(padNum)].GetPreJoyState().rgbButtons[static_cast<unsigned int>(key)] & 0x80;
	return input == 0 && preInput != 0;
}

//!@brief	�\���L�[�̈ʒu���擾
//!@param[in]	padNo	�p�b�h�ԍ�
//!@return	�o�C�g�^�̈ʒu
BYTE	DirectPad::GetPovPosition(const Pad& padNo)
{
	switch (joystick[static_cast<unsigned int>(padNo)].GetNowJoyState().rgbButtons[static_cast<unsigned int>(padNo)])
	{
	case 0:		return (BYTE)Axis::Up;
	case 4500:	return (BYTE)Axis::Up | (BYTE)Axis::Right;
	case 9000:	return (BYTE)Axis::Right;
	case 13500:	return (BYTE)Axis::Right | (BYTE)Axis::Down;
	case 18000:	return (BYTE)Axis::Down;
	case 22500:	return (BYTE)Axis::Down | (BYTE)Axis::Left;
	case 27000:	return (BYTE)Axis::Left;
	case 31500:	return (BYTE)Axis::Left | (BYTE)Axis::Up;
	}
	return (BYTE)0xffffffff;
}