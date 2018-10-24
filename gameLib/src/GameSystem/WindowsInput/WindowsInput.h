#pragma once
#include "../../src/Interface/Input/Input2.h"
#include <array>
#include <Windows.h>

//----------------------------------------------------------------------------------------
//!@class		WindowsInput
//!@brief	�E�B���h�E�Y���p�ӂ��Ă������
//----------------------------------------------------------------------------------------
class WindowsInput : public InputDevice
{
public:
	//!@brief	�R���X�g���N�^
	WindowsInput();
	//!@brief	�f�X�g���N�^
	~WindowsInput();
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
	std::array<BYTE, 256>	keyTable;
	BYTE					preKey;
	int						frameCnt;
};