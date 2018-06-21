#pragma once

#include <string>
#include "../../src/Window/Window.h"
#include "../../src/Screen/Screen.h"
#include "../../src/Device/DXDevice/DXDevice.h"
#include "../../src/GameMain/GameMain.h"

//----------------------------------------------------------------------------------------
//�T�v: �V�X�e�������������܂�
//�T�v: ��ʂƃf�o�C�X���Ȃ��܂�
//----------------------------------------------------------------------------------------
class System
{
public:
	System(HINSTANCE hInstance, LPWSTR cmdLine, int cmdShow);
	~System();

	//�T�v: �X�V����
	void	UpDate();

	Screen&	GetScreen();
private:
	Screen*				screen;			//�X�N���[��
	Window*			window;			//�E�B���h�E
	DXDevice*			device;			//�f�o�C�X
	GameMain*			gameMain;		//�Q�[�����C��
};