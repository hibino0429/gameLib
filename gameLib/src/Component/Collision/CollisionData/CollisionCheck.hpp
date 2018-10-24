#pragma once
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/Component/Collision/SphereCollider/SphereCollider.h"
#include "../../src/Component/Collision/CapsuleCollider/CapsuleCollider.h"
#include "../../src/Component/Collision/BoxCollider/BoxCollider.h"
#include "../../src/Component/Collision/AABB/AABB.h"
#include "../../src/Component/Collision/Ray/Ray.h"
#include "../../src/Component/Collision/Plane/Plane.h"
#include <amp.h>
#include <algorithm>

struct CollisionWorld
{
	//!@brief	���Ƌ��Ƃ̓����蔻��
	//!@return	true:�������Ă���  false:�������Ă��Ȃ�
	static bool	CheckSphereToSphere(const SphereCollider& sphere1, const SphereCollider& sphere2)
	{
		//���Ƌ��Ƃ̍���
		//sub.Distance(const Math::Vector3& pos);
		float sub = Math::VectorLength(sphere1.GetCenterPosition(), sphere2.GetCenterPosition());
		//�O�����̒藝�ŁA�x�N�g���̒������v�Z
		float	distance = sub * sub;
		//���a�̘a
		float sumRadius = sphere1.GetRadius() + sphere2.GetRadius();
		float	sumRadius2 = sumRadius * sumRadius;
		//�����̔��a�̘a�����傫���Ȃ瓖�����Ă��Ȃ�
		if (distance > sumRadius2)
		{
			return false;
		}
		return true;
	}
	//!@brief	���ƃJ�v�Z���Ƃ̓����蔻��
	static bool	CheckSphereToCapsule(const SphereCollider& sphere,const CapsuleCollider& capsule)
	{
		//���̒��S�ƃJ�v�Z���̐����̋���(2��)�v�Z
		Segment seg = capsule.GetSegment();
		float distance2 = seg.GetPointDistance(sphere.GetCenterPosition());
		
		//����(2��)�����a�̘a(2��)��菬������Γ������Ă���
		float radius = sphere.GetRadius() + capsule.GetRadius();
		if (distance2 > radius * radius)
		{
			return false;
		}
		return true;
	}
	//!@brief	�J�v�Z���ƃJ�v�Z���Ƃ̓����蔻��
	static bool	CheckCapsuleToCapsule(const CapsuleCollider& capsule1, const CapsuleCollider& capsule2)
	{
		//���̒��S�ƃJ�v�Z���̒��S(2��)�v�Z
		Segment seg = capsule1.GetSegment();
		Segment seg2 = capsule2.GetSegment();
		float distance2 = seg.GetSegmentDistance(seg2);

		//���a�̘a(2��)�̌v�Z
		float radiusSum = capsule1.GetRadius() + capsule2.GetRadius();
		float radius2 = radiusSum * radiusSum;

		//����(2��)�����a�̘a(2��)���傫����΁A������
		if (distance2 > radius2)
		{
			return false;
		}
		return true;
	}

