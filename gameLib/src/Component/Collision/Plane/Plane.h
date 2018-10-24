#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"


//----------------------------------------------------------------------------
//!@class		Plane
//!@brief	3D��Ԃł̕��ʂ��`����
//!@brief	���ʂ̕�����ax+by+cz+d = 0�ŕ\��
//----------------------------------------------------------------------------
class Plane : public Component
{
public:
	//!@brief	�R���X�g���N�^
	//!@brief	�@����1�̓_�ŕ��ʂ��쐬
	//!@param[in]	normal	���ʏ�̖@��
	//!@param[in]	pos	���ʏ�̈�_
	Plane(const Math::Vector3& normal, const Math::Vector3& pos);
	//!@brief	�R���X�g���N�^
	//!@brief	3�_�w�肵�ĕ��ʂ��쐬
	//!@param[in]	pos1	���ʂ�1�ڂ̓_
	//!@param[in]	pos2	���ʂ�2�ڂ̓_
	//!@param[in]	pos3	���ʂ�3�ڂ̓_
	Plane(const Math::Vector3& pos1, const Math::Vector3& pos2, const Math::Vector3& pos3);
public:
	//!@brief	�@���̎擾
	//!@return	�@��
	const Math::Vector3&	GetNormal() const;
	//!@brief	���ʏ�̓_�̎擾
	//!@return	���ʏ��1�_
	const Math::Vector3&	GetPoint() const;
	//!@brief	�w�肵�����W�܂ł̋����̎擾
	//!@param[in]	pos	�w�肵�����W
	//!@return	����
	const float&	GetLength(const Math::Vector3& pos) const;
	//!@brief	�w�肵�����W�����ʂɑ΂��ĕ\�������`�F�b�N
	//!@param[in]	pos	�w�肵�����W
	//!@return	true: �\ false: ��
	bool	CheckSide(const Math::Vector3& pos) const;
	//!@brief	�e�����̒l�̎擾
	//!@note	ax + by + cz + d = 0;
	//!@note	A:a , B:b , C:c, D:d �̒l��Ԃ�
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