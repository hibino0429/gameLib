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
//概要: 物理エンジンクラス
//--------------------------------------------------------------------
class Physics
{
public:
	//概要: コンストラクタ
	Physics();
	//概要: デストラクタ
	~Physics();

	//概要: 物理世界の取得
	//戻り値: 物理世界
	dWorldID		GetWorld() const;
	//概要: ODE空間の取得
	//戻り値: ODEの空間
	dSpaceID		GetCollisionSpace() const;
	//概要: ジョイントグループの取得
	//戻り値: ジョイントグループの取得
	dJointGroupID	GetJointGroupID() const;

	//概要: 動力学計算の実施
	void	WorldStep();

private:
	dWorldID			world;			//ODE世界
	dSpaceID		collisionSpace;		//ODE空間
	dJointGroupID	jointGroup;			//ジョイントグループ
	float			horizonGravity;		//水平重力(x)
	float			verticalGravity;	//垂直重力(y)
	float			deepGravity;		//奥行重力(z)
	float			stepTime;			//ステップ時間
};