#pragma once
#include "../../src/GameSystem/DirectInput/DirectInput.h"
#include "../../src/GameSystem/DirectInput/DirectPad/DirectJoyStick/DirectJoyStick.h"

#define MaxPadNum 4
//------------------------------------------------------------------------------
//!@class		DirectPad
//!@brief	DirectJoystick�𕡐��ۗL���āA�W���C�X�e�B�b�N������
//------------------------------------------------------------------------------
class DirectPad
{
public:
	//!@brief	�p�b�h�ԍ�
	enum class Pad
	{
		No0 = 0,
		No1,
		No2,
		No3
	};
	//!@brief	�p�b�h�{�^��
	enum class Button
	{
		X,
		Y,
		A,
		B,
		R1,
		R2,
		R3,
		L1,
		L2,
		L3,
	};
	//!@brief	�p�b�h��
	enum class Axis
	{
		Up = 0x1,
		Right = 0x2,
		Down = 0x4,
		Left = 0x8
	};
public:
	//!@brief	�����Ă��邩����
	//!@return �����Ă���Ȃ� true �����Ă��Ȃ��Ȃ� false
	bool	Press(const Pad& padNum,const Button& key);
	//!@brief	������������
	//!@return �������Ȃ� true �����ĂȂ��Ȃ� false
	bool	Push(const Pad& padNum, const Button& key);
	//!@brief	������Ă��Ȃ�������
	//!@return ������Ă��Ȃ��Ȃ� true �����Ă���Ȃ� false
	bool	Free(const Pad& padNum, const Button& key);
	//!@brief	�����ꂽ������
	//!@return �����ꂽ�Ȃ� true ������Ă��Ȃ��Ȃ� false
	bool	Release(const Pad& padNum, const Button& key);
	//!@brief	�\���L�[�̈ʒu���擾
	//!@param[in]	no	�p�b�h�ԍ�
	//!@return	�o�C�g�^�̈ʒu
	BYTE	GetPovPosition(const Pad& padNo);
private:
	std::array<DirectJoyStick, MaxPadNum>	joystick;		//�W���C�X�e�B�b�N
	Pad										nowPadNo;		//���݂̃p�b�h�ԍ�
};




