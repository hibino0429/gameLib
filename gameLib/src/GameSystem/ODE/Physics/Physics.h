#pragma once

#include <ode/ode.h>
#include <memory>
#include <vector>
#include "../../src/GameSystem/ODE/Collision/Collision.h"
#include "../../src/GameSystem/ODE/RigidBody/RigidBody.h"

#if defined(_DEBUG)
#pragma comment(lib,"oded.lib")
#else
#pragma comment(lib,"ode.lib")
#endif


//--------------------------------------------------------------------
//!@class		物理エンジンクラス
//!@brief	物理を扱うクラス
//!@brief	物理挙動を提供したりする
//--------------------------------------------------------------------
class Physics
{
public:
	//!@brief	コンストラクタ
	Physics();
	//!@brief	デストラクタ
	~Physics();
public:
	//!@brief	物理世界の取得
	//!@return	物理世界
	static dWorldID		GetWorld();
	//!@brief	ODE空間の取得
	//!@return	ODEの空間
	static dSpaceID		GetCollisionSpace();
	//!@brief	ジョイントグループの取得
	//!@return	ジョイントグループの取得
	static dJointGroupID	GetJointGroupID();

	//!@brief	動力学計算の実施
	static void	WorldStep();
public:
	//!@brief	更新
	static void	UpDate();

	//!@brief	衝突検知
	//!@param[in]	data	衝突データ
	//!@param[in]	col		自身の物体
	//!@param[in]	col2	相手の物体
	static void	NearCallBack(void* data, const Collision& col, const Collision& col2);


private:
	static dWorldID			world;				//ODE世界
	static dSpaceID			collisionSpace;		//ODE空間
	static dJointGroupID	contactGroup;		//ジョイントグループ

	std::vector<RigidBody*>	rigidBodys;
	std::vector<Collision*>	collsions;

	float			horizonGravity;		//水平重力(x)
	float			verticalGravity;	//垂直重力(y)
	float			deepGravity;		//奥行重力(z)
	static float	stepTime;			//ステップ時間
};