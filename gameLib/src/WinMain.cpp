#define _CRT_SECURE_NO_WARNINGS

#include "../src/GameSystem/Window/Window.h"
#include "../src/Utility/debug.hpp"
#include "../src/GameSystem/System/System.h"
#include "../src/DXEngine/DXDevice/DXDevice.h"
#include "../src/GameSystem/Console/Console.hpp"

//------------------------------------------------------------------------
//アプリケーションのメイン
//------------------------------------------------------------------------
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPWSTR cmdLine, int cmdShow)
{
	//メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//コンソール出力
	ShowConsole();
	
	//システムの生成
	System*		system = new System(hInstance,cmdLine,cmdShow);

	//更新
	system->UpDate();

	//解放
	if (system != nullptr)
	{
		delete system;
		system = nullptr;
	}

	return 0;
}


