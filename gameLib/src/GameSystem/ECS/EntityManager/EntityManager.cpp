#include "EntityManager.h"


EntityManager::~EntityManager()
{
	for (auto& entity : entities)
	{
		entity->Destory();
	}
	this->Refresh();
}

void	EntityManager::Initialize()
{
	for (auto& entity : entities)
	{
		entity->Initialize();
	}
}
//!@brief	更新
void	EntityManager::UpDate()
{
	for (auto& entity : entities)
	{
		entity->UpDate();
	}
}
//!@brief	描画
void	EntityManager::Render2D()
{
	for (auto& entity : entities)
	{
		entity->Render2D();
	}
}

//!@brief	描画3D
void	EntityManager::Render3D()
{
	for (auto& entity : entities)
	{
		entity->Render3D();
	}
}

//!@brief	Entityの削除
//!@brief	登録しているEntityでactiveでないものを削除
void	EntityManager::Refresh()
{
	/*for (auto i(0u); i < MaxGroups; ++i)
	{
		auto& groupEntity(groupEntities[i]);
		groupEntity.erase(
			std::remove_if(std::begin(groupEntity), std::end(groupEntity),
				[i](Entity* entity)
		{
			return !entity->IsActive() || !entity->HasGroup(i);
		}),
			std::end(groupEntity)
			);

		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const Entity* entity)
		{
			return !entity->IsActive();
		}),
			std::end(entities)
		);
	}*/
	entities.erase(std::remove_if(std::begin(entities), std::end(entities),
		[](const Entity* entity)
	{
		return !entity->IsActive();
	}),
		std::end(entities));
}

//!@brief	グループの取得
//!@param[in]	group	グループ
//!@return	保持しているEntityの参照
std::vector<Entity*>&	EntityManager::GetGroup(const Group& group)
{
	return groupEntities[group];
}
//!@brief	グループの追加
void	EntityManager::AddGroup(Entity* entity, const Group& group)
{
	groupEntities[group].emplace_back(entity);
}
//!@brief	Entityの追加
//!@return	追加したEntityの参照
Entity&	EntityManager::AddEntity()
{
	Entity*	entity = new Entity(*this);
	entity->SetTag("");
	entities.emplace_back(entity);
	return *entity;
}

Entity & EntityManager::AddEntityAddTag(const std::string & tag)
{
	Entity*	entity = new Entity(*this);
	entity->SetTag(tag);
	entities.emplace_back(entity);
	return *entity;
}

Entity & EntityManager::GetEntity(const std::string & tag)
{
	for (const auto& it : entities)
	{
		if (it->GetTag() == tag)
		{
			return *it;
		}
	}
	MessageBoxA(nullptr, "tagのEntityがありません", "GetEntity()", MB_OK);
	assert(false);
	return *entities[0];
}
