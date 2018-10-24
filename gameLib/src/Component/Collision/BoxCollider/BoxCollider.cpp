#include "BoxCollider.h"
#include "../../src/GameSystem/ECS/Entity/Entity.h"
#include "../../src/Component/ModelRender/ModelRender.h"
#include "../../src/Component/Transform/Transform.h"


BoxCollider::BoxCollider()
	: centerPosOffset(0.0f,0.0f,0.0f)
	, axisLength(1.0f,1.0f,1.0f)
	, divideLength(2.0f)
{
	
}

BoxCollider::BoxCollider(const Math::Vector3 & center, const Math::Vector3 & size)
	: centerPosOffset(center)
	, axisLength(size)
	, divideLength(2.0f)
{

}

const Math::Vector3 & BoxCollider::GetCenter() const
{
	if (!GetEntity()->HasComponent<Transform>()) { return Math::Vector3(0,0,0); }
	return GetEntity()->GetComponent<Transform>().GetPosition();
}

const Math::Vector3 & BoxCollider::GetSize() const
{
	return maxPos - minPos;
}

const Math::Vector3 & BoxCollider::GetDirect(int elemNum) const
{
	//‰¼
	return maxPos;
}

const float & BoxCollider::GetLength(int elemNum) const
{
	//‰¼
	return 1.0f;
}

const Math::Vector3 & BoxCollider::GetMinPos() const
{
	return minPos;
}

const Math::Vector3 & BoxCollider::GetMaxPos() const
{
	return maxPos;
}



void BoxCollider::Initialize()
{
	//GetEntity()->AddComponent<Material>(Math::Vector4(1, 1, 1, 1));
	//GetEntity()->GetComponent<Material>().SetShader(new Shader("./data/shaderData/diffuseShader"));
	//Math::Vector4 color = GetEntity()->GetComponent<Material>().GetColor();
	GetEntity()->AddComponent<ModelRender>(new FbxModel("./data/model/boxCollider.fbx"));
	GetEntity()->GetComponent<ModelRender>().SetDrawMode(D3D11_FILL_WIREFRAME);
	
	if (GetEntity()->HasComponent<Transform>())
	{
		Transform& trans = GetEntity()->GetComponent<Transform>();
		trans.position += centerPosOffset;
		trans.scale = axisLength;
		minPos = Math::Vector3(trans.GetPosition() - axisLength / divideLength);
		maxPos = Math::Vector3(trans.GetPosition() + axisLength / divideLength);
	}
}

void BoxCollider::UpDate()
{
	if (GetEntity()->HasComponent<Transform>())
	{
		Transform trans = GetEntity()->GetComponent<Transform>();
		minPos = Math::Vector3(trans.GetPosition() - axisLength / divideLength);
		maxPos = Math::Vector3(trans.GetPosition() + axisLength / divideLength);

		DirectX::XMMATRIX	matT = Math::TransformMatrix(trans.position);
		DirectX::XMMATRIX	matR = Math::RotationMatrix(trans.rotation);
		DirectX::XMMATRIX	matS = Math::ScaleMatrix(trans.scale);

		Camera camera = Manager::GetEntityManager().GetEntity("Camera").GetComponent<Camera>();
		DirectionalLight light = Manager::GetEntityManager().GetEntity("DirectionalLight").GetComponent<DirectionalLight>();
		DirectX::XMMATRIX	world = matS * matR * matT;
		DirectX::XMMATRIX	view = camera.GetViewMatrix();
		DirectX::XMMATRIX	proj = camera.GetProjectionMatrix();

		CBuffer	cBuf;
		DirectX::XMStoreFloat4x4(&cBuf.world, DirectX::XMMatrixTranspose(world));
		DirectX::XMStoreFloat4x4(&cBuf.view, view);
		DirectX::XMStoreFloat4x4(&cBuf.projection, proj);
		DirectX::XMStoreFloat4(&cBuf.lightDirection, DirectX::XMVECTOR(light.GetLightDir()));
		DirectX::XMStoreFloat4(&cBuf.lightColor, DirectX::XMVECTOR(light.GetLightColor()));

		constantBuf->UpDate(&cBuf);
	}
}

void BoxCollider::Render2D()
{
}

void BoxCollider::Render3D()
{
}
