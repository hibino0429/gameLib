#include "Component.h"


//!@brief	�G���e�B�e�B�̃Z�b�g
//!@param[in]	entity	�G���e�B�e�B
void	Component::SetEntity(Entity* entity)
{
	this->entity = entity;
}
//!@brief	�G���e�B�e�B�̎擾
//!@return	�G���e�B�e�B
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