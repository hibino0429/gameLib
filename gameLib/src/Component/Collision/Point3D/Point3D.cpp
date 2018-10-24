#include "Point3D.h"

//!@brief	�R���X�g���N�^
Point3D::Point3D()
	: Math::Vector3(0.0f,0.0f,0.0f)
{

}
//!@brief	�R���X�g���N�^
//!@param[in]	point	�_
Point3D::Point3D(const Math::Vector3& point)
{
	x = point.x;
	y = point.y;
	z = point.z;
}
//!@brief	�R���X�g���N�^
//!@param[in]	x	���Wx
//!@param[in]	y	���Wy
//!@param[in]	z	���Wz
Point3D::Point3D(const float x, const float y, const float z)
	: Math::Vector3(x,y,z)
{
	
}

//!@brief	�_���W�̎擾
//!@return	�_�̍��W
const Math::Vector3&	Point3D::GetPointPos() const
{
	return *this;
}