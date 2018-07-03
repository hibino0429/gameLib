#include "GameMain.h"
#include "../../src/Utility/Utility.hpp"
#include "../../src/Input/KeyBoard/KeyBoard.h"
#include "../../src/Engine/Engine.h"
#include "../../src/Device/GLDevice/GLDevice.h"


//コンストラクタ
GameMain::GameMain()
{
	timeCnt = 0;
	Math::Vector3 eyePos = { 2.0f,2.0f,-120.0f };
	Math::Vector3 targetPos = { 0,0,0 };
	Math::Vector3 upVec = { 0, 1 ,0 };
	camera = new Camera(eyePos, targetPos, upVec);

	//sample = new Sample();
	//texture = new Texture("./data/image/texture.png");

	model = new Model();

	//particle = new Particle();
	//particle->Load("./data/particle/TestParticle.efk");
}

//デストラクタ
GameMain::~GameMain()
{
	Utility::SafeDelete(camera);
	//Utility::SafeDelete(sample);
	//Utility::SafeDelete(texture);
	Utility::SafeDelete(model);
	//Utility::SafeDelete(particle);
}

//更新処理
void	GameMain::UpDate()
{
	camera->LookAtLH();
	camera->PerspectiveFovLH();

	
	if (KeyBoard::On(KeyBoard::Key::KEY_UP))
	{
		//camera->AddVec(Math::Vector3(0.0f, 0.0f, 0.5f));
	}
	if (KeyBoard::On(KeyBoard::Key::KEY_DOWN))
	{
		//camera->AddVec(Math::Vector3(0.0f, -0.0f, 0.5f));
	}

	//sample->UpDate();

	++timeCnt;
	if (timeCnt >= 180)
	{
		//particle->Play();
		timeCnt = 0;
	}

	model->SetMatrix(camera);
	model->UpDate();
}

//描画処理
void	GameMain::Render()
{
	FLOAT	color[4] = { 0,0,1,1 };

	Engine<DXDevice>::GetDevice().Run();
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().ClearRenderTargetView(Engine<DXDevice>::GetDevice().GetRenderTargetView(), color);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().ClearDepthStencilView(Engine<DXDevice>::GetDevice().GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	
	//texture->Render();
	//sample->Render();
	model->Render();
	//particle->Draw(*camera);

	Engine<DXDevice>::GetDevice().GetSwapChain().Present(0, 0);
}





