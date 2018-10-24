#include "CapsuleCollider.h"
#include "../../src/Component/ModelRender/ModelRender.h"
#include "../../src/Component/Transform/Transform.h"
#include "../../src/GameSystem/ECS/Entity/Entity.h"


CapsuleCollider::CapsuleCollider()
{
	data.radius = 1.0f;
	data.height = 2.0f;
	data.center = Math::Vector3(0, 0, 0);
}

CapsuleCollider::CapsuleCollider(const Segment & segment, const float radius)
{
	data.radius = radius;
	this->segment = segment;
	data.height = 2.0f;
	data.center = Math::Vector3(0, 0, 0);
}

const Segment & CapsuleCollider::GetSegment() const
{
	return segment;
}

const float CapsuleCollider::GetRadius() const
{
	return data.radius;
}

void CapsuleCollider::Initialize()
{
	//GetEntity()->AddComponent<Material>(Math::Vector4(1, 1, 1, 1));
	//GetEntity()->GetComponent<Material>().LoadShaderFile("./data/shaderData/diffuseShader");
	GetEntity()->AddComponent<ModelRender>(new FbxModel("./data/model/sphere.fbx"));
	GetEntity()->GetComponent<ModelRender>().SetDrawMode(D3D11_FILL_WIREFRAME);
	if (GetEntity()->HasComponent<Transform>())
	{
		GetEntity()->GetComponent<Transform>().position += data.center;
		GetEntity()->GetComponent<Transform>().scale.y *= data.height;
	}

}

void CapsuleCollider::UpDate()
{
	
}

void CapsuleCollider::Render2D()
{
}

void CapsuleCollider::Render3D()
{
}
