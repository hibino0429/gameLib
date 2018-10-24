#pragma once
#include "../../src/DXEngine/Math/Math.h"



//����
struct SegmentData
{
	Math::Vector3	beginPos;
	Math::Vector3	endPos;
};


//��
struct SphereData
{
	Math::Vector3	center;
	float			radius;
};


//�J�v�Z��
struct CapsuleData
{
	SegmentData		segment;
	float			radius;
	Math::Vector3	center;
	float			height;
};

//AABB
struct AABBData
{
	Math::Vector3	minPos;
	Math::Vector3	maxPos;
	Math::Vector3	centerPos;
	Math::Vector3	size;
};


//OBB
struct OBBData
{
	Math::Vector3	pos;			//�ʒu
	Math::Vector3	size;			//�傫��
	Math::Vector3	normalDir[3];	//�����x�N�g��
	float			length[3];		//�e�������̒���
};



