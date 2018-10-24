#include "System.h"
#include "../../src/DXEngine/DXEngine/DXEngine.h"
#include "../../src/GameSystem/DirectInput/DirectInput.h"
#include "../../src/Utility/Utility.hpp"


//�R���X�g���N�^
System::System(HINSTANCE hInstance, LPWSTR cmdLine, int cmdShow)
{
	//�X�N���[���̐���
	screen = new Screen(1280, 720);

	//�E�B���h�E�̐���
	window			= new Window(screen);
	//�t���X�N���[�����[�h
	window->FullScreen(cmdLine, cmdShow);
	//�E�B���h�E�N���X�̏�����
	window->InitWindowClass(hInstance);
	//�E�B���h�E�N���X�̓o�^
	window->RegistWindowClass();
	//�E�B���h�E�̍쐬
	window->CreateWindows(hInstance);

	//�E�B���h�E�̕\��
	window->Show(cmdShow);
	
	//////////////////////////////////////////////////////
	//�f�o�C�X�̐����Ə�����
	device = new DXDevice(screen);
	device->Create();
	
	//�f�o�C�X���G���W���ɓo�^
	Engine<DXDevice>::RegistDevice(device);

	///////////////////////////////////////////////////////
	//DirectInput�̍쐬
	DirectInput::CreateDirectInput(hInstance);
	
	///////////////////////////////////////////////////////
	//�Q�[�����C���̐���
	gameMain = new GameMain();
}

//�f�X�g���N�^
System::~System()
{
	Utility::SafeDelete(window);
	Utility::SafeDelete(screen);
	Utility::SafeDelete(device);
	Utility::SafeDelete(gameMain);
}


//�X�V����
void	System::UpDate()
{
	while (window->Run())
	{
		gameMain->UpDate();
		gameMain->Render();
	}
}



Screen&	System::GetScreen()
{
	return *screen;
}