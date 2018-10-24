#include "ParticleSystem.h"
#include "../../src/Engine/Engine.h"
#include "../../src/Component/Transform/Transform.h"
#include "../../src/GameSystem/ECS/Entity/Entity.h"


ParticleSystem::ParticleSystem()
{
	data.renderer = nullptr;
	data.manager = nullptr;
	data.effect = nullptr;
	data.handle = 0;
	data.maxSprits = 2000;
	data.playFlag = true;

	Create();
}

ParticleSystem::ParticleSystem(const std::string & filePath)
{
	data.renderer = nullptr;
	data.manager = nullptr;
	data.effect = nullptr;
	data.handle = 0;
	data.maxSprits = 2000;
	data.playFlag = true;

	Create();
	Load(filePath);
}

ParticleSystem::~ParticleSystem()
{
	//エフェクトの解放 (再生中は、再生が終了した後、自動で解放)
	ES_SAFE_RELEASE(data.effect);
	//エフェクト管理用インスタンスの破棄
	data.manager->Destroy();
	//サウンド用インスタンスの破棄
	//data.sound->Destory();
	//描画用インスタンスの破棄
	data.renderer->Destroy();
}

void ParticleSystem::Initialize()
{
	
}

void ParticleSystem::UpDate()
{
	data.manager->Update();
	if (data.playFlag)
	{
		Play();
	}
	else
	{
		Stop();
	}
}

void ParticleSystem::Render2D()
{
}

void ParticleSystem::Render3D()
{
	Effekseer::Matrix44	view;
	Effekseer::Matrix44	projection;

	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			view.Values[y][x] = viewMat.m[y][x];
			projection.Values[y][x] = projMat.m[y][x];
		}
	}

	//変換
	view.Transpose();
	projection.Transpose();

	//カメラ行列の更新
	data.renderer->SetCameraMatrix(view);
	//投影行列の更新
	data.renderer->SetProjectionMatrix(projection);

	data.renderer->BeginRendering();
	data.manager->Draw();
	data.renderer->EndRendering();
}

void ParticleSystem::SetCameraMatrix(const Camera & camera)
{
	DirectX::XMStoreFloat4x4(&viewMat, camera.GetViewMatrix());
	DirectX::XMStoreFloat4x4(&projMat, camera.GetProjectionMatrix());
}

void ParticleSystem::PlayBack(bool playFlag)
{
	data.playFlag = playFlag;
}

void ParticleSystem::Create()
{
	//描画管理インスタンスの生成
	data.renderer = EffekseerRendererDX11::Renderer::Create(
		&Engine<DXDevice>::GetDevice().GetDevice3D(),
		&Engine<DXDevice>::GetDevice().GetDeviceContext3D(),
		data.maxSprits);
	//エフェクト管理用インスタンス生成
	data.manager = Effekseer::Manager::Create(data.maxSprits);
	//座標系の指定(RHで右手系,LHで左手系)
	data.manager->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);
	//描画方法を指定 (独自に拡張することもできる)
	data.manager->SetSpriteRenderer(data.renderer->CreateSpriteRenderer());
	data.manager->SetRibbonRenderer(data.renderer->CreateRibbonRenderer());
	data.manager->SetRingRenderer(data.renderer->CreateRingRenderer());
	data.manager->SetTrackRenderer(data.renderer->CreateTrackRenderer());
	data.manager->SetModelRenderer(data.renderer->CreateModelRenderer());

	//テクスチャ画像の読み込み方法の指定 (パッケージ等から読み込む場合、拡張の必要あり)
	data.manager->SetTextureLoader(data.renderer->CreateTextureLoader());
}

void ParticleSystem::Load(const std::string & filePath)
{
	// エフェクトの読込
	EFK_CHAR pass[64];
	Effekseer::ConvertUtf8ToUtf16((int16_t*)pass, 64, (const int8_t*)filePath.c_str());
	data.effect = Effekseer::Effect::Create(data.manager, pass);
}

void ParticleSystem::Play()
{
	if (GetEntity()->HasComponent<Transform>())
	{
		Transform	trans = GetEntity()->GetComponent<Transform>();

		data.handle = data.manager->Play(data.effect, trans.position.x, trans.position.y, trans.position.z);
		data.manager->SetScale(data.handle, trans.scale.x, trans.scale.y, trans.scale.z);
		data.manager->SetRotation(
			data.handle,
			DirectX::XMConvertToRadians(trans.rotation.x),
			DirectX::XMConvertToRadians(trans.rotation.y),
			DirectX::XMConvertToRadians(trans.rotation.z)
		);
	}
}

void ParticleSystem::Stop()
{
	data.manager->StopEffect(data.handle);
}
