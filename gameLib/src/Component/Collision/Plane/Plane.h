#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"


//----------------------------------------------------------------------------
//!@class		Plane
//!@brief	3D空間での平面を定義する
//!@brief	平面の方程式ax+by+cz+d = 0で表す
//----------------------------------------------------------------------------
class Plane : public Component
{
public:
	//!@brief	コンストラクタ
	//!@brief	法線と1つの点で平面を作成
	//!@param[in]	normal	平面上の法線
	//!@param[in]	pos	平面上の一点
	Plane(const Math::Vector3& normal, const Math::Vector3& pos);
	//!@brief	コンストラクタ
	//!@brief	3点指定して平面を作成
	//!@param[in]	pos1	平面の1つ目の点
	//!@param[in]	pos2	平面の2つ目の点
	//!@param[in]	pos3	平面の3つ目の点
	Plane(const Math::Vector3& pos1, const Math::Vector3& pos2, const Math::Vector3& pos3);
public:
	//!@brief	法線の取得
	//!@return	法線
	const Math::Vector3&	GetNormal() const;
	//!@brief	平面上の点の取得
	//!@return	平面上の1点
	const Math::Vector3&	GetPoint() const;
	//!@brief	指定した座標までの距離の取得
	//!@param[in]	pos	指定した座標
	//!@return	距離
	const float&	GetLength(const Math::Vector3& pos) const;
	//!@brief	指定した座標が平面に対して表か裏かチェック
	//!@param[in]	pos	指定した座標
	//!@return	true: 表 false: 裏
	bool	CheckSide(const Math::Vector3& pos) const;
	//!@brief	各次元の値の取得
	//!@note	ax + by + cz + d = 0;
	//!@note	A:a , B:b , C:c, D:d の値を返す
	const float	GetA() const;
	const float GetB() const;
	const float GetC() const;
	const float GetD() const;
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
private:
	float a;
	float b;
	float c;
	float d;
	Math::Vector3	normal;
	Math::Vector3	pos;
};