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
//!@brief	�Q�[�����C��
//--------------------------------------------------------------------------------------
class GameMain
{
public:
	GameMain();
	~GameMain();

	//�X�V����
	void	UpDate();	
	//�`�揈��
	void	Render();

private:
	//!@brief	GUI�̏�����
	void	GuiInitialize();
	//!@brief	GUI�̏I��
	void	GuiFinalize();
	//!@brief	GUI�̍X�V
	void	GuiUpDate();
	//!@brief	GUI�̕`��
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