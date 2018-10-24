#pragma once
#include "../../src/Interface/Input/Input2.h"
#include <array>
#include <Windows.h>
#include <Xinput.h>

#pragma comment(lib,"xinput.lib")

//----------------------------------------------------------------------------------------
//!@class		XInput
//!@brief	Xinput�𗘗p���āA���͂������N���X
//----------------------------------------------------------------------------------------
class XInput : public InputDevice
{
public:
	//!@brief	�p�b�h�̔ԍ�
	enum class PadNum
	{
		Pad0,
		Pad1,
		Pad2,
		Pad3
	};
public:
	//!@brief	�R���X�g���N�^
	//!@brief	0�`3�܂ł̔ԍ������蓖�Ă�
	//!@param[in]	controllerNumber	�R���g���[���ԍ�
	XInput(const PadNum& padNum);
	//!@brief	�f�X�g���N�^
	~XInput();
public:
	//!@brief	�R���g���[���[�̏�Ԃ̎擾
	//!@return	XINPUT_STATE�^
	const XINPUT_STATE&	GetState();
	//!@brief	�R���g���[�����ڑ�����Ă��邩�m�F
	//!@return	true: �ڑ�����Ă��� false: �ڑ�����Ă��Ȃ�
	bool	IsConnect();
	//!@brief	�R���g���[����U��������
	//!@param[in]	leftVal	���ւ̐U���l
	//!@param[in]	rightVal �E�ւ̐U���l
	void	Vibrate(int leftVal = 0, int rightVal = 0);
public:
	//!@brief	���͂̐���
	bool	CreateInput() override;
	//!@brief	�X�V
	void	Run() override;
	//!@brief	�����Ă��邩����
	//!@return �����Ă���Ȃ� true �����Ă��Ȃ��Ȃ� false
	bool	Press(const int key) override;
	//!@brief	������������
	//!@return �������Ȃ� true �����ĂȂ��Ȃ� false
	bool	Push(const int key) override;
	//!@brief	������Ă��Ȃ�������
	//!@return ������Ă��Ȃ��Ȃ� true �����Ă���Ȃ� false
	bool	Free(const int key) override;
	//!@brief	�����ꂽ������
	//!@return �����ꂽ�Ȃ� true ������Ă��Ȃ��Ȃ� false
	bool	Release(const int key) override;
private:
	XINPUT_STATE	controllerState;	//Xbox360�R���g���[���̏��
	PadNum			controllerNumber;	//�R���g���[���̔ԍ�
};