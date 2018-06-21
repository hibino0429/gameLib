#include "Physics.h"

//!@brief コンストラクタ
Physics::Physics()
{
	dInitODE();					//ODEの初期化
	world = dWorldCreate();		//ODE世界の作成

	horizonGravity = 0.0f;
	verticalGravity = -9.81f;
	deepGravity = 0.0f;
	//重力設定
	dWorldSetGravity(world, horizonGravity, verticalGravity, deepGravity);
	//グローバルCFM
	dWorldSetCFM(world, 1e-5);
	dWorldSetContactMaxCorrectingVel(world, 0.1);
	//グローバルERP
	dWorldSetERP(world, 0.8f);

	//空気抵抗(平行移動速度)
	dWorldSetLinearDamping(world, 0.00001);
	//空気抵抗(角速度)
	dWorldSetAngularDamping(world, 0.005);
	//最大角速度
	dWorldSetMaxAngularSpeed(world, 200);
	//接触層の厚さ
	dWorldSetContactSurfaceLayer(world, 0.05);
	//しばらく動かないbodyを自動でdisableする
	dWorldSetAutoDisableFlag(world, 1);

	stepTime = 0.05f;	//ステップ時間
	
	//衝突検出計算
	collisionSpace = dHashSpaceCreate(0);
	//接触点の集まりを格納
	jointGroup = dJointGroupCreate(0);
}
//!@brief デストラクタ
Physics::~Physics()
{
	dJointGroupDestroy(jointGroup);
	dSpaceDestroy(collisionSpace);
	dWorldDestroy(world);
	dCloseODE();
}

//!@brief 物理世界の取得
//!@return 物理世界
dWorldID		Physics::GetWorld() const
{
	return world;
}
//!@brief ODE空間の取得
//!@return ODEの空間
dSpaceID		Physics::GetCollisionSpace() const
{
	return collisionSpace;
}
//!@brief ジョイントグループの取得
//!@return ジョイントグループ
dJointGroupID	Physics::GetJointGroupID() const
{
	return jointGroup;
}


//概要: 動力学計算の実施
void	Physics::WorldStep()
{
	dWorldStep(world, stepTime);
}