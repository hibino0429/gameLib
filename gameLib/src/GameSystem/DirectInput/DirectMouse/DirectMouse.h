#pragma once
#include "../../src/GameSystem/DirectInput/DirectInput.h"

//------------------------------------------------------------------------------
//!@class		DirectMouse
//!@brief	DirectX�̃}�E�X�f�o�C�X���g�p���A�}�E�X������s��
//------------------------------------------------------------------------------
class DirectMouse
{
private:
	//!@brief	�}�E�X�{�^��
	enum class Button
	{
		Left,
		Right
	};
public:
	//!@brief	�R���X�g���N�^
	//!@param[in]	hWnd	�E�B���h�E�n���h��
	DirectMouse(const HWND& hWnd);
	//!@brief	�f�X�g���N�^
	~DirectMouse();
private:
	//!@brief	���̓}�E�X�f�o�C�X�̍쐬
	//!@param[in]	hWnd	�n���h��
	bool	CreateMouseInput(const HWND& hWnd);
public:
	//!@brief	�X�V
	void	Run();
	//!@brief	������Ă��邩����
	bool	LButtonPush();
	//!@brief	������Ă��邩����
	bool	RButtonPush();
	//!@brief	�}�E�X�J�[�\���̈ʒu�̎擾
	//!@return	�}�E�X�J�[�\���̈ʒu
	POINT	GetMousePos();
	//!@brief	�z�C�[������]���Ă��邩
	bool	WheelRotation();
	//!@brief	���]�������̔���
	bool	UpWheelRotation();
	//!@brief	����]�������̔���
	bool	DownWheelRotation();
private:
	LPDIRECTINPUTDEVICE8	DIMouse;
	DIMOUSESTATE			mouseState;
	HWND					hWnd;
	POINT					position;
};

