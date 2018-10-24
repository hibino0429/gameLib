#pragma once
#include <atlbase.h>
#include <vector>
#include <array>
#include "../../src/GameSystem/ECS/Entity/Entity.h"



using Group = std::size_t;
class Entity;
//---------------------------------------------------------------------------------
//!@class		EntityManager
//!@brief	エンティティの管理部
//!@brief	エンティティの更新・描画
//!@brief	エンティティの登録・削除
//---------------------------------------------------------------------------------
class EntityManager
{
public:
	~EntityManager();
public:
	//!@brief	初期化
	void	Initialize();
	//!@brief	更新
	void	UpDate();
	//!@brief	描画2D
	void	Render2D();
	//!@brief	描画3D
	void	Render3D();

	//!@brief	Entityの削除
	//!@brief	登録しているEntityでactiveでないものを削除
	void	Refresh();

	//!@brief	グループの取得
	//!@param[in]	group	グループ
	//!@return	保持しているEntityの参照
	std::vector<Entity*>&	GetGroup(const Group& group);
	//!@brief	グループの追加
	void	AddGroup(Entity* entity, const Group& group);
	//!@brief	Entityの追加
	//!@return	追加したEntityの参照
	Entity&	AddEntity();
	//!@brief	Entity生成時にタグを追加
	//!@param[in]	tag	タグ
	Entity&	AddEntityAddTag(const std::string& tag);
	//!@brief	指定したタグのEntityを取得
	Entity&	GetEntity(const std::string& tag);
private:
	std::vector<Entity*>	entities;
	std::array<std::vector<Entity*>, MaxGroups>	groupEntities;
};




class Manager
{
public:
	//!@brief	EntityManagerの取得
	static  EntityManager&	GetEntityManager()
	{
		static EntityManager	entityManager;
		return entityManager;
	}
};