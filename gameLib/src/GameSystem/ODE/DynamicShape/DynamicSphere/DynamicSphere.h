#pragma once
#include "../../src/GameSystem/ODE/DynamicShape/DynamicShape.h"

//------------------------------------------------------------------------------
//!@class		DynamicSphere
//!@brief	球体の剛体クラス
//!@brief	主に球体の剛体を扱います
//------------------------------------------------------------------------------
class DynamicSphere : public DynamicShape
{
public:
	//!@brief	コンストラクタ
	//!@param[in]	centerPos	中心座標
	//!@param[in]	radius		半径
	//!@param[in]	totalMass	質量
	DynamicSphere(const Math::Vector3& centerPos, const double& radius, const double& totalMass);
	//!@breif	コンストラクタ
	//!@param[in]	dynamicSphere	球の剛体
	DynamicSphere(const DynamicSphere& dynamicSphere);
	//!@brief	デストラクタ
	~DynamicSphere();

public:
	//!@brief	形状の描画
	void	Draw();
};
