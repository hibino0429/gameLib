#pragma once
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/Collision/CollisionData/CollisionData.h"
#include "../../src/Component/ConstantBuffer/ConstantBuffer.h"



//----------------------------------------------------------------------------
//!@class		BoxCollider
//----------------------------------------------------------------------------
class BoxCollider : public Component
{
public:
	//!@brief	コンストラクタ
	BoxCollider();
	//!@brief	コンストラクタ
	//!@param[in]	center	中心のオフセット量
	//!@param[in]	size	大きさ
	BoxCollider(const Math::Vector3& center,const Math::Vector3& size);
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
public:
	//!@brief	中心のオフセット量の取得
	const Math::Vector3&	GetCenter() const;
	//!@brief	大きさの取得
	const Math::Vector3&	GetSize() const;
	//!@brief	指定番号の方向ベクトルの取得
	const Math::Vector3&	GetDirect(int elemNum) const;
	//!@brief	指定軸方向の長さを取得
	const float&	GetLength(int elemNum) const;
	//!@brief	最小の座標の取得
	const Math::Vector3&	GetMinPos() const;
	//!@brief	最大の座標の取得
	const Math::Vector3&	GetMaxPos() const;

private:
	//OBBData		data;
	ConstantBuffer*	constantBuf;
	const float		divideLength;
	Math::Vector3	minPos;
	Math::Vector3	maxPos;
	Math::Vector3	centerPosOffset;
	Math::Vector3	axisLength;
};