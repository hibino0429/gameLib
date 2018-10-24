#pragma once
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/Collision/CollisionData/CollisionData.h"



//!@class		Segment
class Segment
{
public:
	//!@brief	�R���X�g���N�^
	Segment()
	{
		data.beginPos = Math::Vector3(0, 0, 0);
		data.endPos = Math::Vector3(0, 1, 0);
	}
	//!@brief	�R���X�g���N�^
	//!@param[in]	beginPos	�n�_
	//!@param[in]	endPos		�I�_
	Segment(const Math::Vector3& beginPos, const Math::Vector3& endPos)
	{
		data.beginPos = beginPos;
		data.endPos = endPos;
	}
public:
	//!@brief	�n�_�̎擾
	const Math::Vector3&	GetBeginPos() const
	{
		return data.beginPos;
	}
	//!@brief	�I�_�̎擾
	const Math::Vector3&	GetEndPos() const
	{
		return data.endPos;
	}
	//!@brief	�n�_�̐ݒ�
	void	SetBeginPos(const Math::Vector3& beginPos)
	{
		data.beginPos = beginPos;
	}
	//!@brief	�I�_�̐ݒ�
	void	SetEndPos(const Math::Vector3& endPos)
	{
		data.endPos = endPos;
	}
	//!@brief	�_�܂ł̋�����2��̎擾
	//!@param[in]	pos	���W�_
	//!@note	�����̒[�_A,B�A�_C�Ƃ���
	//!@note	1:AB�x�N�g����AC�x�N�g���̓��ς����Ȃ�A�_A���_C�̍ŋߖT
	//!@note	2:BA�x�N�g����BC�x�N�g���̓��ς����Ȃ�A�_B���_C�̍ŋߖT
	//!@note	3: 1,2�ɊY�����Ȃ��Ȃ�A�_C�̎ˉe��AC�̓����ɑ��݂���̂ŁA���̓_���ŋߖT
	const float GetPointDistance(const Math::Vector3& pos)
	{
		const float epsilon = 1.0e-5f;	//�덷�̒l
		Math::Vector3 segmentSub;
		Math::Vector3 segmentPoint;
		Math::Vector3 projPos;

		//�����̎n�_����I�_�x�N�g��
		segmentSub = data.endPos - data.beginPos;
		//�����̎n�_����w��̓_�ւ̃x�N�g��
		segmentPoint = pos - data.beginPos;
		//2�̃x�N�g���̓��ς����Ȃ�A�����̎n�_���ŋߖT
		if (Math::Dot3D(segmentSub, segmentPoint) < epsilon)
		{
			return Math::Dot3D(segmentPoint, segmentPoint);
		}
		//�_��������̏I�_�ւ̃x�N�g��
		segmentPoint = pos - data.endPos;
		//2�̃x�N�g���̓��ς����Ȃ�A�����̎n�_���ŋߖT
		if (Math::Dot3D(segmentSub, segmentPoint) < epsilon)
		{
			return Math::Dot3D(segmentPoint, segmentPoint);
		}
		//�ǂ�����Y�����Ȃ��ꍇ�A������ɗ��Ƃ��ē��e���ꂽ�ˉe���ŋߖT
		//([ sin�g�p ]���ċ��߂��邪�A[ �O�ς̑傫�� / �����̃x�N�g���̑傫�� ]�ł����܂�)
		projPos = Math::Cross3D(segmentSub, segmentPoint);

		return Math::Dot3D(projPos, projPos) / Math::Dot3D(segmentSub, segmentSub);
	}
	//!@brief	�����Ɛ����Ƃ̋���(2��)
	//!@param[in]	segment	�Ώۂ̐���
	//!@note	1: ������̍Őڋߓ_�������̐����̓����ɑ��݂���Ƃ�
	//!@note	2: ������̍Đڋߓ_������݂̂̐����̓����ɑ��݂���Ƃ�
	//!@note	3: ������̍Đڋߓ_�������̐����̊O���ɑ��݂���Ƃ�
	const float	GetSegmentDistance(Segment& segment)
	{
		const float epsilon = 1.0e-5f;	//�덷
		Math::Vector3	distance1, distance2;
		Math::Vector3	beginVec;	//�������m�̎n�_�x�N�g��
		Math::Vector3	nearPos1, nearPos2;	//2�̐�����̍Őڋߓ_
		Math::Vector3	pointVec;	//nearPos2 - nearPos1
		float	a, b, c, e, f;
		float	s, t;
		float	denom;
		float	tnom;

		distance1 = data.endPos - data.beginPos;
		distance2 = segment.GetEndPos() - segment.GetBeginPos();
		beginVec = data.beginPos - segment.GetBeginPos();
		a = Math::Dot3D(distance1, distance1);	//����1�̋���2��
		e = Math::Dot3D(distance2, distance2);	//����2�̋���2��

		//�����ꂩ�̐����̒�����0���̃`�F�b�N
		if (a <= epsilon && e <= epsilon)
		{
			pointVec = data.beginPos - segment.GetBeginPos();
			return	Math::Dot3D(pointVec, pointVec);
		}
		//����1�̒�����0
		if (a <= epsilon)
		{
			return segment.GetPointDistance(data.beginPos);
		}
		//����2�̒�����0
		if (e <= epsilon)
		{
			return	GetPointDistance(segment.GetBeginPos());
		}

		//���ς̌v�Z
		b = Math::Dot3D(distance1, distance2);
		f = Math::Dot3D(distance1, beginVec);
		c = Math::Dot3D(distance1, beginVec);

		denom = a * e - b * e;	//��ɔ�
		//���������s�łȂ��ꍇ�A����1��̒���2�ɑ΂���Őڋߓ_���v�Z
		//����1��ɃN�����v�A�����łȂ��ꍇ�A�C�ӂ�s��I��
		if (denom != 0)
		{
			s = Math::Clamp((b * f - c * e) / denom, 0, 1);
		}
		else
		{
			s = 0;
		}
		//����1��̍Őڋߓ_���v�Z
		tnom = b * s + f;
		if (tnom < 0)
		{
			t = 0;
			s = Math::Clamp(-c / a, 0, 1);
		}
		else if (tnom > e)
		{
			t = 1;
			s = Math::Clamp((b - c) / a, 0, 1);
		}
		else
		{
			t = tnom / e;
		}
		nearPos1 = distance1 * s + data.beginPos;
		nearPos2 = distance2 * t + segment.GetBeginPos();
		pointVec = nearPos1 - nearPos2;

		return Math::Dot3D(pointVec, pointVec);
	}
private:
	SegmentData		data;
};


//---------------------------------------
//!@class		CapsuleCollider
//---------------------------------------
class CapsuleCollider : public Component
{
public:
	//!@brief	�R���X�g���N�^
	CapsuleCollider();
	//!@brief	�R���X�g���N�^
	//!@param[in]	segment	�c��
	//!@param[in]	radius	���a
	CapsuleCollider(const Segment& segment, const float radius);
public:
	//!@brief	�c���̎擾
	const Segment&	GetSegment() const;
	//!@brief	���a�̎擾
	const float		GetRadius() const;
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
private:
	CapsuleData	data;
	Segment		segment;
};