#pragma once
#include "../../src/GameSystem/ODE/DynamicShape/DynamicShape.h"


//------------------------------------------------------------------------------
//!@class		DynamicCapsule
//!@brief	カプセルの剛体クラス
//!@brief	主にカプセルの剛体を扱います
//------------------------------------------------------------------------------
class DynamicCapsule : public DynamicShape
{
public:
	//!@brief	コンストラクタ
	//!@param[in]	centerPos	中心座標
	//!@param[in]	direction	方向
	//!@param[in]	radius		角度
	//!@param[in]	length		長さ
	//!@param[in]	totalMass	質量
	DynamicCapsule(const Math::Vector3& centerPos, const int direction,const double radius,const double length, const double& totalMass);
	//!@brief	コンストラクタ
	//!@param[in]	dynamicBox	直方体の剛体
	DynamicCapsule(const DynamicCapsule& dynamicCapsule);
	//!@brief	デストラクタ
	~DynamicCapsule();
public:
	//!@brief	形状の描画
	void	Draw() override;
};
