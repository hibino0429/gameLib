#pragma once

class EntityManager;
class Entity;



struct Prefab
{
	EntityManager	entityManager;
	//!@brief	パーティクルの生成
	Entity&		CreateParticle(const std::string& filePath)
	{
		Entity*	particle = &entityManager->AddEntity();
		particle->AddComponent<Transform>(Math::Vector3(0, 0, -20), Math::Vector3(0, 0, 0), Math::Vector3(10, 10, 10));
		particle->AddComponent<ParticleSystem>(filePath);
		return particle;
	}

	//!@brief	カメラの生成
	Entity&		CreateCamera()
	{
		Entity*	camera = &entityManager->AddEntity();
		camera->AddComponent<Transform>(Math::Vector3(0, 0, 150), Math::Vector3(0, 0, 0), Math::Vector3(1, 1, 1));
		camera->AddComponent<Camera>(Math::Vector3(0, 0, 150), Math::Vector3(0, 0, -20.0f));
		return camera;
	}

	//!@brief	DirectionalLightの生成
	Entity&		CreateDirectionalLight()
	{
		Entity*	light = &entityManager->AddEntity();
		light->AddComponent<DirectionalLight>();
		light->AddComponent<Transform>(Math::Vector3(0, -10, -50), Math::Vector3(0, 0, 0), Math::Vector3(1, 1, 1));
		light->AddComponent<Material>(Math::Vector4(1, 1, 0, 1));
		light->GetComponent<Material>().LoadShaderFile("./data/shaderData/diffuseShader");
		light->AddComponent<ModelRender>("./data/model/ball.fbx");
		return light;
	}
};