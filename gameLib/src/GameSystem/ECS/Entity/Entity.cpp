#include "Entity.h"


//!@brief	�R���X�g���N�^
	//!@param[in]	entityManager	�G���e�B�e�B�}�l�[�W���[
Entity::Entity(EntityManager& entityManager)
	:entityManager(entityManager)
	, active(true)
{
	
}

Entity::~Entity()
{
	for (auto& com : components)
	{
		delete com;
		com = nullptr;
	}
}

//!@brief	�����Ă��邩�̃`�F�b�N
//!@return	true: �����Ă��� false: ����ł���
bool	Entity::IsActive() const
{
	return active;
}
//!@brief	�j��
void	Entity::Destory()
{
	active = false;
}

//!@brief	������
void	Entity::Initialize()
{
	for (auto& com : components)
	{
		com->Initialize();
	}
}
//!@brief	�X�V
void	Entity::UpDate()
{
	for (auto& com : components)
	{
		com->UpDate();
	}
}
//!@brief	�`��
void	Entity::Render2D()
{
	for (auto& com : components)
	{
		com->Render2D();
	}
}

//!@brief	�`��3D
void	Entity::Render3D()
{
	for (auto& com : components)
	{
		com->Render3D();
	}
}



//!@brief	�O���[�v�������Ă��邩
//!@param[in]	group	�O���[�v
//!return	true: �O���[�v��ێ� false: �O���[�v��ێ����Ă��Ȃ�
bool	Entity::HasGroup(const Group& group)
{
	return groupBitSet[group];
}	

//!@brief	�O���[�v�̒ǉ�
//!@brief	�����Ŏw�肵���O���[�v�ɒǉ�����
//!@param[in]	group	�O���[�v
void	Entity::AddGroup(const Group& group)
{
	groupBitSet[group] = true;
	entityManager.AddGroup(this, group);
}

//!@brief	�O���[�v����̍폜
//!@brief	�����Ŏw�肵���O���[�v����폜����
//!@param[in]	group	�O���[�v
void	Entity::DeleteGroup(const Group& group)
{
	groupBitSet[group] = false;
}

void Entity::SetTag(const std::string & tag)
{
	this->tag = tag;
}

const std::string & Entity::GetTag() const
{
	return tag;
}
