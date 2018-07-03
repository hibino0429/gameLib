#define _CRT_SECURE_NO_WARNINGS

#include "Window/Window.h"
#include "debug.hpp"
#include "System/System.h"

#include "../src/Device/DXDevice/DXDevice.h"
#include "../../src/Console/Console.hpp"

//------------------------------------------------------------------------
//�A�v���P�[�V�����̃��C��
//------------------------------------------------------------------------
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPWSTR cmdLine, int cmdShow)
{
	//���������[�N���o
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//�R���\�[���o��
	ShowConsole();
	
	//�V�X�e���̐���
	System*		system = new System(hInstance,cmdLine,cmdShow);

	//�X�V
	system->UpDate();

	//���
	if (system != nullptr)
	{
		delete system;
		system = nullptr;
	}

	return 0;
}


