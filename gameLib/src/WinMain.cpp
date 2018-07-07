#define _CRT_SECURE_NO_WARNINGS

#include "../src/GameSystem/Window/Window.h"
#include "../src/Utility/debug.hpp"
#include "../src/GameSystem/System/System.h"
#include "../src/DXEngine/DXDevice/DXDevice.h"
#include "../src/GameSystem/Console/Console.hpp"

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


