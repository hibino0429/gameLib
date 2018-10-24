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
	//!@brief	コンストラクタ
	ParticleSystem();
	//!@brief	コンストラクタ
	//!@param[in]	filePath	ファイルパス
	ParticleSystem(const std::string& filePath);
	//!@brief	デストラクタ
	~ParticleSystem();
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
public:
	void	SetCameraMatrix(const Camera& camera);
	//!@brief	再生 (継続させたり、止めたりする)
	//!@param[in]	playFlag	true:再生する false:再生しない
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