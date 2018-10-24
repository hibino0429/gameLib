#pragma once
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/Collision/CollisionData/CollisionData.h"



//-----------------------------------------------------------
//!@class		SphereCollider
//-----------------------------------------------------------
class SphereCollider : public Component
{
public:
	//!@brief	�R���X�g���N�^
	SphereCollider();
	//!@brief	�R���X�g���N�^
	//!@param[in]	center	���S���W
	//!@param[in]	radius	���a
	SphereCollider(const Math::Vector3& center, const float radius);
public:
	//!@brief	���a�̎擾
	const float	GetRadius() const;
	//!@brief	���S���W�̃I�t�Z�b�g�ʂ̎擾
	const Math::Vector3&	GetCenterOffset() const;
	//!@brief	���W�̎擾
	const Math::Vector3&	GetCenterPosition() const;
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
private:
	SphereData		data;
};