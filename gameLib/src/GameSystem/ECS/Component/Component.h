#pragma once
#include <atlbase.h>
#include <bitset>


using ComponentID = std::size_t;

constexpr std::size_t MaxComponents = 32;
constexpr std::size_t MaxGroups = 32;


class Entity;
//---------------------------------------------------------------------------------
//!@class		Component
//!@brief	コンポーネントを扱う
//!@brief	機能を追加していく
//---------------------------------------------------------------------------------
class Component
{
public:
	virtual ~Component() {}
	virtual void	Initialize() = 0;
	virtual void	UpDate() = 0;
	virtual void	Render2D() = 0;
	virtual void	Render3D() = 0;

	//!@brief	エンティティのセット
	//!@param[in]	entity	エンティティ
	void	SetEntity(Entity* entity);
	//!@brief	エンティティの取得
	//!@return	エンティティ
	Entity*	GetEntity() const;
	//!@brief	コンポーネントがあるかチェック
	//!@return	true: ある false: ない
	virtual bool	IsActive() const;
private:
	//!@brief	自身を削除
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