	//!@brief	AABB���m�̓����蔻��
	//!@note	�Փˏ���
	//!@note	aabb1�̉E����aabb2�̍������傫���@����
	//!@note	aabb1�̍�����aabb2�̉E����菬�����@����
	//!@note	aabb1�̏㑤��aabb2�̉������傫���@����
	//!@note	aabb1�̉�����aabb2�̏㑤��菬����  �Ȃ�Փ�
	bool	CheckAABBToAABB(AABB& aabb1, AABB& aabb2)
	{
		Segment seg(aabb2.GetLeftUpFrontPos(),aabb2.GetLeftUpBackPos());
		Segment seg2(aabb2.GetLeftUpBackPos(), aabb2.GetRightUpBackPos());
		Segment seg3(aabb2.GetRightUpBackPos(), aabb2.GetRightUpFrontPos());
		Segment seg4(aabb2.GetRightUpFrontPos(), aabb2.GetLeftUpFrontPos());
		Segment seg5(aabb2.GetLeftUpBackPos(), aabb2.GetLeftDownBackPos());
		Segment seg6(aabb2.GetRightUpBackPos(), aabb2.GetRightDownBackPos());
		Segment seg7(aabb2.GetRightUpFrontPos(), aabb2.GetRightDownFrontPos());
		Segment seg8(aabb2.GetLeftUpFrontPos(), aabb2.GetLeftDownFrontPos());
		Segment seg9(aabb2.GetLeftUpFrontPos(), aabb2.GetLeftDownBackPos());
		Segment seg10(aabb2.GetLeftDownBackPos(), aabb2.GetRightDownBackPos());
		Segment seg11(aabb2.GetRightDownBackPos(), aabb2.GetRightDownFrontPos());
		Segment seg12(aabb2.GetRightDownFrontPos(), aabb2.GetLeftDownFrontPos());
		if (!aabb1.HitSegment(seg)) { return false; }
		if (!aabb1.HitSegment(seg2)) { return false; }
		if (!aabb1.HitSegment(seg3)) { return false; }
		if (!aabb1.HitSegment(seg4)) { return false; }
		if (!aabb1.HitSegment(seg5)) { return false; }
		if (!aabb1.HitSegment(seg6)) { return false; }
		if (!aabb1.HitSegment(seg7)) { return false; }
		if (!aabb1.HitSegment(seg8)) { return false; }
		if (!aabb1.HitSegment(seg9)) { return false; }
		if (!aabb1.HitSegment(seg10)) { return false; }
		if (!aabb1.HitSegment(seg11)) { return false; }
		if (!aabb1.HitSegment(seg12)) { return false; }
		return true;
	}

