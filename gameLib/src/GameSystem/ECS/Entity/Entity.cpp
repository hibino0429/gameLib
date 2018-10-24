#include "Entity.h"


//!@brief	コンストラクタ
	//!@param[in]	entityManager	エンティティマネージャー
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

//!@brief	生きているかのチェック
//!@return	true: 生きている false: 死んでいる
bool	Entity::IsActive() const
{
	return active;
}
//!@brief	破棄
void	Entity::Destory()
{
	active = false;
}

//!@brief	初期化
void	Entity::Initialize()
{
	for (auto& com : components)
	{
		com->Initialize();
	}
}
//!@brief	更新
void	Entity::UpDate()
{
	for (auto& com : components)
	{
		com->UpDate();
	}
}
//!@brief	描画
void	Entity::Render2D()
{
	for (auto& com : components)
	{
		com->Render2D();
	}
}

//!@brief	描画3D
void	Entity::Render3D()
{
	for (auto& com : components)
	{
		com->Render3D();
	}
}



//!@brief	グループを持っているか
//!@param[in]	group	グループ
//!return	true: グループを保持 false: グループを保持していない
bool	Entity::HasGroup(const Group& group)
{
	return groupBitSet[group];
}	

//!@brief	グループの追加
//!@brief	引数で指定したグループに追加する
//!@param[in]	group	グループ
void	Entity::AddGroup(const Group& group)
{
	groupBitSet[group] = true;
	entityManager.AddGroup(this, group);
}

//!@brief	グループからの削除
//!@brief	引数で指定したグループから削除する
//!@param[in]	group	グループ
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
