#include "Circle2D.h"

//!@brief	�R���X�g���N�^
Circle2D::Circle2D()
	: centerPos(0.0f,0.0f)
	, radius(0.0f)
{

}
//!@brief	�R���X�g���N�^
//!@param[in]	centerPos	���S�_
//!@param[in]	radius	���a
Circle2D::Circle2D(const Math::Vector2& centerPos, const float radius)
	: centerPos(centerPos)
	, radius(radius)
{

}
//!@brief	���S�_�̎擾
//!@return	���S�_
const Math::Vector2&	Circle2D::GetCenterPos() const
{
	return centerPos;
}
//!@brief	���a�̎擾
//!@return	���a
const float		Circle2D::GetRadius() const
{
	return radius;
}
//!@brief	���S�_�̃I�t�Z�b�g
//!@param[in]	offsetVolume	�I�t�Z�b�g��
void	Circle2D::OffsetCenterPos(const Math::Vector2& offsetVolume)
{
	centerPos += offsetVolume;
}