	//!@brief	OBB���m�̓����蔻��
	static bool	CheckOBBToOBB(const BoxCollider& obb1, const BoxCollider& obb2)
	{
		//�e�����̃x�N�g���̊m��
		Math::Vector3	normalAe1 = obb1.GetDirect(0), Ae1 = normalAe1 * obb1.GetLength(0);
		Math::Vector3	normalAe2 = obb1.GetDirect(1), Ae2 = normalAe2 * obb1.GetLength(1);
		Math::Vector3	normalAe3 = obb1.GetDirect(2), Ae3 = normalAe3 * obb1.GetLength(2);
		Math::Vector3	normalBe1 = obb2.GetDirect(0), Be1 = normalBe1 * obb2.GetLength(0);
		Math::Vector3	normalBe2 = obb2.GetDirect(1), Be2 = normalBe2 * obb2.GetLength(1);
		Math::Vector3	normalBe3 = obb2.GetDirect(2), Be3 = normalBe3 * obb2.GetLength(2);
		//���S���W���m�̋���
		Math::Vector3	interval = obb1.GetCenter() - obb2.GetCenter();

		//������ : Ae1
		float	rA = Ae1.Length();
		float	rB = Math::LengthSegmentOnSeparateAxis(normalAe1, normalBe1, Be2, Be3);
		float	len = fabsf(Math::Dot3D(interval, normalAe1));
		//���S�_���W�̋������������e�����̒����̍��v���������Ȃ�A�Փ˂��ĂȂ�
		if (len > rA + rB)
		{
			return false;
		}
		//������ : Ae2
		rA = Ae2.Length();
		rB = Math::LengthSegmentOnSeparateAxis(normalAe2, Be1, Be2, Be3);
		len = fabs(Math::Dot3D(interval, normalAe2));
		if (len > rA + rB)
		{
			return false;
		}
		//������ : Ae3
		rA = Ae3.Length();
		rB = Math::LengthSegmentOnSeparateAxis(normalAe3, Be1, Be2, Be3);
		len = fabs(Math::Dot3D(interval, normalAe3));
		if (len > rA + rB)
		{
			return false;
		}
		//������ : Be1
		rA = Math::LengthSegmentOnSeparateAxis(normalBe1, Ae1, Ae2, Ae3);
		rB = Be1.Length();
		len = fabs(Math::Dot3D(interval, normalBe1));
		if (len > rA + rB)
		{
			return false;
		}
		//������ : Be2
		rA = Math::LengthSegmentOnSeparateAxis(normalBe2, Ae1, Ae2, Ae3);
		rB = Be2.Length();
		len = fabs(Math::Dot3D(interval, normalBe2));
		if (len > rA + rB)
		{
			return false;
		}
		//������ : Be3
		rA = Math::LengthSegmentOnSeparateAxis(normalBe3, Ae1, Ae2, Ae3);
		rB = Be3.Length();
		len = fabs(Math::Dot3D(interval, normalBe3));
		if (len > rA + rB)
		{
			return false;
		}
		//������ : C11
		Math::Vector3	cross;
		cross = Math::Cross3D(normalAe1, normalBe1);
		rA = Math::LengthSegmentOnSeparateAxis(cross, Ae2, Ae3);
		rB = Math::LengthSegmentOnSeparateAxis(cross, Be2, Be3);
		len = fabs(Math::Dot3D(interval, cross));
		if (len > rA + rB)
		{
			return false;
		}
		//������ : C12
		cross = Math::Cross3D(cross, normalAe1, normalBe2);
		rA = LengthSegmentOnSeparateAxis(cross, Ae2, Ae3);
		rB = LengthSegmentOnSeparateAxis(cross, Be1, Be3);
		len = fabs(Math::Dot3D(interval, cross));
		if (len > rA + rB)
		{
			return false;
		}
		//������ : C13
		cross = Math::Cross3D(cross, normalAe1, normalBe3);
		rA = Math::LengthSegmentOnSeparateAxis(cross, Ae2, Ae3);
		rB = Math::LengthSegmentOnSeparateAxis(cross, Be1, Be2);
		len = fabs(Math::Dot3D(interval, cross));
		if (len > rA + rB)
		{
			return false;
		}
		//������ : C21
		cross = Math::Cross3D(cross, normalAe2, normalBe1);
		rA = Math::LengthSegmentOnSeparateAxis(cross, Ae1, Ae3);
		rB = Math::LengthSegmentOnSeparateAxis(cross, Be2, Be3);
		len = fabs(Math::Dot3D(interval, cross));
		if (len > rA + rB)
		{
			return false;
		}
		//������ : C22
		cross = Math::Cross3D(cross, normalAe2, normalBe2);
		rA = Math::LengthSegmentOnSeparateAxis(cross, Ae1, Ae3);
		rB = Math::LengthSegmentOnSeparateAxis(cross, Be1, Be3);
		len = fabs(Math::Dot3D(interval, cross));
		if (len > rA + rB)
		{
			return false;
		}
		//������ : C23
		cross = Math::Cross3D(cross, normalAe2, normalBe3);
		rA = Math::LengthSegmentOnSeparateAxis(cross, Ae1, Ae3);
		rB = Math::LengthSegmentOnSeparateAxis(cross, Be1, Be2);
		len = fabs(Math::Dot3D(interval, cross));
		if (len > rA + rB)
		{
			return false;
		}
		//������ : C31
		cross = Math::Cross3D(cross, normalAe3, normalBe1);
		rA = Math::LengthSegmentOnSeparateAxis(cross, Ae1, Ae2);
		rB = Math::LengthSegmentOnSeparateAxis(cross, Be2, Be3);
		len = fabs(Math::Dot3D(interval, cross));
		if (len > rA + rB)
		{
			return false;
		}
		//������ : C32
		cross = Math::Cross3D(cross, normalAe3, normalBe2);
		rA = Math::LengthSegmentOnSeparateAxis(cross, Ae1, Ae2);
		rB = Math::LengthSegmentOnSeparateAxis(cross, Be1, Be3);
		len = fabs(Math::Dot3D(interval, cross));
		if (len > rA + rB)
		{
			return false;
		}
		//������ : C33
		cross = Math::Cross3D(cross, normalAe3, normalBe3);
		rA = Math::LengthSegmentOnSeparateAxis(cross, Ae1, Ae2);
		rB = Math::LengthSegmentOnSeparateAxis(cross, Be1, Be2);
		len = fabs(Math::Dot3D(interval, cross));
		if (len > rA + rB)
		{
			return false;
		}
		//�������ʂ����݂��Ȃ����ߏՓ�
		return true;
	}
	
