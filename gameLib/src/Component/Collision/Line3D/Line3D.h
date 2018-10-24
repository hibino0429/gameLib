#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/Collision/Point3D/Point3D.h"

//----------------------------------------------------------------------------
//!@class		Line3D
//!@brief	3D��Ԃł̒������`���܂�
//!@brief	[������̈�_]��[�����x�N�g��]�ŕ\���܂�
//----------------------------------------------------------------------------
class Line3D
{
public:
	//!@brief	�R���X�g���N�^
	Line3D();
	//!@brief	�R���X�g���N�^
	//!@param[in]	point	�_
	//!@param[in]	vector	�����x�N�g��
	Line3D(const Point3D& point, const Math::Vector3& vector);
public:
	//!@brief	�_��̍��W���擾
	//!@param[in]	t	�x�N�g���ɂ�����W��
	const Point3D& GetPoint(const float t) const;
private:
	Point3D			point;
	Math::Vector3	vector;
};







//#include "../../src/Component/Collision/Segment3D/Segment3D.h"
//#include "../../src/Component/Collision/Plane/Plane.h"
//#include "../../src/Component/Collision/Sphere/Sphere.h"
//#include "../../src/Component/Collision/AABB/AABB.h"
//
//
////�R���W�����RD�̓����蔻��
//namespace CollisionJudge
//{
//	//�_�Ɛ�
//	bool	Point3DToSegment3D(const Point3D& point, const Segment3D& segment)
//	{
//		//���s�ȃx�N�g�����狁�߂�[�@���x�N�g��]��0�x�N�g���ɂȂ�
//		//segment�̎n�_����Փ˓_�֌������x�N�g���̎Z�o
//		//���̃x�N�g���̑傫���������̒�����菬�����Ȃ�Փ�
//		Math::Vector3 vec = segment.GetBeginPoint() - point;
//		Math::Vector3 cross = Cross3D(vec, segment.GetVector());
//		if (cross.x != 0 || cross.y != 0 || cross.z != 0)
//		{
//			return false;
//		}
//		if (vec.Length() > cross.Length())
//		{
//			return false;
//		}
//		return true;
//	}
//
//	//���Ɛ�
//	bool	Segment3DToSegment3D(const Segment3D& segment1, const Segment3D& segment2)
//	{
//		//���ʂɂ��镽�s�łȂ����͕K�������
//
//		//1:2�ӂ��������ʂɏ���Ă��邩�`�F�b�N
//		//���̍ۂɁA2�̐��x�N�g���̊O�ς̖@���x�N�g���𒲂ׂ�
//		Math::Vector3 cross = Math::Cross3D(segment1.GetVector(), segment2.GetVector());
//
//		//2:����1��̓_�������2��̓_�܂ŐL�΂����x�N�g���̎Z�o
//		Math::Vector3 vec = segment1.GetBeginPoint() - segment2.GetBeginPoint();
//		Math::Vector3 normalVec = Math::Cross3D(segment1.GetVector(), vec);
//
//		//3:normalVec��0�ȊO�Ȃ�Փ˂��N�����Ă��Ȃ�
//		if (normalVec.Length() != 0)
//		{
//			return false;
//		}
//
//		//|n1| <= 0�@�Ȃ�Փ˂͂Ȃ�
//		if (cross.Length() <= 0)
//		{
//			return false;
//		}
//		//|n1*n2| == 0�Ȃ�Փ�
//		if (Math::Cross3D(cross, normalVec).Length() != 0)
//		{
//			return false;
//		}
//		return true;
//	}
//
//	//�����ƕ���
//	bool	Segment3DToPlane(const Segment3D& segment, const Plane& plane)
//	{
//		//�����ɍL���镽�ʂɑ΂��Đ��������Ȃ��ꍇ�A[���ʂƐ��������s]
//		//���ʂ̖@���x�N�g���Ɛ��̃x�N�g�����������`�F�b�N(����0)
//		//v1�En == 0 �܂��� v�En != 0�@�Ȃ�Փ�
//		//v1�͕��ʏ�̓_p0�Ɛ���̓_p1�̃x�N�g��
//		Math::Vector3	vector1 = plane.GetPoint() - segment.GetBeginPoint();
//		if (Math::Dot3D(vector1, plane.GetNormal()) != 0)
//		{
//			return false;
//		}
//		if (Math::Dot3D(segment.GetVector(), plane.GetNormal()) == 0)
//		{
//			return false;
//		}
//		//������2�_�����񂾕������Ȃ̂ŁA���ʂƏՓ˂��Ă���Ȃ�_�̈�����ʂ̗��ƕ\�ɂ���
//		//�@���x�N�g���Ɛ����x�N�g���͖ʂ̕\�̂ǂ��ł����Ă��A�p�x�͉s�p�ɂȂ�
//		//(v1 �E n) * (v2 �E n) <= 0 �Ȃ�Փ�
//		Math::Vector3	vector2 = plane.GetPoint() - segment.GetEndPoint();
//		if (Math::Dot3D(vector1, plane.GetNormal()) * Math::Dot3D(vector2, plane.GetNormal()) > 0)
//		{
//			return false;
//		}
//		return true;
//	}
//
//	//���Ƌ�
//	bool	SphereToSphere(const Sphere& sphere1, const Sphere& sphere2)
//	{
//		float lengthX = sphere2.GetCenterPoint().x - sphere1.GetCenterPoint().x;
//		float lengthY = sphere2.GetCenterPoint().y - sphere1.GetCenterPoint().y;
//		float lengthZ = sphere2.GetCenterPoint().z - sphere1.GetCenterPoint().z;
//		//���S���m�̋����Ɣ��a�̍��v�̔�r
//		if (powf(lengthX, 2) + powf(lengthY, 2) + powf(lengthZ, 2) > powf(sphere1.GetRadius() + sphere2.GetRadius(), 2))
//		{
//			return false;
//		}
//		return true;
//	}
//
//
//	//AABB��AABB
//	bool	AABBToAABB(const AABB& aabbBox1, const AABB& aabbBox2)
//	{
//
//	}
//}