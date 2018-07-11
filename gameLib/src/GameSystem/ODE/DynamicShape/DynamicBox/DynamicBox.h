#pragma once
#include "../../src/GameSystem/ODE/DynamicShape/DynamicShape.h"
#include "../../src/DXEngine/Math/Math.h"


//------------------------------------------------------------------------------
//!@class		DynamicBox
//!@brief	直方体の剛体クラス
//!@brief	主に直方体の剛体を扱います
//------------------------------------------------------------------------------
class DynamicBox : public DynamicShape
{
public:
	//!@brief	コンストラクタ
	//!@param[in]	centerPos	中心座標
	//!@param[in]	scale	軸1辺の大きさ
	//!@param[in]	totalMass	質量
	DynamicBox(const Math::Vector3& centerPos, const Math::Vector3& scale, const double& totalMass);
	//!@brief	コンストラクタ
	//!@param[in]	dynamicBox	直方体の剛体
	DynamicBox(const DynamicBox& dynamicBox);
	//!@brief	デストラクタ
	~DynamicBox();
public:
	//!@brief	形状の描画
	void	Draw() override;
};
