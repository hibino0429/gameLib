#include "Triangle2D.h"

//!@brief	�R���X�g���N�^
Triangle2D::Triangle2D()
{
	for (int i = 0; i < 3; ++i)
	{
		point[i] = Math::Vector2(0.0f, 0.0f);
	}
}
//!@brief	�R���X�g���N�^
//!@param[in]	point1	�_1
//!@param[in]	point2	�_2
//!@param[in]	point3	�_3
Triangle2D::Triangle2D(const Math::Vector2& point1, const Math::Vector2& point2, const Math::Vector2& point3)
{
	point[0] = point1;
	point[1] = point2;
	point[2] = point3;
}

//!@brief	�ӂ̒������擾
//!@param[in]	vectorNo	�x�N�g��No
//!@return	�ӂ̒���
const float	Triangle2D::GetLength(int vectorNo) const
{
	return point[vectorNo].Length();
}
//!@brief	�Ӄx�N�g��(�񐳋K��)���擾
//!@param[in]	vectorNo	�x�N�g��No
//!@return	�Ӄx�N�g��
const Math::Vector2&	Triangle2D::GetVector(int vectorNo) const
{
	int id[] = { 1,2,0,1 };
	return point[id[vectorNo + 1]] - point[id[vectorNo]];
}
//!@brief	���_�̎擾
//!@param[in]	pointNo	���_�ԍ�
const Math::Vector2&	Triangle2D::GetPoint(int pointNo) const
{
	return point[pointNo];
}