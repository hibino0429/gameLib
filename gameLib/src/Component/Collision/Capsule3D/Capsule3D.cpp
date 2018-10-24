#include "Capsule3D.h"


//!@brief	�R���X�g���N�^
Capsule3D::Capsule3D()
	: radius(0.5f)
{

}
//!@brief	�R���X�g���N�^
//!@param[in]	segment	����
//!@param[in]	radius	���a
Capsule3D::Capsule3D(const Segment3D& segment, const float radius)
	: segment(segment)
	, radius(radius)
{

}
//!@brief	�R���X�g���N�^
//!@param[in]	point1	�_1
//!@param[in]	point2	�_2
//!@param[in]	radius	���a
Capsule3D::Capsule3D(const Point3D& point1, const Point3D& point2, const float radius)
	: segment(point1,point2)
	, radius(radius)
{

}

//!@brief	�����̎擾
//!@return	����
const Segment3D&	Capsule3D::GetSegment() const
{
	return segment;
}
//!@brief	���a�̎擾
//!@return	���a
const float&	Capsule3D::GetRadius() const
{
	return radius;
}