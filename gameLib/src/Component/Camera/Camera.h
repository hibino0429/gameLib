#pragma once
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/ConstantBuffer/ConstantBuffer.h"
#include "../../src/Component/Camera/CameraData.h"




//----------------------------------------------
//!@class		Camera
//!@brief	カメラのコンポーネント
//----------------------------------------------
class Camera : public Component
{
public:
	Camera() = delete;
	//!@brief	コンストラクタ
	Camera(const Math::Vector3& eyePos = Math::Vector3(0, 0, 0),
		const Math::Vector3& targetPos = Math::Vector3(0, 0, 0),
		const Math::Vector3& upVec = Math::Vector3(0, 1, 0));
	//!@brief	デストラクタ
	virtual ~Camera();
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
public:
	//!@brief	view変換行列を取得
	const DirectX::XMMATRIX&	GetViewMatrix() const;
	//!@brief	projection変換行列を取得
	const DirectX::XMMATRIX&	GetProjectionMatrix() const;
public:
	void*	operator new(size_t ptr)
	{
		return _mm_malloc(ptr, 16);
	}
	void	operator delete(void* ptr)
	{
		_mm_free(ptr);
	}
private:
	//!@brief	View変換
	void	View();
	//!@brief	Perspective変換
	void	Perspective();
	//!@brief	Ortho変換
	void	Orthographic();
private:
	CameraData		data;
	TransMatrix		transMat;
	ConstantBuffer*	cBuffer;
};