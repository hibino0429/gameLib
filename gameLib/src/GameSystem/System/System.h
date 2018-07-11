#pragma once

#include <string>
#include "../../src/GameSystem/Window/Window.h"
#include "../../src/GameSystem/Screen/Screen.h"
#include "../../src/DXEngine/DXDevice/DXDevice.h"
#include "../../src/GameSystem/GameMain/GameMain.h"

//----------------------------------------------------------------------------------------
//!@class		System
//!@brief	システム部分を扱います
//!@brief	画面とデバイスをつなげます
//----------------------------------------------------------------------------------------
class System
{
public:
	//!@brief	コンストラクタ
	System(HINSTANCE hInstance, LPWSTR cmdLine, int cmdShow);
	//!@brief	デストラクタ
	~System();

	//!@brief	更新
	void	UpDate();
	//!@brief	画面情報の取得
	//!@return 画面情報
	Screen&	GetScreen();
private:
	Screen*				screen;			//スクリーン
	Window*				window;				//ウィンドウ
	DXDevice*			device;			//デバイス
	GameMain*			gameMain;		//ゲームメイン
};