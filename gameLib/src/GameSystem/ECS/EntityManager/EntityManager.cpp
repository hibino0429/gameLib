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
//!@brief	�X�V
void	EntityManager::UpDate()
{
	for (auto& entity : entities)
	{
		entity->UpDate();
	}
}
//!@brief	�`��
void	EntityManager::Render2D()
{
	for (auto& entity : entities)
	{
		entity->Render2D();
	}
}

//!@brief	�`��3D
void	EntityManager::Render3D()
{
	for (auto& entity : entities)
	{
		entity->Render3D();
	}
}

//!@brief	Entity�̍폜
//!@brief	�o�^���Ă���Entity��active�łȂ����̂��폜
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

//!@brief	�O���[�v�̎擾
//!@param[in]	group	�O���[�v
//!@return	�ێ����Ă���Entity�̎Q��
std::vector<Entity*>&	EntityManager::GetGroup(const Group& group)
{
	return groupEntities[group];
}
//!@brief	�O���[�v�̒ǉ�
void	EntityManager::AddGroup(Entity* entity, const Group& group)
{
	groupEntities[group].emplace_back(entity);
}
//!@brief	Entity�̒ǉ�
//!@return	�ǉ�����Entity�̎Q��
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
	MessageBoxA(nullptr, "tag��Entity������܂���", "GetEntity()", MB_OK);
	assert(false);
	return *entities[0];
}
