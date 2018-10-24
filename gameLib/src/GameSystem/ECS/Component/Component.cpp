#include "Component.h"


//!@brief	エンティティのセット
//!@param[in]	entity	エンティティ
void	Component::SetEntity(Entity* entity)
{
	this->entity = entity;
}
//!@brief	エンティティの取得
//!@return	エンティティ
Entity*	Component::GetEntity() const
{
	return entity;
}

bool	Component::IsActive() const
{
	return active;
}

void	Component::DeleteThis()
{
	active = false;
}