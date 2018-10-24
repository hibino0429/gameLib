#pragma once
#include <atlbase.h>
#include <vector>
#include <bitset>
#include <assert.h>
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/GameSystem/ECS/EntityManager/EntityManager.h"



using Group = std::size_t;

using ComponentArray = std::array<Component*, MaxComponents>;
using ComponentBitSet = std::bitset<MaxComponents>;
using GroupBitSet = std::bitset<MaxGroups>;


class EntityManager;
//---------------------------------------------------------------------------------
//!@class		Entity
//!@brief	��̃I�u�W�F�N�g
//!@brief	��̃I�u�W�F�N�g�ɂ��̂�ǉ����Ă���
//---------------------------------------------------------------------------------
class Entity
{
public:
	//!@brief	�R���X�g���N�^
	//!@param[in]	entityManager	�G���e�B�e�B�}�l�[�W���[
	Entity(EntityManager& entityManager);
	//!@brief	�f�X�g���N�^
	~Entity();
public:
	//!@brief	�����Ă��邩�̃`�F�b�N
	//!@return	true: �����Ă��� false: ����ł���
	bool	IsActive() const;
	//!@brief	�j��
	void	Destory();
	//!@brief	������
	void	Initialize();
	//!@brief	�X�V
	void	UpDate();
	//!@brief	�`��2D
	void	Render2D();
	//!@brief	�`��3D
	void	Render3D();
	//!@brief	�R���|�[�l���g��ێ����Ă��邩�̃`�F�b�N
	//!@return	true: �ێ����Ă��� false: �ێ����Ă��Ȃ�
	template<typename Type>
	bool	HasComponent() const
	{
		return componentBitSet[ComSystem::GetComponentTypeID<Type>()];
	}

	//!@brief	�R���|�[�l���g�̒ǉ�
	//!@param[in]	args	�ǉ�����R���|�[�l���g
	//!@return	�ǉ������R���|�[�l���g�̎Q��
	template<typename Type, typename... TArgs>
	Type&	AddComponent(TArgs&&... args)
	{
		//�d���͕s��
		if (HasComponent<Type>())
		{
			return GetComponent<Type>();
		}
		Type*	component(new Type(std::forward<TArgs>(args)...));
		component->SetEntity(this);
		components.emplace_back(component);

		componentArray[ComSystem::GetComponentTypeID<Type>()] = component;
		componentBitSet[ComSystem::GetComponentTypeID<Type>()] = true;

		component->Initialize();
		return *component;
	}

	//!@brief	�R���|�[�l���g�̎擾
	//!@return	�擾�����R���|�[�l���g�̎Q��
	template<typename Type>
	Type&	GetComponent() const
	{
		//assert(!HasComponent<Type>());
		if (HasComponent<Type>())
		{
			auto ptr(componentArray[ComSystem::GetComponentTypeID<Type>()]);
			return *static_cast<Type*>(ptr);
		}
		return *static_cast<Type*>(nullptr);
	}
	//!@brief	�w�肵���R���|�[�l���g���폜
	template<typename Type>
	void	DeleteComponent()
	{
		if (HasComponent<Type>())
		{
			GetComponent<Type>().DeleteThis();
			componentBitSet[ComSystem::GetComponentTypeID<Type>()] = false;
		}
	}

	//!@brief	�O���[�v�������Ă��邩
	//!@param[in]	group	�O���[�v
	//!return	true: �O���[�v��ێ� false: �O���[�v��ێ����Ă��Ȃ�
	bool	HasGroup(const Group& group);
	//!@brief	�O���[�v�̒ǉ�
	//!@brief	�����Ŏw�肵���O���[�v�ɒǉ�����
	//!@param[in]	group	�O���[�v
	void	AddGroup(const Group& group);
	//!@brief	�O���[�v����̍폜
	//!@brief	�����Ŏw�肵���O���[�v����폜����
	//!@param[in]	group	�O���[�v
	void	DeleteGroup(const Group& group);
	//!@brief	�^�O�̐ݒ�
	//!@param[in]	tag	�^�O
	void	SetTag(const std::string& tag);
	//!@brief	�^�O�̎擾
	const std::string&	GetTag() const;
private:
	bool					active;
	EntityManager&			entityManager;
	std::vector<Component*>	components;
	ComponentArray		componentArray;
	ComponentBitSet		componentBitSet;
	GroupBitSet			groupBitSet;
	std::string			tag;
};