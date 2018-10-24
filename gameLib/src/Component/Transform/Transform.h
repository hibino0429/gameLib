#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"


//----------------------------------------------------------------------------
//!@class		Transform
//!@brief	�ό`������R���|�[�l���g
//!@brief	�ʒu�E��]�E�g�k
//----------------------------------------------------------------------------
class Transform : public Component
{
public:
	//!@brief	�R���X�g���N�^
	Transform() = default;
	//!@brief	�R���X�g���N�^
	//!@param[in]	pos		�ʒu
	//!@param[in]	rotate	��]
	//!@param[in]	scale	�g�k
	Transform(const Math::Vector3& pos, const Math::Vector3& rotate, const Math::Vector3& scale);
	//!@brief	�f�X�g���N�^
	~Transform();

	//!@brief	������
	void	Initialize() override;
	//!@brief	�X�V
	void	UpDate() override;
	//!@brief	�`��2D
	void	Render2D() override;
	//!@brief	�`��3D
	void	Render3D() override;

	//!@brief	�ʒu�̎擾
	const Math::Vector3&	GetPosition() const;
	//!@brief	��]�̎擾
	const Math::Vector3&	GetRotation() const;
	//!@brief	�X�P�[���̎擾
	const Math::Vector3&	GetScale() const;
public:
	Math::Vector3	position;
	Math::Vector3	rotation;
	Math::Vector3	scale;
};