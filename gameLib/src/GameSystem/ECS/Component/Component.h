#pragma once
#include <atlbase.h>
#include <bitset>


using ComponentID = std::size_t;

constexpr std::size_t MaxComponents = 32;
constexpr std::size_t MaxGroups = 32;


class Entity;
//---------------------------------------------------------------------------------
//!@class		Component
//!@brief	�R���|�[�l���g������
//!@brief	�@�\��ǉ����Ă���
//---------------------------------------------------------------------------------
class Component
{
public:
	virtual ~Component() {}
	virtual void	Initialize() = 0;
	virtual void	UpDate() = 0;
	virtual void	Render2D() = 0;
	virtual void	Render3D() = 0;

	//!@brief	�G���e�B�e�B�̃Z�b�g
	//!@param[in]	entity	�G���e�B�e�B
	void	SetEntity(Entity* entity);
	//!@brief	�G���e�B�e�B�̎擾
	//!@return	�G���e�B�e�B
	Entity*	GetEntity() const;
	//!@brief	�R���|�[�l���g�����邩�`�F�b�N
	//!@return	true: ���� false: �Ȃ�
	virtual bool	IsActive() const;
private:
	//!@brief	���g���폜
	void	DeleteThis();
private:
	Entity*		entity;
	bool		active = true;
};


namespace ComSystem
{
	inline ComponentID&	GetNewComponentTypeID()
	{
		static ComponentID lastID = 0;
		return ++lastID;
	}
	template<typename Type>
	inline ComponentID&	GetComponentTypeID() noexcept
	{
		static ComponentID	typeID = GetNewComponentTypeID();
		return typeID;
	}
}