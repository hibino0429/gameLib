#include "Capsule2D.h"

//!@brief	�R���X�g���N�^
Capsule2D::Capsule2D()
	: segment()
	, radius(0.5f)
{

}
//!@brief	�R���X�g���N�^
//!@param[in]	segment	����
//!@param[in]	radius	���a
Capsule2D::Capsule2D(const Segment2D& segment, const float radius)
	: segment(segment)
	, radius(radius)
{

}
//!@brief	�R���X�g���N�^
//!@param[in]	beginPoint	�n�_
//!@param[in]	endPoint	�I�_
//!@param[in]	radius	���a
Capsule2D::Capsule2D(const Math::Vector2& beginPoint, const Math::Vector2& endPoint, const float radius)
	: segment(beginPoint, endPoint - beginPoint)
	, radius(radius)
{

}