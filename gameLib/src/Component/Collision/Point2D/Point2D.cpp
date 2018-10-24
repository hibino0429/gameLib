#include "Point2D.h"

//!@brief	�R���X�g���N�^
Point2D::Point2D()
	: point(Math::Vector2(0,0))
	, permissible(0.01f)
{

}
//!@brief	�R���X�g���N�^
//!@param[in]	point	�_
Point2D::Point2D(const Math::Vector2& point)
	: point(point)
	, permissible(0.01f)
{

}

//!@brief	�_�̎擾
//!@return	�_
const Math::Vector2&	Point2D::GetPoint() const
{
	return point;
}

//!@brief	�_�Ɠ_�̓����蔻��
//!@param[in]	targetPoint	���葤�̓_
//!@return	true: �Փ� false: �Փ˂��Ă��Ȃ�
bool	Point2D::Hit(const Point2D& targetPoint)
{
	if (fabsf(point.x - targetPoint.GetPoint().x) < permissible)
	{
		if (fabsf(point.y - targetPoint.GetPoint().y < permissible))
		{
			return true;
		}
	}
	return false;
}