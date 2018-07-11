#pragma once

#include <ode/ode.h>
#include <memory>
#include <vector>


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
	dWorldID		GetWorld();
	//!@brief	ODE空間の取得
	//!@return	ODEの空間
	dSpaceID		GetCollisionSpace();
	//!@brief	ジョイントグループの取得
	//!@return	ジョイントグループの取得
	dJointGroupID	GetJointGroupID();
	//!@brief	ステップ時間の取得
	float	GetStepTime() const;

private:
	dWorldID			world;				//ODE世界
	dSpaceID			collisionSpace;		//ODE空間
	dJointGroupID		contactGroup;		//ジョイントグループ

	float			horizonGravity;		//水平重力(x)
	float			verticalGravity;	//垂直重力(y)
	float			deepGravity;		//奥行重力(z)
	float			stepTime;			//ステップ時間
};



//物理空間を扱うクラス
//基本的に、staticなグローバル変数
//物理世界の衝突検知を行う
class PhysicsWorld
{
public:
	//!@brief	生成した物理空間を適用
	//!@param[in]	physics	物理空間
	static void	Attach(Physics* physics);
	//!@brief	衝突検知のコールバック
	//!@param[in]	data	衝突データ
	//!@param[in]	col		自身の物体
	//!@param[in]	col2	相手の物体
	static void	NearCallBack(void* data, dGeomID geometory1, dGeomID geometory2);
	//!@brief	物理世界の更新
	static void	UpDate();
	//!@brief	衝突しているかを返す
	static bool	Hit();
	//!@brief	1つ前の衝突があったかをチェック
	static bool	PreHit();
	//!@brief	保持している物理空間を取得する
	//!@return	物理空間
	static Physics&	GetPhysics();
public:
	static int num;					//現在の衝突個数
	static int preNum;				//1つ前の衝突個数
	static Physics*	physicsWorld;	//物理空間
};

