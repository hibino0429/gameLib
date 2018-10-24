#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/Collision/Line2D/Line2D.h"

//----------------------------------------------------------------------------
//!@class		Segment2D
//!@brief	����(�n�_�ƏI�_������)���`
//!@brief	[�n�_]��[�����x�N�g��]������
//----------------------------------------------------------------------------
class Segment2D
{
public:
	//!@brief	�R���X�g���N�^
	Segment2D();
	//!@brief	�R���X�g���N�^
	//!@param[in]	point	�n�_
	//!@param[in]	dirVector	�����x�N�g��(��������)
	Segment2D(const Math::Vector2& point, const Math::Vector2& dirVector);
	//!@brief	�R���X�g���N�^
	//!@param[in]	beginPoint	�n�_
	//!@param[in]	endPoint	�I�_
	//Segment2D(const Math::Vector2& beginPoint, const Math::Vector2& endPoint);
public:
	//!@brief	�n�_�̎擾
	//!@return	�n�_
	const Math::Vector2&	GetBeginPoint() const;
	//!@brief	�I�_�̎擾
	//!@return	�I�_
	const Math::Vector2&	GetEndPoint() const;
	//!brief	�����̒������擾
	//!@return	�����̒���
	const float		GetLength() const;
	//!@brief	�����̎n�_���炠��_�܂ł̒��������߂�
	//!@param[in]	point	�w�肵����_
	//!@return	�n�_������̓_�܂ł̒���
	const float		GetLength(const Math::Vector2& point) const;
	//!@brief	�����̕��̒���
	//!@return	width��Ԃ�
	const float		GetWidth() const;
	//!@brief	�����̍����̒���
	//!@return	height��Ԃ�
	const float		GetHeight() const;
	//!@brief	�n�_�̃I�t�Z�b�g
	//!@param[in]	offsetVolume	�I�t�Z�b�g��
	void	OffsetBeginPos(const Math::Vector2& offsetVolume);
private:
	Line2D	line;	//����
};




