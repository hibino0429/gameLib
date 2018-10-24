#pragma once
#include "../../src/GameSystem/ECS/Entity/Entity.h"
#include "../../src/GameSystem/ECS/EntityManager/EntityManager.h"
#include "../../src/Utility/Utility.hpp"

#include "../../src/GameSystem/XInput/XInput.h"
#include "../../src/Component/Assset/AssetManager/AssetManager.h"
#include "../../src/Component/Assset/LoadAsset/LoadAsset.h"
#include "../../src/DXEngine/Texture/Texture.h"
#include "../../src/DXEngine/Model/Model.h"
#include "../../src/Bullet/BulletWorld.h"
#include "../../src/GameSystem/DirectInput/DirectKey/DirectKey.h"
#include "../../src/Component/Material/Shader.h"
#include "../../src/DXEngine/Sound/Audio.h"
#include "../../src/DXEngine/Sound/AudioSource.h"


class GameController
{
private:
	enum class GameState
	{
		Play,
		Stop
	};
	enum GameGroup : std::size_t
	{
		Always,			//常に更新
		DuringGame,		//ゲーム中
		Non,			//なし
	};
public:
	//!@brief	コンストラクタ
	GameController();
	//!@brief	デストラクタ
	~GameController();

	//!@brief	初期化
	void	Initialize();
	//!@brief	終了
	void	Finalize();
	//!@brief	更新
	void	UpDate();
	//!@brief	描画2D
	void	Render2D();
	//!@brief	描画3D
	void	Render3D();
private:
	GameState		gameState;
	
	Entity*			player;
	Entity*			enemy;

	Entity*			mainCamera;
	Entity*			light;
	Entity*			particle;
	Entity*			obj;

private:
	XInput*			xInput;
	DirectKey*		dKey;
private:
	LoadAsset<Texture>		textureLoader;
	LoadAsset<FbxModel>		modelLoader;
	//LoadAsset<Shader>	shaderLoader;

	AssetList<Texture*>*	texList;
	AssetList<FbxModel*>*	modelList;
	AssetList<Shader*>*		shaderList;
	AssetManager			manager;		//アセット管理部

	AudioSystem::Audio			audio;
	AudioSystem::AudioSource*	source;
};
