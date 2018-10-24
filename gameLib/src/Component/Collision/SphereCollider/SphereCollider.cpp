#include "SphereCollider.h"
#include "../../src/GameSystem/ECS/Entity/Entity.h"
#include "../../src/Component/ModelRender/ModelRender.h"
#include "../../src/Component/Transform/Transform.h"


SphereCollider::SphereCollider()
{
	data.center = Math::Vector3(0, 0, 0);
	data.radius = 0.5f;
}

SphereCollider::SphereCollider(const Math::Vector3 & center, const float radius)
{
	data.center = center;
	data.radius = radius;
}

const float SphereCollider::GetRadius() const
{
	return data.radius;
}

const Math::Vector3 & SphereCollider::GetCenterOffset() const
{
	return data.center;
}

const Math::Vector3 & SphereCollider::GetCenterPosition() const
{
	if (GetEntity()->HasComponent<Transform>())
	{
		return GetEntity()->GetComponent<Transform>().GetPosition();
	}
	return Math::Vector3(0, 0, 0);
}

void SphereCollider::Initialize()
{
	//GetEntity()->AddComponent<Material>(Math::Vector4(1, 1, 1, 1));
	//GetEntity()->GetComponent<Material>().LoadShaderFile("./data/shaderData/diffuseShader");
	GetEntity()->AddComponent<ModelRender>(new FbxModel("./data/model/sphere.fbx"));
	GetEntity()->GetComponent<ModelRender>().SetDrawMode(D3D11_FILL_WIREFRAME);
	if (GetEntity()->HasComponent<Transform>())
	{
		GetEntity()->GetComponent<Transform>().position += data.center;
		GetEntity()->GetComponent<Transform>().scale *= data.radius / 2.2f;
	}
}

void SphereCollider::UpDate()
{
	
}

void SphereCollider::Render2D()
{
}

void SphereCollider::Render3D()
{
}
