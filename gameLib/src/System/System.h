#pragma once

#include <string>
#include "../../src/Window/Window.h"
#include "../../src/Screen/Screen.h"
#include "../../src/Device/DXDevice/DXDevice.h"
#include "../../src/GameMain/GameMain.h"

//----------------------------------------------------------------------------------------
//概要: システム部分を扱います
//概要: 画面とデバイスをつなげます
//----------------------------------------------------------------------------------------
class System
{
public:
	System(HINSTANCE hInstance, LPWSTR cmdLine, int cmdShow);
	~System();

	//概要: 更新処理
	void	UpDate();

	Screen&	GetScreen();
private:
	Screen*				screen;			//スクリーン
	Window*			window;			//ウィンドウ
	DXDevice*			device;			//デバイス
	GameMain*			gameMain;		//ゲームメイン
};