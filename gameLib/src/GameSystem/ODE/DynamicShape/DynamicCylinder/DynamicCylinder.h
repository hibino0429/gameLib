#pragma once
#include "../../src/GameSystem/ODE/DynamicShape/DynamicShape.h"

//------------------------------------------------------------------------------
//!@class		DynamicCylinder
//!@brief	円柱の剛体クラス
//!@brief	主に円柱の剛体を扱います
//------------------------------------------------------------------------------
class DynamicCylinder : public DynamicShape
{
public:
	//!@brief	コンストラクタ
	//!@param[in]	centerPos	中心座標
	//!@param[in]	direction	方向
	//!@param[in]	radius		角度
	//!@param[in]	length		長さ
	//!@param[in]	mass		質量
	DynamicCylinder(const Math::Vector3& centerPos, const int direction,const double radius,const double length, const double& mass);
	//!@brief	コンストラクタ
	//!@param[in]	dynamicBox	直方体の剛体
	DynamicCylinder(const DynamicCylinder& dynamicCylinder);
	//!@brief	デストラクタ
	~DynamicCylinder();
public:
	//!@brief	形状の描画
	void	Draw() override;
};
