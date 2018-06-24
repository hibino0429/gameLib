#include "GameMain.h"
#include "../../src/Utility/Utility.hpp"
#include "../../src/Input/KeyBoard/KeyBoard.h"
#include "../../src/Engine/Engine.h"
#include "../../src/Device/GLDevice/GLDevice.h"

//コンストラクタ
GameMain::GameMain()
{

	Math::Vector3 pos = { 0,0,-50 };
	Math::Vector3 angle = { 0,0,0 };
	camera = new Camera(pos, angle);
	camera->PerspectiveFovLH();


	sample = new Sample();
}

//デストラクタ
GameMain::~GameMain()
{
	Utility::SafeDelete(camera);
	Utility::SafeDelete(sample);


}

//更新処理
void	GameMain::UpDate()
{
	camera->LookAtLH();
	if (KeyBoard::On(KeyBoard::Key::KEY_UP))
	{
		camera->AddVec(Math::Vector3(0.0f, 0.0f, 0.5f));
	}
	if (KeyBoard::On(KeyBoard::Key::KEY_DOWN))
	{
		camera->AddVec(Math::Vector3(0.0f, -0.0f, 0.5f));
	}

	sample->UpDate();
}

//描画処理
void	GameMain::Render()
{
	FLOAT	color[4] = { 0,0,1,1 };

	Engine<DXDevice>::GetDevice().Run();
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().ClearRenderTargetView(Engine<DXDevice>::GetDevice().GetRenderTargetView(), color);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().ClearDepthStencilView(Engine<DXDevice>::GetDevice().GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 20);

	sample->Render();

	Engine<DXDevice>::GetDevice().GetSwapChain().Present(0, 0);
}





