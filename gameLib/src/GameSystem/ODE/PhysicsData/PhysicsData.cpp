#include "PhysicsData.h"


//!@brief	コンストラクタ
PhysicsData::PhysicsData()
{

}
//!@brief	デストラクタ
PhysicsData::~PhysicsData()
{

}

////////////////////////////////////////////////////////////////////
//設定処理
////////////////////////////////////////////////////////////////////
//!@brief	水平重力(x)の設定
void	PhysicsData::SetHorizonGravity(const double& horizonGravity)
{

}
//!@brief	垂直重力(y)の設定
void	PhysicsData::SetVerticalGravity(const double& verticalGravity)
{

}
//!@brief	奥行重力(z)の設定
void	PhysicsData::SetDeepGravity(const double& deepGravity)
{

}
//!@brief	空気抵抗(平行移動速度)の設定
void	PhysicsData::SetAirResistanceSpeed(const double& airResistanceSpeed)
{

}
//!@brief	空気抵抗(角速度)の設定
void	PhysicsData::SetAirResistanceAngleVelocity(const double& airResistanceAngleVelocity)
{

}
//!@brief	最大角速度の設定
void	PhysicsData::SetMaxAirAngleVelocity(const double& maxAirAngleVelocity)
{

}
//!@brief	接触層の厚さ
void	PhysicsData::SetContactSurfaceLayerThickness(const double& constactSurfaceLayerThickness)
{

}
//!@brief	ステップ時間の設定
void	PhysicsData::SetStepTime(const double& stepTime)
{

}



////////////////////////////////////////////////////////////////////
//取得処理
////////////////////////////////////////////////////////////////////
//!@brief	水平重力(x)の取得
const double&	PhysicsData::GetHorizonGravity() const
{
	return horizonGravity;
}
//!@brief	垂直重力(y)の取得
const double&	PhysicsData::GetVerticalGravity() const
{
	return verticalGravity;
}
//!@brief	奥行重力(z)の取得
const double&	PhysicsData::GetDeepGravity() const
{
	return deepGravity;
}
//!@brief	空気抵抗(平行移動速度)の取得
const double&	PhysicsData::GetAirResistanceSpeed() const
{
	return airResistanceSpeed;
}
//!@brief	空気抵抗(角速度)の取得
const double&	PhysicsData::GetAirResistanceAngleVelocity() const
{
	return airResistanceAngleVelocity;
}
//!@brief	最大角速度の取得
const double&	PhysicsData::GetMaxAirAngleVelocity() const
{
	return maxAirAngleVelocity;
}
//!@brief	接触層の厚さの取得
const double&	PhysicsData::GetContactSurfaceLayerThickness() const
{
	return contactSurfaceLayerThickness;
}
//!@brief	ステップ時間の取得
const double&	PhysicsData::GetStepTime() const
{
	return stepTime;
}