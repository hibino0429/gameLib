#pragma once
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/Collision/CollisionData/CollisionData.h"



//-----------------------------------------------------------
//!@class		SphereCollider
//-----------------------------------------------------------
class SphereCollider : public Component
{
public:
	//!@brief	コンストラクタ
	SphereCollider();
	//!@brief	コンストラクタ
	//!@param[in]	center	中心座標
	//!@param[in]	radius	半径
	SphereCollider(const Math::Vector3& center, const float radius);
public:
	//!@brief	半径の取得
	const float	GetRadius() const;
	//!@brief	中心座標のオフセット量の取得
	const Math::Vector3&	GetCenterOffset() const;
	//!@brief	座標の取得
	const Math::Vector3&	GetCenterPosition() const;
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
private:
	SphereData		data;
};