#include "Line2D.h"

//!@brief	�R���X�g���N�^
Line2D::Line2D()
	: point(0.0f,0.0f)
	, dirVector(1.0f,0.0f)
{

}
//!@brief	�R���X�g���N�^
//!@param[in]	point		�_
//!@param[in]	dirVector	�����x�N�g��
Line2D::Line2D(const Math::Vector2& point, const Math::Vector2& dirVector)
	: point(point)
	, dirVector(dirVector)
{

}

//!@brief	�_��̍��W���擾
//!@param[in]	t	�x�N�g���ɂ�����W��
//!@return	�_�̍��W
const Math::Vector2&	Line2D::GetPoint(const float t) const
{
	return point + Math::Vector2(t * dirVector.x, t * dirVector.y);
}