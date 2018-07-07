#pragma once

#include <string>
#include "../../src/GameSystem/Window/Window.h"
#include "../../src/GameSystem/Screen/Screen.h"
#include "../../src/DXEngine/DXDevice/DXDevice.h"
#include "../../src/GameSystem/GameMain/GameMain.h"

//----------------------------------------------------------------------------------------
//!@class		System
//!@brief	�V�X�e�������������܂�
//!@brief	��ʂƃf�o�C�X���Ȃ��܂�
//----------------------------------------------------------------------------------------
class System
{
public:
	//!@brief	�R���X�g���N�^
	System(HINSTANCE hInstance, LPWSTR cmdLine, int cmdShow);
	//!@brief	�f�X�g���N�^
	~System();

	//!@brief	�X�V
	void	UpDate();
	//!@brief	��ʏ��̎擾
	//!@return ��ʏ��
	Screen&	GetScreen();
private:
	Screen*				screen;			//�X�N���[��
	Window*				window;				//�E�B���h�E
	DXDevice*			device;			//�f�o�C�X
	GameMain*			gameMain;		//�Q�[�����C��
};