#include "Plane.h"


//!@brief	�R���X�g���N�^
//!@brief	�@����1�̓_�ŕ��ʂ��쐬
//!@param[in]	normal	���ʏ�̖@��
//!@param[in]	pos	���ʏ�̈�_
Plane::Plane(const Math::Vector3& normal, const Math::Vector3& pos)
	: pos(pos)
{
	//�@���𐳋K��
	Math::Vector3 normalVec = normal;
	normalVec.Normalize();
	//���ʂ�a,b,c�̐ݒ�
	a = normalVec.x;
	b = normalVec.y;
	c = normalVec.z;
	//���ʂ�d
	d = -((normalVec.x * pos.x) + (normalVec.y * pos.y) + (normalVec.z * pos.z));
	this->normal = normalVec;
}
//!@brief	�R���X�g���N�^
//!@brief	3�_�w�肵�ĕ��ʂ��쐬
//!@param[in]	pos1	���ʂ�1�ڂ̓_
//!@param[in]	pos2	���ʂ�2�ڂ̓_
//!@param[in]	pos3	���ʂ�3�ڂ̓_
Plane::Plane(const Math::Vector3& pos1, const Math::Vector3& pos2, const Math::Vector3& pos3)
{
	//�@�������߂�
	Math::Vector3 normal = Math::Cross3D(pos1, pos2, pos3);
	Plane(normal, pos1);
}

//!@brief	�@���̎擾
//!@return	�@��
const Math::Vector3&	Plane::GetNormal() const
{
	return normal;
}
//!@brief	���ʏ�̓_�̎擾
//!@return	���ʏ��1�_
const Math::Vector3&	Plane::GetPoint() const
{
	return pos;
}

//!@brief	�w�肵�����W�܂ł̋����̎擾
//!@param[in]	pos	�w�肵�����W
//!@return	����
const float&	Plane::GetLength(const Math::Vector3& pos) const
{
	return  a * pos.x + b * pos.y + c * pos.z + d;
}
//!@brief	�w�肵�����W�����ʂɑ΂��ĕ\�������`�F�b�N
//!@param[in]	pos	�w�肵�����W
//!@return	true: �\ false: ��
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
