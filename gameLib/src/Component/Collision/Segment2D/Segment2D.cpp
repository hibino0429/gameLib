#include "Segment2D.h"

//!@brief	�R���X�g���N�^
Segment2D::Segment2D()
	: line()
{

}
//!@brief	�R���X�g���N�^
//!@param[in]	point	�n�_
//!@param[in]	dirVector	�����x�N�g��(��������)
Segment2D::Segment2D(const Math::Vector2& point, const Math::Vector2& dirVector)
	: line(point,dirVector)
{

}
//!@brief	�R���X�g���N�^
//!@param[in]	beginPoint	�n�_
//!@param[in]	endPoint	�I�_
//Segment2D::Segment2D(const Math::Vector2& beginPoint, const Math::Vector2& endPoint)
//	: line(beginPoint,endPoint - beginPoint)
//{
//
//}

//!@brief	�n�_�̎擾
//!@return	�n�_
const Math::Vector2&	Segment2D::GetBeginPoint() const
{
	return line.GetPoint(0.0f);
}
//!@brief	�I�_�̎擾
//!@return	�I�_
const Math::Vector2&	Segment2D::GetEndPoint() const
{
	return line.GetPoint(1.0f);
}
//!brief	�����̒������擾
//!@return	�����̒���
const float		Segment2D::GetLength() const
{
	return (line.GetPoint(1.0f) - line.GetPoint(0.0f)).Length();
}
//!@brief	�����̎n�_���炠��_�܂ł̒��������߂�
//!@param[in]	point	�w�肵����_
//!@return	�n�_������̓_�܂ł̒���
const float		Segment2D::GetLength(const Math::Vector2& point) const
{
	return (point - line.GetPoint(0.0f)).Length();
}
//!@brief	�����̕��̒���
//!@return	width��Ԃ�
const float		Segment2D::GetWidth() const
{
	return line.GetPoint(1.0f).x - line.GetPoint(0.0f).x;
}
//!@brief	�����̍����̒���
//!@return	height��Ԃ�
const float		Segment2D::GetHeight() const
{
	return line.GetPoint(1.0f).y - line.GetPoint(0.0f).y;
}
//!@brief	�n�_�̃I�t�Z�b�g
//!@param[in]	offsetVolume	�I�t�Z�b�g��
void	Segment2D::OffsetBeginPos(const Math::Vector2& offsetVolume)
{
	//������
}