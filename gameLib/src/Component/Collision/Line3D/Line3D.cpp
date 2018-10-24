#include "Line3D.h"


//!@brief	�R���X�g���N�^
Line3D::Line3D()
	:point(0.0f,0.0f,0.0f)
	,vector(1.0f,0.0f,0.0f)
{

}
//!@brief	�R���X�g���N�^
//!@param[in]	point	�_
//!@param[in]	vector	�����x�N�g��
Line3D::Line3D(const Point3D& point, const Math::Vector3& vector)
	: point(point)
	,vector(vector)
{

}

//!@brief	�_��̍��W���擾
//!@param[in]	t	�x�N�g���ɂ�����W��
const Point3D& Line3D::GetPoint(const float t) const
{
	return point + Math::Vector3(t*vector.x,t*vector.y,t*vector.z);
}