#include "System.h"
#include "../../src/DXEngine/DXEngine/DXEngine.h"
#include "../../src/GameSystem/DirectInput/DirectInput.h"
#include "../../src/Utility/Utility.hpp"


//コンストラクタ
System::System(HINSTANCE hInstance, LPWSTR cmdLine, int cmdShow)
{
	//スクリーンの生成
	screen = new Screen(1280, 720);

	//ウィンドウの生成
	window			= new Window(screen);
	//フルスクリーンモード
	window->FullScreen(cmdLine, cmdShow);
	//ウィンドウクラスの初期化
	window->InitWindowClass(hInstance);
	//ウィンドウクラスの登録
	window->RegistWindowClass();
	//ウィンドウの作成
	window->CreateWindows(hInstance);

	//ウィンドウの表示
	window->Show(cmdShow);
	
	//////////////////////////////////////////////////////
	//デバイスの生成と初期化
	device = new DXDevice(screen);
	device->Create();
	
	//デバイスをエンジンに登録
	Engine<DXDevice>::RegistDevice(device);

	///////////////////////////////////////////////////////
	//DirectInputの作成
	DirectInput::CreateDirectInput(hInstance);
	
	///////////////////////////////////////////////////////
	//ゲームメインの生成
	gameMain = new GameMain();
}

//デストラクタ
System::~System()
{
	Utility::SafeDelete(window);
	Utility::SafeDelete(screen);
	Utility::SafeDelete(device);
	Utility::SafeDelete(gameMain);
}


//更新処理
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