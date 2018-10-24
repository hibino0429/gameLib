#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"


//----------------------------------------------------------------------------
//!@class		Transform
//!@brief	変形させるコンポーネント
//!@brief	位置・回転・拡縮
//----------------------------------------------------------------------------
class Transform : public Component
{
public:
	//!@brief	コンストラクタ
	Transform() = default;
	//!@brief	コンストラクタ
	//!@param[in]	pos		位置
	//!@param[in]	rotate	回転
	//!@param[in]	scale	拡縮
	Transform(const Math::Vector3& pos, const Math::Vector3& rotate, const Math::Vector3& scale);
	//!@brief	デストラクタ
	~Transform();

	//!@brief	初期化
	void	Initialize() override;
	//!@brief	更新
	void	UpDate() override;
	//!@brief	描画2D
	void	Render2D() override;
	//!@brief	描画3D
	void	Render3D() override;

	//!@brief	位置の取得
	const Math::Vector3&	GetPosition() const;
	//!@brief	回転の取得
	const Math::Vector3&	GetRotation() const;
	//!@brief	スケールの取得
	const Math::Vector3&	GetScale() const;
public:
	Math::Vector3	position;
	Math::Vector3	rotation;
	Math::Vector3	scale;
};