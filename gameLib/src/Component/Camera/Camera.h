#pragma once
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/ConstantBuffer/ConstantBuffer.h"
#include "../../src/Component/Camera/CameraData.h"




//----------------------------------------------
//!@class		Camera
//!@brief	�J�����̃R���|�[�l���g
//----------------------------------------------
class Camera : public Component
{
public:
	Camera() = delete;
	//!@brief	�R���X�g���N�^
	Camera(const Math::Vector3& eyePos = Math::Vector3(0, 0, 0),
		const Math::Vector3& targetPos = Math::Vector3(0, 0, 0),
		const Math::Vector3& upVec = Math::Vector3(0, 1, 0));
	//!@brief	�f�X�g���N�^
	virtual ~Camera();
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
public:
	//!@brief	view�ϊ��s����擾
	const DirectX::XMMATRIX&	GetViewMatrix() const;
	//!@brief	projection�ϊ��s����擾
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
	//!@brief	View�ϊ�
	void	View();
	//!@brief	Perspective�ϊ�
	void	Perspective();
	//!@brief	Ortho�ϊ�
	void	Orthographic();
private:
	CameraData		data;
	TransMatrix		transMat;
	ConstantBuffer*	cBuffer;
};