#include "GameMain.h"
#include "../../src/Utility/Utility.hpp"
#include "../../src/Input/KeyBoard/KeyBoard.h"
#include "../../src/Engine/Engine.h"
#include "../../src/Device/GLDevice/GLDevice.h"

//コンストラクタ
GameMain::GameMain()
{
	vertexBuf = new VertexBuffer(3);
	vertexBuf->Create();

	

	Math::Vector3 pos = { 0,12,-20 };
	Math::Vector3 angle = { 20,0,0 };
	camera = new Camera(pos, angle);
	camera->PerspectiveFovLH();

	
	texture = new Texture("./data/image/texture.png");
	
	mesh = new Mesh();
	mesh->CreateCube();
	mesh->GetMaterial().SetTexture(0, texture);
	mesh->SetPos(Math::Vector3(0, 1, -10));
	mesh->SetAngle(Math::Vector3(0, 0, 0));
	mesh->SetScale(Math::Vector3(10, 1, 1));

}

//デストラクタ
GameMain::~GameMain()
{
	Utility::SafeDelete(vertexBuf);
	Utility::SafeDelete(camera);


	Utility::SafeDelete(texture);
	Utility::SafeDelete(mesh);
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
}

//描画処理
void	GameMain::Render()
{
	FLOAT	color[4] = { 0,0,1,1 };

	Engine<DXDevice>::GetDevice().GetDeviceContext3D().ClearRenderTargetView(Engine<DXDevice>::GetDevice().GetRenderTargetView(), color);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().ClearDepthStencilView(Engine<DXDevice>::GetDevice().GetDepthStencilView(), 0, 1.0f, 20);

	mesh->Draw();
	//vertexBuf->Render();
	Engine<DXDevice>::GetDevice().GetSwapChain().Present(0, 0);
}





