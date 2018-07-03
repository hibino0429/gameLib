#include "System.h"
#include "../../src/Engine/DXEngine/DXEngine.h"

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

	//�f�o�C�X�̐����Ə�����
	device = new DXDevice(screen);
	device->Create();
	
	//�f�o�C�X���G���W���ɓo�^
	Engine<DXDevice>::RegistDevice(device);


	//�Q�[�����C���̐���
	gameMain = new GameMain();
}

//�f�X�g���N�^
System::~System()
{
	delete window;
	delete screen;
	delete device;
	delete gameMain;
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