//
//#include "../../src/Component/Collision/Point2D/Point2D.h"
//#include "../../src/Component/Collision/Circle2D/Circle2D.h"
//#include "../../src/Component/Collision/Triangle2D/Triangle2D.h"
//
//
////�R���W�����̓����蔻��
//namespace CollisionJudge
//{
//	//�A���S���Y��
//	//1:���͓_�����ԂȂ�����Ō`��
//	//2:���o�͊O�ς𗘗p���܂�
//	//3:����̓_���n�_�A�I�_�̃x�N�g���Z�o(�I�_ - �n�_)
//	//4:��̃x�N�g�����A���̕����x�N�g���ƕ��s�Ȃ�A����ɂ���
//	//5:���s�Ȏ�,�O�ς� = 0�ƂȂ�
//	bool	Point2DToLine2D(const Point2D& point, const Segment2D& segment)
//	{
//		//�����̎n�_����_�܂ł̒���
//		float len = segment.GetLength(Math::Vector2(point.GetPoint().x, point.GetPoint().y));
//
//		//���ς̌���
//		float dot = segment.GetWidth() * (point.GetPoint().x - segment.GetBeginPoint().x) + segment.GetHeight() * (point.GetPoint().y - segment.GetBeginPoint().y);
//		
//		if (dot != segment.GetLength() * len)
//		{
//			return false;
//		}
//		if (segment.GetLength() < len)
//		{
//			return false;
//		}
//		return true;
//	}
//
//
//	//�A���S���Y��
//	//�_�Ɖ~
//	//1: �_���~���Ɋ܂܂�Ă��邩����
//	//2: �~�̔��a�Ɠ_�܂ł̋������~�̔��a�ȉ��ł���ΏՓ�
//	bool	Point2DToCircle2D(const Point2D& point, const Circle2D& circle)
//	{
//		float xlen = point.GetPoint().x - circle.GetCenterPos().x;
//		float ylen = point.GetPoint().y - circle.GetCenterPos().y;
//
//		if (powf(xlen, 2) + powf(ylen, 2) > powf(circle.GetRadius(), 2))
//		{
//			return false;
//		}
//		return true;
//	}
//
//	//�A���S���Y��
//	//�~�Ɖ~
//	//1: �Q�̉~�̒��S�_�Ԃ̋��������a�̒������Z���Ȃ�Փ�
//	bool	Circle2DToCircle2D(const Circle2D& circle1, const Circle2D& circle2)
//	{
//		float xlen2 = powf(circle1.GetCenterPos().x - circle2.GetCenterPos().x,2);
//		float ylen2 = powf(circle2.GetCenterPos().y - circle2.GetCenterPos().y,2);
//
//		if (xlen2 + ylen2 > powf(circle1.GetRadius() + circle2.GetRadius(),2))
//		{
//			return false;
//		}
//		return true;
//	}
//
//	//���ς̌v�Z
//	float	Dot(const Math::Vector2& vector1, const Math::Vector2& vector2)
//	{
//		return vector1.x * vector2.x + vector1.y * vector2.y;
//	}
//	//�O�ς̌v�Z
//	float	Cross(const Math::Vector2& vector1, const Math::Vector2& vector2)
//	{
//		return vector1.x * vector2.y - vector1.y - vector2.x;
//	}
//
//	//�����Ɛ���
//	//�A���S���Y��
//	bool	Segment2DToSegment2D(const Segment2D& segment1, const Segment2D& segment2)
//	{
//		//�����̒���
//		float	length = segment2.GetLength() - segment1.GetLength();
//		float crossV1_V2 = Cross(length, segment1.GetLength());
//		if (crossV1_V2 == 0.0f) { return false; }
//
//		float crossV_V1 = Cross(length, segment1.GetLength());
//		float crossV_V2 = Cross(length, segment2.GetLength());
//
//		float t1 = crossV_V2 / crossV1_V2;
//		float t2 = crossV_V1 / crossV1_V2;
//
//		const float eps = 0.00001f;
//		if (t1 + eps < 0 || t1 - eps > 1 || t2 + eps < 0 || t2 - eps > 1)
//		{
//			return false;
//		}
//		return true;
//	}
//
//	//�~�ƃ��C�̏Փ˓_
//	//1:�~�̒��S�_�ƃ��C�Ƃ̋��������߂�
//	//2:�Փ˂��Ă��邱�ƂƏՓ˓X�������؂�ɋ��߂Ă��܂���
//	bool	Circle2DToSegment2D(const Circle2D& circle, Segment2D& segment)
//	{
//		//���a�̃}�C�i�X�̓G���[(���a�̃[���͋��e�͈�)
//		if (circle.GetRadius() < 0.0f) { return false; }
//		//���C�̕����x�N�g�����Ȃ�
//		if (segment.GetWidth() == 0.0f && segment.GetHeight() == 0.0f) { return false; }
//
//		//�~�̒��S�_�����_�ɂȂ�悤�Ɏn�_���I�t�Z�b�g
//		segment.OffsetBeginPos(circle.GetCenterPos());
//
//		//���C�̕����x�N�g���𐳋K��
//		segment.Normalize();
//
//		//�W��t���Z�o
//		float dotPos_Vec = segment.GetBeginPoint().x * segment.GetWidth() + segment.GetEndPoint().x * segment.GetHeight();
//		float dotPos_Pos = powf(segment.GetBeginPoint().x, 2) + powf(segment.GetBeginPoint().y, 2);
//		float s = dotPos_Vec * dotPos_Vec - dotPos_Pos + circle.GetRadius() * circle.GetRadius();
//		if (fabsf(s) < 0.00001f)
//		{
//			s = 0.0f;	//�덷�̏C��
//		}
//		if (s < 0.0f) { return false; }
//
//		float sq = sqrtf(s);
//		float t1 = -dotPos_Vec - sq;
//		float t2 = -dotPos_Pos + sq;
//
//		//t1�܂���t2���}�C�i�X�Ȃ�n�_���~���ɂ߂荞��ł��邽�߁A�G���[
//		if (t1 < 0.0f || t2 < 0.0f) { return false; }
//
//		//�Փˍ��W�̏o��
//
//		return true;
//	}
//
//
//	//�O�p�`���m�̓����蔻��
//	bool	Triangle2DToTriangle2D(const Triangle2D& triangle1, const Triangle2D& triangle2)
//	{
//		const int other[] = { 1,2,0 };
//		const Triangle2D*	triangle[] = { &triangle1,&triangle2,&triangle1 };
//
//		for (int t = 0; t < 2; ++t)
//		{
//			const Triangle2D& ta = *triangle[t];
//			const Triangle2D& tb = *triangle[t + 1];
//
//			for (int i = 0; i < 3; ++i)
//			{
//				//A�����番�����̐�����L���Z�o
//				const Math::Vector2& vec = ta.GetVector(i);
//				const Math::Vector2 sepVec(vec.y, -vec.x);
//
//				//A��L�ɓ��e
//				float s1min = Dot(sepVec, ta.GetPoint(i));
//				float s1max = Dot(sepVec, ta.GetPoint(other[i]));
//				if (s1min > s1max)
//				{
//					float tmp = s1min;
//					s1min = s1max;
//					s1max = tmp;
//				}
//
//				//B��L�ɓ��e
//				float s2min = Dot(sepVec, tb.GetPoint(0));
//				float s2max = Dot(sepVec, tb.GetPoint(1));
//				if (s2min > s2max)
//				{
//					float tmp = s2min;
//					s2min = s2max;
//					s2max = tmp;
//				}
//				float d3 = Dot(sepVec, tb.GetPoint(2));
//				if (d3 < s2min)
//				{
//					s2min = d3;
//				}
//				else if (d3 > s2max)
//				{
//					s2max = d3;
//				}
//				//����������
//				if (
//					(s2min <= s1min && s1min <= s2max) ||
//					(s2min <= s2max && s1max <= s2max) ||
//					(s1min <= s2min && s2min <= s1max) ||
//					(s1min <= s2max && s2max <= s1max) 
//				   )
//				{
//					continue;	//�e���d�Ȃ���
//				}
//				//�����������������߁A�Փ˂��Ă��Ȃ�
//				return false;
//			}
//		}
//		return true;
//	}
//}