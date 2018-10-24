#include "Camera.h"
#include "../../src/Engine/Engine.h"
#include "../../src/Utility/Utility.hpp"
#include "../../src/Component/Transform/Transform.h"
#include "../../src/GameSystem/ECS/Entity/Entity.h"



Camera::Camera(const Math::Vector3 & eyePos, const Math::Vector3 & targetPos, const Math::Vector3 & upVec)
{
	data.eyePos = eyePos;
	data.targetPos = targetPos;
	data.upVec = upVec;
	data.backGround = Math::Vector4(0, 0, 1, 1);
	data.aspect = Engine<DXDevice>::GetDevice().GetViewPort().Width / Engine<DXDevice>::GetDevice().GetViewPort().Height;
	data.fovAngle = 45.0f;
	data.nearZ = 0.1f;
	data.farZ = 1000.0f;
	data.projectionFlag = true;
	
	cBuffer = new ConstantBuffer(sizeof(CBuffer));
}

Camera::~Camera()
{
	Utility::SafeDelete(cBuffer);
}

void Camera::Initialize()
{
	if (GetEntity()->HasComponent<Transform>())
	{
		data.eyePos = GetEntity()->GetComponent<Transform>().GetPosition();
	}
}

void Camera::UpDate()
{
	View();
	if (data.projectionFlag)
	{
		Perspective();
	}
	else
	{
		Orthographic();
	}
	CBuffer	cb;
	DirectX::XMStoreFloat4x4(&cb.world, DirectX::XMMatrixTranslation(data.eyePos.x, data.eyePos.y, data.eyePos.z));
	DirectX::XMStoreFloat4x4(&cb.view, transMat.viewMat);
	DirectX::XMStoreFloat4x4(&cb.projection, transMat.projMat);
	cBuffer->UpDate(&cb);
}

void Camera::Render2D()
{
	
}

void Camera::Render3D()
{
	float	color[] = { data.backGround.x,data.backGround.y,data.backGround.z,data.backGround.w };
	Engine<DXDevice>::GetDevice().Run();
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().ClearRenderTargetView(Engine<DXDevice>::GetDevice().GetRenderTargetView(), static_cast<float*>(color));
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().ClearDepthStencilView(Engine<DXDevice>::GetDevice().GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	cBuffer->Render();
}

const DirectX::XMMATRIX & Camera::GetViewMatrix() const
{
	return transMat.viewMat;
}

const DirectX::XMMATRIX & Camera::GetProjectionMatrix() const
{
	return transMat.projMat;
}

void Camera::View()
{
	/*transMat.viewMat = DirectX::XMMatrixTranspose(
		DirectX::XMMatrixLookAtLH(data.eyePos, data.targetPos, data.upVec)
	);*/
	if (GetEntity()->HasComponent<Transform>())
	{
		Transform& trans = GetEntity()->GetComponent<Transform>();
		transMat.viewMat = DirectX::XMMatrixTranspose(
			DirectX::XMMatrixInverse(
				nullptr,
				DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(trans.GetRotation().x)) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(trans.GetRotation().y)) *
				DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(trans.GetRotation().z)) *
				DirectX::XMMatrixTranslation(trans.GetPosition().x, trans.GetPosition().y, trans.GetPosition().z)
			)
		);
	}
}

void Camera::Perspective()
{
	transMat.projMat = DirectX::XMMatrixTranspose(
		DirectX::XMMatrixPerspectiveFovLH(
			DirectX::XMConvertToRadians(data.fovAngle),
			data.aspect,
			data.nearZ,
			data.farZ
		)
	);
}

void Camera::Orthographic()
{
	transMat.projMat = DirectX::XMMatrixTranspose(
		DirectX::XMMatrixOrthographicLH(
			Engine<DXDevice>::GetDevice().GetViewPort().Width,
			Engine<DXDevice>::GetDevice().GetViewPort().Height,
			data.nearZ,
			data.farZ)
	);
}
