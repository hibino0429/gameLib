#pragma once
#include <atlbase.h>
#include <vector>
#include <array>
#include "../../src/GameSystem/ECS/Entity/Entity.h"



using Group = std::size_t;
class Entity;
//---------------------------------------------------------------------------------
//!@class		EntityManager
//!@brief	�G���e�B�e�B�̊Ǘ���
//!@brief	�G���e�B�e�B�̍X�V�E�`��
//!@brief	�G���e�B�e�B�̓o�^�E�폜
//---------------------------------------------------------------------------------
class EntityManager
{
public:
	~EntityManager();
public:
	//!@brief	������
	void	Initialize();
	//!@brief	�X�V
	void	UpDate();
	//!@brief	�`��2D
	void	Render2D();
	//!@brief	�`��3D
	void	Render3D();

	//!@brief	Entity�̍폜
	//!@brief	�o�^���Ă���Entity��active�łȂ����̂��폜
	void	Refresh();

	//!@brief	�O���[�v�̎擾
	//!@param[in]	group	�O���[�v
	//!@return	�ێ����Ă���Entity�̎Q��
	std::vector<Entity*>&	GetGroup(const Group& group);
	//!@brief	�O���[�v�̒ǉ�
	void	AddGroup(Entity* entity, const Group& group);
	//!@brief	Entity�̒ǉ�
	//!@return	�ǉ�����Entity�̎Q��
	Entity&	AddEntity();
	//!@brief	Entity�������Ƀ^�O��ǉ�
	//!@param[in]	tag	�^�O
	Entity&	AddEntityAddTag(const std::string& tag);
	//!@brief	�w�肵���^�O��Entity���擾
	Entity&	GetEntity(const std::string& tag);
private:
	std::vector<Entity*>	entities;
	std::array<std::vector<Entity*>, MaxGroups>	groupEntities;
};




class Manager
{
public:
	//!@brief	EntityManager�̎擾
	static  EntityManager&	GetEntityManager()
	{
		static EntityManager	entityManager;
		return entityManager;
	}
};