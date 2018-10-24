#include "Plane.h"


//!@brief	コンストラクタ
//!@brief	法線と1つの点で平面を作成
//!@param[in]	normal	平面上の法線
//!@param[in]	pos	平面上の一点
Plane::Plane(const Math::Vector3& normal, const Math::Vector3& pos)
	: pos(pos)
{
	//法線を正規化
	Math::Vector3 normalVec = normal;
	normalVec.Normalize();
	//平面のa,b,cの設定
	a = normalVec.x;
	b = normalVec.y;
	c = normalVec.z;
	//平面のd
	d = -((normalVec.x * pos.x) + (normalVec.y * pos.y) + (normalVec.z * pos.z));
	this->normal = normalVec;
}
//!@brief	コンストラクタ
//!@brief	3点指定して平面を作成
//!@param[in]	pos1	平面の1つ目の点
//!@param[in]	pos2	平面の2つ目の点
//!@param[in]	pos3	平面の3つ目の点
Plane::Plane(const Math::Vector3& pos1, const Math::Vector3& pos2, const Math::Vector3& pos3)
{
	//法線を求める
	Math::Vector3 normal = Math::Cross3D(pos1, pos2, pos3);
	Plane(normal, pos1);
}

//!@brief	法線の取得
//!@return	法線
const Math::Vector3&	Plane::GetNormal() const
{
	return normal;
}
//!@brief	平面上の点の取得
//!@return	平面上の1点
const Math::Vector3&	Plane::GetPoint() const
{
	return pos;
}

//!@brief	指定した座標までの距離の取得
//!@param[in]	pos	指定した座標
//!@return	距離
const float&	Plane::GetLength(const Math::Vector3& pos) const
{
	return  a * pos.x + b * pos.y + c * pos.z + d;
}
//!@brief	指定した座標が平面に対して表か裏かチェック
//!@param[in]	pos	指定した座標
//!@return	true: 表 false: 裏
bool	Plane::CheckSide(const Math::Vector3& pos) const
{
	if (GetLength(pos) < 0.0f)
	{
		return false;
	}
	return true;
}

const float Plane::GetA() const
{
	return a;
}

const float Plane::GetB() const
{
	return b;
}

const float Plane::GetC() const
{
	return c;
}

const float Plane::GetD() const
{
	return d;
}

void Plane::Initialize()
{
}

void Plane::UpDate()
{
}

void Plane::Render2D()
{
}

void Plane::Render3D()
{
}
