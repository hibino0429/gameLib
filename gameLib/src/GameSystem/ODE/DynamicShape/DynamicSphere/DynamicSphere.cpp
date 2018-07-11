#include "DynamicSphere.h"
#include "../../src/GameSystem/ODE/Physics/Physics.h"

//!@brief	コンストラクタ
//!@param[in]	centerPos	中心座標
//!@param[in]	radius	半径
//!@param[in]	mass	質量
DynamicSphere::DynamicSphere(const Math::Vector3& centerPos, const double& radius, const double& totalMass)
{
	Create();
	dMassSetSphereTotal(ChangeMass(), totalMass, radius);
	dBodySetMass(GetRigidBody(), &GetMass());
	//ジオメトリの作成
	SetGeometory(dCreateSphere(PhysicsWorld::GetPhysics().GetCollisionSpace(),radius));
	//ボディにアタッチ
	dGeomSetBody(GetGeometory(), GetRigidBody());
	dBodySetPosition(GetRigidBody(), centerPos.x, centerPos.y, centerPos.z);
}

//!@breif	コンストラクタ
//!@param[in]	dynamicSphere	球の剛体
DynamicSphere::DynamicSphere(const DynamicSphere& dynamicSphere)
{
	SetRigidBody(dynamicSphere.GetRigidBody());
	SetGeometory(dynamicSphere.GetGeometory());
}
//!@brief	デストラクタ
DynamicSphere::~DynamicSphere()
{

}

//!@brief	形状の描画
void	DynamicSphere::Draw()
{
	//未実装
}