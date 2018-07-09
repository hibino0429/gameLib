#include "DynamicBox.h"
#include "../../src/GameSystem/ODE/Physics/Physics.h"


//!@brief	コンストラクタ
//!@param[in]	centerPos	中心座標
//!@param[in]	scale	軸1辺の大きさ
//!@param[in]	mass	質量
DynamicBox::DynamicBox(const Math::Vector3& centerPos, const Math::Vector3& scale, const double& totalMass)
{
	Create();
	dMassSetBoxTotal(ChangeMass(), totalMass, scale.x, scale.y, scale.z);
	dBodySetMass(GetRigidBody(), ChangeMass());
	SetGeometory(dCreateBox(Physics::GetCollisionSpace(),scale.x, scale.y, scale.z));
	dGeomSetBody(GetGeometory(), GetRigidBody());
	dBodySetPosition(GetRigidBody(), centerPos.x, centerPos.y, centerPos.z);
}

//!@brief	コンストラクタ
//!@param[in]	dynamicBox	直方体の剛体
DynamicBox::DynamicBox(const DynamicBox& dynamicBox)
{
	SetRigidBody(dynamicBox.GetRigidBody());
	SetGeometory(dynamicBox.GetGeometory());
}
//!@brief	デストラクタ
DynamicBox::~DynamicBox()
{

}


//!@brief	形状の描画
void	DynamicBox::Draw()
{
	//未実装
}