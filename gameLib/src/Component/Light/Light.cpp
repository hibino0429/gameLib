#include "Light.h"
#include "../../Utility/Utility.hpp"


Light::Light(const LightType & lightType, const Math::Vector3 & lightColor)
{
	data.type = lightType;
	data.color = lightColor;
}

void Light::Initialize()
{
	/*material = material = new Material(Math::Vector4(data.color.x,data.color.y,data.color.z, 1));
	switch (data.type) {
	case LightType::Directional:
		cBuffer = new ConstantBuffer(sizeof(DirLightCBuffer));
		material->LoadShaderFile("./data/shaderData/DirectionalLight");
		break;
	case LightType::Point:
		cBuffer = new ConstantBuffer(sizeof(PointLightCBuffer));
		material->LoadShaderFile("./data/shaderData/PointLight");
		break;
	default:
		break;
	}*/
}

void Light::UpDate()
{
	//material->UpDate();
}

void Light::Render2D()
{
}

void Light::Render3D()
{
	//material->Render3D();
	//cBuffer->Render();
}

const LightData& Light::GetLightData() const
{
	return data;
}

const TransMatrix& Light::GetTransMat() const
{
	return transMat;
}


void Light::SetMatrix(const TransMatrix& transMatrix)
{
	transMat = transMatrix;
}



//平行光源
DirectionalLight::DirectionalLight()
{
	light = new Light(LightType::Directional, Math::Vector3(1, 1, 1));
	data.lightDir = Math::Vector3(1,0,1);
}

DirectionalLight::DirectionalLight(const Math::Vector3 & lightDir)
{
	light = new Light(LightType::Directional, Math::Vector3(1,1,1));
	data.lightDir = lightDir;
}

DirectionalLight::DirectionalLight(const Math::Vector3 & lightDir, const Math::Vector3 & lightColor)
{
	light = new Light(LightType::Directional, lightColor);
	data.lightDir = lightDir;
}

DirectionalLight::~DirectionalLight()
{
	Utility::SafeDelete(light);
}

void DirectionalLight::Initialize()
{
	light->Initialize();
	data.lightDir.Normalize();
}

void DirectionalLight::UpDate()
{
	light->UpDate();
}

void DirectionalLight::Render2D()
{
	light->Render2D();
}

void DirectionalLight::Render3D()
{
	light->Render3D();
}

const Math::Vector3 & DirectionalLight::GetLightDir() const
{
	return data.lightDir;
}

const Math::Vector3 & DirectionalLight::GetLightColor() const
{
	return light->GetLightData().color;
}

void DirectionalLight::SetLightDir(const Math::Vector3 & lightDir)
{
	data.lightDir = lightDir;
}

void DirectionalLight::SetMatrix(const TransMatrix & transMatrix)
{
	light->SetMatrix(transMatrix);
}




//ポイントライト
PointLight::PointLight()
{
	data.pos = Math::Vector3(0, 0, 0);
	data.attenuation = 255.0f / 255.0f;
	light = new Light(LightType::Point, Math::Vector3(1, 1, 1));
}

PointLight::PointLight(const Math::Vector3 & pos, const Math::Vector3 & attenuation)
{
	data.pos = pos;
	data.attenuation = attenuation;
	light = new Light(LightType::Point, Math::Vector3(1, 1, 1));
}

PointLight::~PointLight()
{
	Utility::SafeDelete(light);
}

void PointLight::Initialize()
{
	light->Initialize();
}

void PointLight::UpDate()
{
	light->UpDate();

	PointLightCBuffer	cb;
	DirectX::XMStoreFloat4x4(&cb.world, DirectX::XMMatrixTranspose(light->GetTransMat().worldMat));
	DirectX::XMStoreFloat4x4(&cb.view, DirectX::XMMatrixTranspose(light->GetTransMat().viewMat));
	DirectX::XMStoreFloat4x4(&cb.projection, DirectX::XMMatrixTranspose(light->GetTransMat().projMat));
	DirectX::XMStoreFloat4(&cb.lightPos, DirectX::XMVECTOR(data.pos));
	DirectX::XMStoreFloat4(&cb.attenuation, DirectX::XMVECTOR(data.attenuation));
	DirectX::XMStoreFloat4(&cb.lightColor, DirectX::XMVECTOR(light->GetLightData().color));
	//light->GetConstantBuffer().UpDate(&cb);
}

void PointLight::Render2D()
{
	light->Render2D();
}

void PointLight::Render3D()
{
	light->Render3D();
}
