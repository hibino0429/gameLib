#include "Material.h"
#include "../../src/Utility/Utility.hpp"
#include "../../src/DXEngine/DXEngine/DXEngine.h"
#include "../../src/GameSystem/ECS/Entity/Entity.h"
#include "../../src/Component/ModelRender/ModelRender.h"


Material::Material(const Math::Vector4& color)
{
	Engine<DXDevice>::GetDevice().COMInitialize();
	data.texture = nullptr;
	data.vertexShader = nullptr;
	data.pixelShader = nullptr;
	data.diffuseColor = color;

}

Material::Material(Texture* texture)
{
	Engine<DXDevice>::GetDevice().COMInitialize();
	data.texture = texture;
	data.vertexShader = nullptr;
	data.pixelShader = nullptr;
	data.diffuseColor = Math::Vector4(1, 1, 1, 1);
}


Material::~Material()
{
	Utility::SafeDelete(data.vertexShader);
	Utility::SafeDelete(data.pixelShader);
}

void Material::ChangeTexture(Texture* texture)
{
	data.texture = texture;
}

const Math::Vector4 & Material::GetColor() const
{
	return data.diffuseColor;
}



bool Material::SetShader(Shader * shader)
{
	this->shader = shader;
	return false;
}

void Material::Initialize()
{
	if (GetEntity()->HasComponent<ModelRender>())
	{
		GetEntity()->GetComponent<ModelRender>().SetColor(data.diffuseColor);
	}
}

void Material::UpDate()
{
	if (!Utility::CheckNull(shader))
	{
		shader->UpDate();
	}
	if (Utility::CheckNull(data.texture)) { return; }
	data.texture->Attach(0);
}

void Material::Render2D()
{
}

void Material::Render3D()
{
	if (Utility::CheckNull(data.texture)) { return; }
	data.texture->Render();
}
