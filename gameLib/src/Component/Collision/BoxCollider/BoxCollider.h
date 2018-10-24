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
	//!@brief	�R���X�g���N�^
	BoxCollider();
	//!@brief	�R���X�g���N�^
	//!@param[in]	center	���S�̃I�t�Z�b�g��
	//!@param[in]	size	�傫��
	BoxCollider(const Math::Vector3& center,const Math::Vector3& size);
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
public:
	//!@brief	���S�̃I�t�Z�b�g�ʂ̎擾
	const Math::Vector3&	GetCenter() const;
	//!@brief	�傫���̎擾
	const Math::Vector3&	GetSize() const;
	//!@brief	�w��ԍ��̕����x�N�g���̎擾
	const Math::Vector3&	GetDirect(int elemNum) const;
	//!@brief	�w�莲�����̒������擾
	const float&	GetLength(int elemNum) const;
	//!@brief	�ŏ��̍��W�̎擾
	const Math::Vector3&	GetMinPos() const;
	//!@brief	�ő�̍��W�̎擾
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