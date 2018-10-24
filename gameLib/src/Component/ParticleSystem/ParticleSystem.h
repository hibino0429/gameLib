#pragma once
#include "../../src/Component/ParticleSystem/ParticleData.h"
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/Camera/Camera.h"


//----------------------------------------------------------------
//!@class		ParticleSystem
//----------------------------------------------------------------
class ParticleSystem : public Component
{
public:
	//!@brief	�R���X�g���N�^
	ParticleSystem();
	//!@brief	�R���X�g���N�^
	//!@param[in]	filePath	�t�@�C���p�X
	ParticleSystem(const std::string& filePath);
	//!@brief	�f�X�g���N�^
	~ParticleSystem();
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
public:
	void	SetCameraMatrix(const Camera& camera);
	//!@brief	�Đ� (�p����������A�~�߂��肷��)
	//!@param[in]	playFlag	true:�Đ����� false:�Đ����Ȃ�
	void	PlayBack(bool playFlag);
private:
	void	Create();
	void	Load(const std::string& filePath);
	void	Play();
	void	Stop();
private:
	ParticleData			data;
	DirectX::XMFLOAT4X4		viewMat;
	DirectX::XMFLOAT4X4		projMat;
};