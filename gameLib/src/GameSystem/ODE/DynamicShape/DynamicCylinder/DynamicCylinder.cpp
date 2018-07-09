#include "DynamicCylinder.h"
#include "../../src/GameSystem/ODE/Physics/Physics.h"

//!@brief	コンストラクタ
//!@param[in]	centerPos	中心座標
//!@param[in]	direction	方向
//!@param[in]	radius		角度
//!@param[in]	length		長さ
//!@param[in]	mass		質量
DynamicCylinder::DynamicCylinder(const Math::Vector3& centerPos, const int direction, const double radius, const double length, const double& mass)
{
	Create();
	SetGeometory(dCreateCylinder(Physics::GetCollisionSpace(), radius, length));
	dGeomSetBody(GetGeometory(), GetRigidBody());
	dBodySetPosition(GetRigidBody(), centerPos.x, centerPos.y, centerPos.z);
}
//!@brief	コンストラクタ
//!@param[in]	dynamicBox	直方体の剛体
DynamicCylinder::DynamicCylinder(const DynamicCylinder& dynamicCylinder)
{
	SetRigidBody(dynamicCylinder.GetRigidBody());
	SetGeometory(dynamicCylinder.GetGeometory());
}
//!@brief	デストラクタ
DynamicCylinder::~DynamicCylinder()
{

}

//!@brief	形状の描画
void	DynamicCylinder::Draw()
{
	//未実装
}