#pragma once
#include "../../src/DXEngine/Math/Math.h"



//線分
struct SegmentData
{
	Math::Vector3	beginPos;
	Math::Vector3	endPos;
};


//球
struct SphereData
{
	Math::Vector3	center;
	float			radius;
};


//カプセル
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
	Math::Vector3	pos;			//位置
	Math::Vector3	size;			//大きさ
	Math::Vector3	normalDir[3];	//方向ベクトル
	float			length[3];		//各軸方向の長さ
};



