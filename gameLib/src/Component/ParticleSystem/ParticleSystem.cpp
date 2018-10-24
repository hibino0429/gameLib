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
	//�G�t�F�N�g�̉�� (�Đ����́A�Đ����I��������A�����ŉ��)
	ES_SAFE_RELEASE(data.effect);
	//�G�t�F�N�g�Ǘ��p�C���X�^���X�̔j��
	data.manager->Destroy();
	//�T�E���h�p�C���X�^���X�̔j��
	//data.sound->Destory();
	//�`��p�C���X�^���X�̔j��
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

	//�ϊ�
	view.Transpose();
	projection.Transpose();

	//�J�����s��̍X�V
	data.renderer->SetCameraMatrix(view);
	//���e�s��̍X�V
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
	//�`��Ǘ��C���X�^���X�̐���
	data.renderer = EffekseerRendererDX11::Renderer::Create(
		&Engine<DXDevice>::GetDevice().GetDevice3D(),
		&Engine<DXDevice>::GetDevice().GetDeviceContext3D(),
		data.maxSprits);
	//�G�t�F�N�g�Ǘ��p�C���X�^���X����
	data.manager = Effekseer::Manager::Create(data.maxSprits);
	//���W�n�̎w��(RH�ŉE��n,LH�ō���n)
	data.manager->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);
	//�`����@���w�� (�Ǝ��Ɋg�����邱�Ƃ��ł���)
	data.manager->SetSpriteRenderer(data.renderer->CreateSpriteRenderer());
	data.manager->SetRibbonRenderer(data.renderer->CreateRibbonRenderer());
	data.manager->SetRingRenderer(data.renderer->CreateRingRenderer());
	data.manager->SetTrackRenderer(data.renderer->CreateTrackRenderer());
	data.manager->SetModelRenderer(data.renderer->CreateModelRenderer());

	//�e�N�X�`���摜�̓ǂݍ��ݕ��@�̎w�� (�p�b�P�[�W������ǂݍ��ޏꍇ�A�g���̕K�v����)
	data.manager->SetTextureLoader(data.renderer->CreateTextureLoader());
}

void ParticleSystem::Load(const std::string & filePath)
{
	// �G�t�F�N�g�̓Ǎ�
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
