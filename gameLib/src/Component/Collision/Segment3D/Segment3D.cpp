#include "Segment3D.h"

//!@brief	�R���X�g���N�^
Segment3D::Segment3D()
	:line(Point3D(0.0f,0.0f,0.0f),Math::Vector3(1.0f,0.0f,0.0f))
{

}
//!@brief	�R���X�g���N�^
//!@param[in]	beginPoint	�n�_
//!@param[in]	vector	�����x�N�g��
Segment3D::Segment3D(const Point3D& beginPoint, const Math::Vector3& vector)
	: line(beginPoint,vector)
{

}
//!@brief	�R���X�g���N�^
//!@param[in]	beginPoint	�n�_
//!@param[in]	endPoint	�I�_
Segment3D::Segment3D(const Point3D& beginPoint, const Point3D& endPoint)
	: line(beginPoint,endPoint-beginPoint)
{

}

//!@brief	�n�_�̎擾
//!@return	�n�_(Point3D)
const Point3D&	Segment3D::GetBeginPoint() const
{
	return line.GetPoint(0.0f);
}
//!@brief	�I�_�̎擾
//!@return	�I�_(Point3D)
const Point3D&	Segment3D::GetEndPoint() const
{
	return line.GetPoint(1.0f);
}
//!@brief	�����x�N�g���̎擾
//!@return	�����x�N�g��(Math::Vector3)
const Math::Vector3&	Segment3D::GetVector() const
{
	return line.GetPoint(1.0f) - line.GetPoint(0.0f);
}