#include "DynamicCapsule.h"
#include "../../src/GameSystem/ODE/Physics/Physics.h"

//!@brief	コンストラクタ
//!@param[in]	centerPos	中心座標
//!@param[in]	direction	方向
//!@param[in]	radius		角度
//!@param[in]	length		長さ
//!@param[in]	totalMass	質量
DynamicCapsule::DynamicCapsule(const Math::Vector3& centerPos, const int direction, const double radius, const double length, const double& totalMass)
{
	Create();
	SetGeometory(dCreateCapsule(PhysicsWorld::GetPhysics().GetCollisionSpace(), radius, length));
	dGeomSetBody(GetGeometory(), GetRigidBody());
	dBodySetPosition(GetRigidBody(), centerPos.x, centerPos.y, centerPos.z);
}

//!@brief	コンストラクタ
//!@param[in]	dynamicBox	直方体の剛体
DynamicCapsule::DynamicCapsule(const DynamicCapsule& dynamicCapsule)
{
	SetRigidBody(dynamicCapsule.GetRigidBody());
	SetGeometory(dynamicCapsule.GetGeometory());
}

//!@brief	デストラクタ
DynamicCapsule::~DynamicCapsule()
{

}

//!@brief	形状の描画
void	DynamicCapsule::Draw()
{
	//未実装
}