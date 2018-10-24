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
	//!@brief	�R���X�g���N�^
	//!@param[in]	beginPos	�o���_
	//!@param[in]	dirVec		�����x�N�g��
	Ray(const Math::Vector3& beginPos, const Math::Vector3& dirVec);
	//!@brief	�f�X�g���N�^
	~Ray();
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
public:
	//!@brief	���C�̏o���_
	const Math::Vector3&	GetBeginPos() const;
	//!@brief	���C�̕����x�N�g��
	const Math::Vector3&	GetDirVec() const;
private:
	Math::Vector3	beginPos;
	Math::Vector3	dirVec;
	ConstantBuffer*	constantBuf;
	Transform		transform;
};