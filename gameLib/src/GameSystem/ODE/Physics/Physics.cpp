#include "Physics.h"


dWorldID		Physics::world = nullptr;
dSpaceID		Physics::collisionSpace = nullptr;
dJointGroupID	Physics::contactGroup = nullptr;
float			Physics::stepTime = 0;


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
	contactGroup = dJointGroupCreate(0);
}
//!@brief デストラクタ
Physics::~Physics()
{
	dJointGroupDestroy(contactGroup);
	dSpaceDestroy(collisionSpace);
	dWorldDestroy(world);
	dCloseODE();
}

//!@brief 物理世界の取得
//!@return 物理世界
dWorldID		Physics::GetWorld()
{
	return world;
}
//!@brief ODE空間の取得
//!@return ODEの空間
dSpaceID		Physics::GetCollisionSpace()
{
	return collisionSpace;
}
//!@brief ジョイントグループの取得
//!@return ジョイントグループ
dJointGroupID	Physics::GetJointGroupID()
{
	return contactGroup;
}


//概要: 動力学計算の実施
void	Physics::WorldStep()
{
	dWorldStep(world, stepTime);
}

//!@brief	更新
void	Physics::UpDate()
{
	
}


//!@brief	衝突検知
//!@param[in]	data	衝突データ
//!@param[in]	col		自身の物体
//!@param[in]	col2	相手の物体
void	Physics::NearCallBack(void* data, const Collision& col, const Collision& col2)
{
	dBodyID	body1 = dGeomGetBody(col.GetDynamicShape().GetGeometory());
	dBodyID body2 = dGeomGetBody(col2.GetDynamicShape().GetGeometory());
	//衝突対象か判定
	if (body1 && body2 && dAreConnectedExcluding(body1, body2, dJointTypeContact))
	{
		return;
	}
	//接触箇所の個数を決める
	static constexpr int contactNum = 10;	//接触箇所
	dContact	contact[contactNum];
	for (int i = 0; i < contactNum; ++i)
	{
		//物体同士の接触時のパラメータの設定
		contact[i].surface.mode = dContactBounce | dContactSoftCFM;
		contact[i].surface.mu = dInfinity;		//摩擦係数
		contact[i].surface.bounce = 0.1f;		//反発係数
		contact[i].surface.soft_cfm = 0.01f;	//CFM設定
	}

	//衝突検出
	int	num = dCollide(col.GetDynamicShape().GetGeometory(), col2.GetDynamicShape().GetGeometory(), contactNum, &contact[0].geom, sizeof(dContact));
	if (num > 0)
	{
		for (int i = 0; i < num; ++i)
		{
			//衝突発生
			dJointID jointID = dJointCreateContact(Physics::GetWorld(), contactGroup, contact + i);
			//接触ジョイント生成
			dJointAttach(jointID, body1, body2);
		}
	}
}

