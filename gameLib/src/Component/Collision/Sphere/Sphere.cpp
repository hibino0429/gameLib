#include "Sphere.h"


//!@brief	�R���X�g���N�^
Sphere::Sphere()
	: point(0.0f,0.0f,0.0f)
	, radius(0.5f)
{

}
//!@brief	�R���X�g���N�^
//!@param[in]	centerPos	���S�_
//!@param[in]	radius	���a
Sphere::Sphere(const Point3D& centerPoint, const float radius)
	: point(centerPoint)
	, radius(radius)
{

}

//!@brief	���S�_�̎擾
//!@return	���a(Point3D)
const Point3D&	Sphere::GetCenterPoint() const
{
	return point;
}
//!@brief	���a�̎擾
//!@return	���a(float)
const float		Sphere::GetRadius() const
{
	return radius;
}