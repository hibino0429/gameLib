#include "RigidBody.h"

//コンストラクタ
RigidBody::RigidBody()
{
	rigidBody = dBodyCreate(0);		//引数にworldIDを入れる
	dMassSetZero(&mass);
	
	Create();
}

//デストラクタ
RigidBody::~RigidBody()
{
	if (geometory != nullptr)
	{
		dGeomDestroy(geometory);
		geometory = nullptr;
	}
	if (rigidBody != nullptr)
	{
		dBodyDestroy(rigidBody);
		rigidBody = nullptr;
	}
}


//生成
void	RigidBody::Create()
{
	Vec3 pos = Vec3(0, 0, 0);
	Vec3 scale = Vec3(1, 1, 1);
	dReal	totalMass = 0;

	rigidBody = dBodyCreate(0);		//引数にworldIDを入れる
	dMassSetZero(&mass);
	dMassSetBoxTotal(&mass, totalMass, scale.x, scale.y, scale.z);
	dBodySetMass(rigidBody, &mass);

	//ジオメトリの作成、ボディにコリジョンを反映
	geometory = dCreateBox(0, scale.x, scale.y, scale.z);
	dGeomSetBody(geometory, rigidBody);

	//ボディの位置設定
	dBodySetPosition(rigidBody, pos.x, pos.y, pos.z);

}