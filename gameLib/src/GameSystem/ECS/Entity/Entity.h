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
//!@brief	空のオブジェクト
//!@brief	空のオブジェクトにものを追加していく
//---------------------------------------------------------------------------------
class Entity
{
public:
	//!@brief	コンストラクタ
	//!@param[in]	entityManager	エンティティマネージャー
	Entity(EntityManager& entityManager);
	//!@brief	デストラクタ
	~Entity();
public:
	//!@brief	生きているかのチェック
	//!@return	true: 生きている false: 死んでいる
	bool	IsActive() const;
	//!@brief	破棄
	void	Destory();
	//!@brief	初期化
	void	Initialize();
	//!@brief	更新
	void	UpDate();
	//!@brief	描画2D
	void	Render2D();
	//!@brief	描画3D
	void	Render3D();
	//!@brief	コンポーネントを保持しているかのチェック
	//!@return	true: 保持している false: 保持していない
	template<typename Type>
	bool	HasComponent() const
	{
		return componentBitSet[ComSystem::GetComponentTypeID<Type>()];
	}

	//!@brief	コンポーネントの追加
	//!@param[in]	args	追加するコンポーネント
	//!@return	追加したコンポーネントの参照
	template<typename Type, typename... TArgs>
	Type&	AddComponent(TArgs&&... args)
	{
		//重複は不可
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

	//!@brief	コンポーネントの取得
	//!@return	取得したコンポーネントの参照
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
	//!@brief	指定したコンポーネントを削除
	template<typename Type>
	void	DeleteComponent()
	{
		if (HasComponent<Type>())
		{
			GetComponent<Type>().DeleteThis();
			componentBitSet[ComSystem::GetComponentTypeID<Type>()] = false;
		}
	}

	//!@brief	グループを持っているか
	//!@param[in]	group	グループ
	//!return	true: グループを保持 false: グループを保持していない
	bool	HasGroup(const Group& group);
	//!@brief	グループの追加
	//!@brief	引数で指定したグループに追加する
	//!@param[in]	group	グループ
	void	AddGroup(const Group& group);
	//!@brief	グループからの削除
	//!@brief	引数で指定したグループから削除する
	//!@param[in]	group	グループ
	void	DeleteGroup(const Group& group);
	//!@brief	タグの設定
	//!@param[in]	tag	タグ
	void	SetTag(const std::string& tag);
	//!@brief	タグの取得
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