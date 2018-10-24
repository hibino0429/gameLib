#pragma once

#include "../../src/DXEngine/VertexBuffer/VertexBuffer.h"
#include "../../src/DXEngine/Texture/Texture.h"
#include "../../src/DXEngine/Shader/VertexShader/VertexShader.h"
#include "../../src/DXEngine/Shader/PixelShader/PixelShader.h"
#include "../../src/GameSystem/Sample/Sample.h"
#include "../../src/DXEngine/Model/Model.h"
#include "../../src/GameSystem/Particle/Particle.h"
#include "../../src/DXEngine/PointLight/PointLight.h"
#include "../../src/GUISystem/GUISystem.h"
#include "../../src/GameSystem/WindowsInput/WindowsInput.h"
#include "../../src/GameSystem/DirectInput/DirectKey/DirectKey.h"
#include "../../src/GameSystem/DirectInput/DirectMouse/DirectMouse.h"
#include "../../src/GameSystem/GameController/GameController.h"
#include "../../src/Component/SpriteRender/SpriteRender.h"
#include "../../src/GameSystem/XInput/XInput.h"
#include "../../src/Component/ModelRender/ModelRender.h"



//--------------------------------------------------------------------------------------
//!@class		GameMain
//!@brief	ゲームメイン
//--------------------------------------------------------------------------------------
class GameMain
{
public:
	GameMain();
	~GameMain();

	//更新処理
	void	UpDate();	
	//描画処理
	void	Render();

private:
	//!@brief	GUIの初期化
	void	GuiInitialize();
	//!@brief	GUIの終了
	void	GuiFinalize();
	//!@brief	GUIの更新
	void	GuiUpDate();
	//!@brief	GUIの描画
	void	GuiRender();
private:
	Particle*		particle;

	int				timeCnt;
	int				cnt;
	bool			showDemoWindow;
	bool			showAnotherWindow;
	ImVec4			clearColor;

	DirectKey*		directKey;
	DirectMouse*	directMouse;
	WindowsInput*	windowsInput;
	XInput*			xInput;
	GUISystem*		guiSystem;
	GameController*	gameController;
};