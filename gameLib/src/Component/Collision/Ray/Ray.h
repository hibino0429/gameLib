#pragma once
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/GameSystem/ECS/Entity/Entity.h"
#include "../../src/Component/Transform/Transform.h"
#include "../../src/Component/ConstantBuffer/ConstantBuffer.h"


//---------------------------------------------------------
//!@class		Ray
//---------------------------------------------------------
class Ray : public Component
{
public:
	//!@brief	コンストラクタ
	//!@param[in]	beginPos	出発点
	//!@param[in]	dirVec		方向ベクトル
	Ray(const Math::Vector3& beginPos, const Math::Vector3& dirVec);
	//!@brief	デストラクタ
	~Ray();
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
public:
	//!@brief	レイの出発点
	const Math::Vector3&	GetBeginPos() const;
	//!@brief	レイの方向ベクトル
	const Math::Vector3&	GetDirVec() const;
private:
	Math::Vector3	beginPos;
	Math::Vector3	dirVec;
	ConstantBuffer*	constantBuf;
	Transform		transform;
};