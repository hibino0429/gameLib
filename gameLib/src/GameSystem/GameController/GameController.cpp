#include "GameController.h"
#include "../../src/Component/Transform/Transform.h"
#include "../../src/DXEngine/Sprite/Sprite.h"
#include "../../src/Component/ModelRender/ModelRender.h"
#include "../../src/Component/Light/Light.h"
#include "../../src/Component/Material/Material.h"
#include "../../src/Component/Camera/Camera.h"
#include "../../src/Component/ParticleSystem/ParticleSystem.h"
#include "../../src/Component/SpriteAnimation/SpriteAnimation.h"
#include "../../src/Component/Collision/SphereCollider/SphereCollider.h"
#include "../../src/Component/Collision/CapsuleCollider/CapsuleCollider.h"
#include "../../src/Component/Collision/BoxCollider/BoxCollider.h"
#include "../../src/Component/Collision/CollisionData/CollisionCheck.hpp"
#include "../../src/Component/Move/MoveCamera.h"
#include "../../src/GameSrc/Move/MovePlayer.h"
#include "../../src/GameSrc/Map/Map.h"


//!@brief	コンストラクタ
GameController::GameController()
{
	//Entityの生成
	mainCamera = &Manager::GetEntityManager().AddEntityAddTag("Camera");
	light = &Manager::GetEntityManager().AddEntityAddTag("DirectionalLight");
	player = &Manager::GetEntityManager().AddEntity();
	enemy = &Manager::GetEntityManager().AddEntity();
	obj = &Manager::GetEntityManager().AddEntity();
	
	//Assetのロード
	//texList = textureLoader.LoadAssetList("./data/loadFile/textureData.txt");
	//modelList = modelLoader.LoadAssetList("./data/loadFile/modelData.txt");
	////AssetListを登録する
	//manager.RegistAssetList<Texture>("texture", texList);
	//manager.RegistAssetList<FbxModel>("model", modelList);
	shaderList = new AssetList<Shader*>();
	shaderList->Regist(0, new Shader("./data/shaderData/diffuseShader"));
	shaderList->Regist(1, new Shader("./data/shaderData/mesh"));
	shaderList->GetAsset(0)->CreateColorShaderParam();
	shaderList->GetAsset(1)->CreateTextureShaderParam();
	//manager.RegistAssetList<Shader>("shader", shaderList);

	modelList = new AssetList<FbxModel*>();
	modelList->Regist(0, new FbxModel("./data/model/ufo.fbx"));
	modelList->Regist(1, new FbxModel("./data/model/ball.fbx"));

	texList = new AssetList<Texture*>();
	texList->Regist(0, new Texture("./data/image/UFO_D.png"));
	texList->Regist(1, new Texture("./data/image/texture.png"));
	texList->Regist(2, new Texture("./data/image/star.png"));

	//メインカメラ
	mainCamera->AddComponent<Transform>(Math::Vector3(10, 0, 150), Math::Vector3(0, -170, 0), Math::Vector3(1, 1, 1));
	mainCamera->AddComponent<Camera>(Math::Vector3(0, 0, 150), Math::Vector3(0, 0, -20.0f));
	mainCamera->AddComponent<MoveInput>();

	//ライト
	light->AddComponent<DirectionalLight>();
	light->AddComponent<Transform>(Math::Vector3(0,-10,-50),Math::Vector3(0,0,0),Math::Vector3(1,1,1));
	light->AddComponent<ModelRender>(modelList->GetAsset(1));
	light->AddComponent<Material>(Math::Vector4(1,0,0,1));
	light->GetComponent<Material>().SetShader(shaderList->GetAsset(1));


	//コンポーネントの追加
	player->AddComponent<Transform>(Math::Vector3(0, -20, -80), Math::Vector3(0, 0, 0), Math::Vector3(1, 1, 1));
	player->AddComponent<ModelRender>(modelList->GetAsset(0));
	player->AddComponent<Material>(texList->GetAsset(2));
	player->GetComponent<Material>().SetShader(shaderList->GetAsset(1));

	enemy->AddComponent<Transform>(Math::Vector3(10, 10, -40), Math::Vector3(0, 0, 0), Math::Vector3(1, 1, 1));
	enemy->AddComponent<MovePlayer>();
	//enemy->AddComponent<BoxCollider>(Math::Vector3(0, 0, 0), Math::Vector3(10, 10, 10));

	obj->AddComponent<Transform>(Math::Vector3(0, 10, -40), Math::Vector3(90, 0, 0), Math::Vector3(10, 10, 10));
	obj->AddComponent<ModelRender>(modelList->GetAsset(1));
	obj->AddComponent<Material>(Math::Vector4(0, 1, 0, 1));
	obj->GetComponent<Material>().SetShader(shaderList->GetAsset(0));
	//obj->AddComponent<BoxCollider>(Math::Vector3(0, 0, 0), Math::Vector3(10, 10, 10));

	audio.SetMasterGain(0.5f);

	source = new AudioSystem::AudioSource();
 	source->Load("data/sound/Town.ogg", false);
	//source->SetLoopPoint(0u, 500000u);
	source->PlayBGM();
	source->SetVolume(0.3f);

	dKey = new DirectKey(Engine<DXDevice>::GetDevice().GetScreen().GetHWND());

	//グループの追加
	player->AddGroup(Always);
}

//!@brief	デストラクタ
GameController::~GameController()
{
	//Entityの削除
	Utility::SafeDelete(player);
	Utility::SafeDelete(light);
	Utility::SafeDelete(mainCamera);
	Utility::SafeDelete(particle);
	Utility::SafeDelete(enemy);
	Utility::SafeDelete(obj);
	Utility::SafeDelete(source);

	Utility::SafeDelete(dKey);
	//削除する際は、登録したAssestList分行う必要がある
	//manager.Delete<Texture>();
	//manager.Delete<FbxModel>();
	Utility::SafeDelete(texList);
	Utility::SafeDelete(modelList);
	Utility::SafeDelete(shaderList);
}

//!@brief	初期化
void	GameController::Initialize()
{
	Manager::GetEntityManager().Initialize();
}

//!@brief	終了
void	GameController::Finalize()
{
	Manager::GetEntityManager().Refresh();
}

//!@brief	更新
void	GameController::UpDate()
{
	Manager::GetEntityManager().Refresh();
	Manager::GetEntityManager().UpDate();


	/*if (CollisionWorld::CheckSphereToSphere(obj->GetComponent<SphereCollider>(), enemy->GetComponent<SphereCollider>()))
	{
		std::cout << "衝突" << std::endl;
	}*/
	//if (CollisionWorld::CheckBoxToBox(obj->GetComponent<BoxCollider>(), enemy->GetComponent<BoxCollider>()))
	{
		std::cout << "衝突" << std::endl;
	}
	if (dKey->Press(DirectKey::Key::A))
	{
		obj->GetComponent<Transform>().position.x -= 0.2f;
	}
	if (dKey->Press(DirectKey::Key::D))
	{
		obj->GetComponent<Transform>().position.x += 0.2f;
	}
	if (dKey->Press(DirectKey::Key::W))
	{
		obj->GetComponent<Transform>().position.y += 0.2f;
	}
	if (dKey->Press(DirectKey::Key::S))
	{
		obj->GetComponent<Transform>().position.y -= 0.2f;
	}

}

//!@brief	描画2D
void	GameController::Render2D()
{
	//Manager::GetEntityManager().Render2D();
}

//!@brief	描画3D
void	GameController::Render3D()
{
	Manager::GetEntityManager().Render3D();
}