	//!@brief	�{�b�N�X���m�̓����蔻��
	//!@param[in]	box1	�{�b�N�X1
	//!@param[in]	box2	�{�b�N�X2
	static bool	CheckBoxToBox(const BoxCollider& box1, const BoxCollider& box2)
	{
		if (box1.GetMinPos().x > box2.GetMaxPos().x) { return false; }
		if (box1.GetMaxPos().x < box2.GetMinPos().x) { return false; }
		if (box1.GetMinPos().y > box2.GetMaxPos().y) { return false; }
		if (box1.GetMaxPos().y < box2.GetMinPos().y) { return false; }
		if (box1.GetMinPos().z > box2.GetMaxPos().z) { return false; }
		if (box1.GetMaxPos().z < box2.GetMinPos().z) { return false; }
		return true;

		Math::Vector3	v;		//������ v
		float	box1Vertex;		//�{�b�N�X1�̒��_ |v|�Ea
		float	box2Vertex;		//�{�b�N�X2�̒��_ |v * Bt|�Eb
		float	box2Center;		//�{�b�N�X2�̒��S���W |v �Ec|
		//���s�ړ�
		Math::Vector3	trans;
		//A��X��
		v = Math::Vector3(1, 0, 0);
		box1Vertex = Math::Dot3D(AbsVector3(v),box1.GetSize());
		box2Center = fabsf(Math::Dot3D(v, trans));
		//box2Vertex = 
		//A��x��
		//Math::Vector3	v;	//������
	}
	static Math::Vector3	AbsVector3(const Math::Vector3& vec3)
	{
		Math::Vector3 vec;
		vec.x = fabsf(vec3.x);
		vec.y = fabsf(vec3.y);
		vec.z = fabsf(vec3.z);
		return vec;
	}
	//!@brief	���C�Ƌ��Ƃ̓����蔻��
	//!@param[in]	ray	���C
	//!@param[in]	sphere	��
	//!@param[in]	hitPos	�Փˍ��W(�擾�p)
	static bool	CheckRayToSphere(const Ray& ray, const SphereCollider& sphere,Math::Vector3* hitPos = nullptr)
	{
		float pos2 = std::powf(ray.GetBeginPos().x, 2) + std::powf(ray.GetBeginPos().y, 2) + std::powf(ray.GetBeginPos().x, 2);
		float v2 = std::powf(ray.GetDirVec().x, 2) + std::powf(ray.GetDirVec().y, 2) + std::powf(ray.GetDirVec().z, 2);
		float posDotDir = Math::Dot3D(ray.GetBeginPos(), ray.GetDirVec());
		float sub2 = pos2 - std::powf(sphere.GetRadius(), 2.0f);
		float d = std::powf(posDotDir, 2.0f) - v2 * (pos2 - std::powf(sphere.GetRadius(), 2.0f));

		if (d < 0.0f) { return false; }

		if (!Utility::CheckNull(hitPos))
		{
			//��_�̌��o
			float t = -posDotDir - std::sqrtf(d);
			*hitPos = ray.GetBeginPos() + (ray.GetDirVec() * t);
		}
		return true;
	}
	//!@brief	���C�ƕ��ʂƂ̓����蔻��
	//!@param[in]	ray	���C
	//!@param[in]	plane	����
	//!@param[in]	hitPos	�Փˍ��W(�擾�p)
	static bool	CheckRayToPlane(const Ray& ray, const Plane& plane,Math::Vector3* hitPos = nullptr)
	{
		//���C�̎n�_�ƕ��ʂƂ̋������Z�o
		float length = plane.GetLength(ray.GetBeginPos());
		//���C�̕����x�N�g����2����Z�o
		float rayVec2 = ray.GetDirVec().x * ray.GetDirVec().x + ray.GetDirVec().y * ray.GetDirVec().y + ray.GetDirVec().z * ray.GetDirVec().z;
		//�������r�����ʂɓ͂����`�F�b�N
		if (rayVec2 < length * length) { return false; }
		
		float raySqVec2 = sqrtf(rayVec2);
		//cos�𗘗p���ē��ς����߂�
		Math::Vector3	vec = ray.GetDirVec() * (1.0f / raySqVec2);
		//���C�̃x�N�g���𐳋K��
		//�����x�N�g��(���K��)�ƕ��ʖ@���̔��]
		float	dot = Math::Dot3D(vec, -plane.GetNormal());
		
		//���������ʂɓ͂��������Z�o���A���ʂɓ͂������f
		float planeLen = length / dot;
		if (planeLen > raySqVec2) { return false; }

		//���ʂƂ̌�_���Z�o
		if (!Utility::CheckNull(hitPos))
		{
			*hitPos = ray.GetBeginPos() + (vec * planeLen);
		}
		return true;
	}
	//!@brief	���ƕ��ʂƂ̓����蔻��
	//!@param[in]	sphere	��
	//!@param[in]	plane	����
	//!@param[in]	hitVec	�߂荞�ݗ�(�擾�p)
	static bool	CheckSphereToPlane(const SphereCollider& sphere, const Plane& plane,Math::Vector3* hitVec = nullptr)
	{
		//���ʂƋ��Ƃ̒��S����
		float length = plane.GetLength(sphere.GetCenterPosition());
		if (length > sphere.GetRadius()) { return false; }

		//�߂荞�ݗ�
		if (!Utility::CheckNull(hitVec))
		{
			length = sphere.GetRadius() - length;
			*hitVec = Math::Vector3(plane.GetA() * length + plane.GetB() * length + plane.GetC() * length);
		}
		return true;
	}
	//!@brief	���ʂƕ��ʂƂ̓����蔻��
	//!@param[in]	plane1	����1
	//!@param[in]	plane2	����2
	static bool	CheckPlaneToPlane(const Plane& plane1, const Plane& plane2)
	{
		//���ʂ̖@���𗘗p���A���ʂ����s�����`�F�b�N
		float dot = (plane1.GetA() * plane2.GetA()) + (plane1.GetB() * plane2.GetB()) + (plane1.GetC() * plane2.GetC());
		if ((dot >= 1.0f) || (dot <= -1.0f)) { return false; }

		//if (ray) { return true; }
		//����������K�v�ɉ����č쐬
		//�O�ς𗘗p���Č�����������x�N�g�����쐬
		Math::Vector3 vec = Math::Cross3D(Math::Vector3(plane1.GetA(), plane1.GetB(), plane1.GetC()), Math::Vector3(plane2.GetA(), plane2.GetB(), plane2.GetC()));
		//���������̎n�_���Z�o
		Math::Vector3	beginPos;
		if (vec.z != 0.0f)
		{
			beginPos = Math::Vector3(
				(plane2.GetB() * plane1.GetD() - plane1.GetB() * plane2.GetD()) / vec.z,
				(plane1.GetA() * plane2.GetD() - plane2.GetA() * plane1.GetD()) / vec.z,
				0.0f
			);
		}
		else if (vec.y != 0.0f)
		{
			beginPos = Math::Vector3(
				(plane2.GetC() * plane1.GetD() - plane1.GetC() * plane2.GetD()) / vec.y,
				0.0f,
				(plane1.GetA() * plane2.GetD() - plane2.GetA() * plane1.GetD()) / vec.y
			);
		}
		else
		{
			beginPos = Math::Vector3(
				0.0f,
				(plane1.GetC() * plane2.GetD() - plane2.GetC() * plane1.GetD()) / vec.x,
				(plane2.GetB() * plane1.GetD() - plane1.GetB() * plane2.GetD()) / vec.x
			);
		}
		//�����̐ݒ�
		//Ray* ray = new Ray(beginPos, vec);
		return true;
	}
	//�{�b�N�X�Ƌ��Ƃ̓����蔻��
	static bool		CheckBoxToSphere(const BoxCollider& box, const SphereCollider& sphere)
	{
		//�N�����v�֐������߂�
		Math::Vector3	boxSurfacePoint;
		boxSurfacePoint.x = Clamp(sphere.GetCenterPosition().x, -box.GetSize().x, box.GetSize().x);
		boxSurfacePoint.y = Clamp(sphere.GetCenterPosition().y, -box.GetSize().y, box.GetSize().y);
		boxSurfacePoint.z = Clamp(sphere.GetCenterPosition().z, -box.GetSize().z, box.GetSize().z);

		Math::Vector3	sub = boxSurfacePoint - sphere.GetCenterPosition();
		float distance2 = std::powf(sub.x, 2.0f) + std::powf(sub.y, 2.0f) + std::powf(sub.z, 2.0f);
		if (distance2 > sphere.GetRadius() * sphere.GetRadius())
		{
			return false;
		}
		return true;
	}
	static float Clamp(float value, float min, float max)
	{
		if (value < min)
		{
			return min;
		}
		else if (value > max)
		{
			return max;
		}
		return value;
	}
};