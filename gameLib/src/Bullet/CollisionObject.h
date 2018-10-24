#pragma once

#if defined(_DEBUG)
#pragma comment(lib,"BulletCollision_vs2010_debug.lib")
#pragma comment(lib,"BulletDynamics_vs2010_debug.lib")
#pragma comment(lib,"BulletSoftBody_vs2010_debug.lib")
#pragma comment(lib,"LinearMath_vs2010_debug.lib")
#else
#pragma comment(lib,"BulletCollision_vs2010.lib")
#pragma comment(lib,"BulletDynamics_vs2010.lib")
#pragma comment(lib,"BulletSoftBody_vs2010.lib")
#pragma comment(lib,"LinearMath_vs2010.lib")
#endif

#include "../../src/DXEngine/Math/Math.h"
#include <../Bullet/btBulletCollisionCommon.h>
#include <../Bullet/btBulletDynamicsCommon.h>
#include <../Bullet/BulletCollision/CollisionDispatch/btInternalEdgeUtility.h>
#include <../Bullet/BulletCollision/CollisionDispatch/btGhostObject.h>
#include <string>


//物理
namespace Physics
{
	//コリジョンのタグのデータ
	struct CollisionTag
	{
		std::string		tagName;
		int				tagIndex;
		void*			userData;
	};

	//コリジョンに必要なデータ
	struct CollisionData
	{
		btCollisionShape*	shape;
		CollisionTag		tagData;
		bool				active;
		int					myselfMask;
		int					giveMask;
	};

	//剛体に必要なデータ
	struct RigidBodyData
	{
		CollisionData	collisionData;
		btScalar		mass;		//質量
		btVector3		inertia;	//慣性モーメント
		btRigidBody*	rigid;		//剛体
		bool			isDynamic;	//移動するオブジェクトか
	};


	//!@class	コリジョンの形状
	typedef btCollisionShape CollisionShape;


	//コリジョンをオブジェクトとして扱う
	class CollisionObject
	{
	public:
		//!@brief	コリジョンの形状とともに生成
		CollisionObject(CollisionShape * shape, bool ghost, const int myselfMask, const int giveMask, const Math::Vector3 & pos = Math::Vector3(0, 0, 0), const Math::Vector3 & rotate = Math::Vector3(0, 0, 0));
		//!@brief	形状も削除
		~CollisionObject();
	public:
		//設定処理
		//!@brief	コリジョンの位置の設定
		//!@param[in]	position	位置
		void	SetCollisionPosition(const Math::Vector3& position);
		//!@brief	コリジョンの回転の設定
		//!@param[in]	rotation	回転
		void	SetCollisionRotation(const Math::Vector3& rotation);
		//!@brief	生きているかのフラグの設定
		//!@param[in]	activeFlag	生きているかのフラグ
		void	SetActiveFlag(bool activeFlag);
		//!@brief	コリジョンタグの設定
		//!@param[in]	tag	タグ
		void	SetCollisionTag(const CollisionTag& tag);
		//!@brief	自身のマスクの設定
		//!@param[in]	mask	マスクの設定
		void	SetMyselfMask(const int mask);
		//!@brief	相手のマスクの設定
		//!@param[in]	mask	マスクの設定
		void	SetGiveMask(const int mask);

		//取得処理
		//!@brief	コリジョンの位置の取得
		const Math::Vector3&	GetCollisionPosition() const;
		//!@brief	コリジョンの回転の取得
		const Math::Vector3&	GetCollisionRotation() const;
		//!@brief	コリジョンの取得
		const btCollisionObject&	GetCollision() const;
		//!@brief	コリジョンのポインタの取得
		const btCollisionObject*	GetCollisionPtr() const;
		//!@brief	自身のマスクの取得
		const int	GetMyselfMask() const;
		//!@brief	相手のマスクの取得
		const int	GetGiveMask() const;
		//!@brief	コリジョンタグの取得
		const CollisionTag&	GetCollisionTag() const;
		//!@brief	生きているか判定
		bool	IsActive() const;
	private:
		CollisionData		data;
		btCollisionObject*	collisionObj;
	};



	//剛体
	class RigidBody
	{
	public:
		RigidBody(CollisionShape* shape, const float mass, bool ghost, const int myselfMask, const int giveMask, const Math::Vector3 & pos = Math::Vector3(0, 0, 0), const Math::Vector3 & rotate = Math::Vector3(0, 0, 0));
		~RigidBody();
		void*	operator new(size_t size)
		{
			return _mm_malloc(size, 16);
		}
		void	operator delete(void* p)
		{
			_mm_free(p);
		}
	public:
		//!@brief	コリジョンの取得
		const btCollisionObject&	GetCollision() const;
		//!@brief	コリジョンのポインタの取得
		const btCollisionObject*	GetCollisionPtr() const;
		//!@brief	RigidBodyの取得
		const btRigidBody*	GetRigidBody() const;
	private:
		CollisionObject*	collision;
		RigidBodyData		data;		//コリジョンデータ
	};
}