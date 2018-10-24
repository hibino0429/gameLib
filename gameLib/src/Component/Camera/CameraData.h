#pragma once
#include "../../src/DXEngine/Math/Math.h"


//------------------------------------------------
//!@class		CameraData
//------------------------------------------------
struct CameraData
{
	Math::Vector3	eyePos;			//視点
	Math::Vector3	targetPos;		//注視点
	Math::Vector3	upVec;			//上方向ベクトル
	float			fovAngle;		//視野角(度数)
	float			aspect;			//アスペクト比
	float			nearZ;			//前方投影面までの距離
	float			farZ;			//後方投影面までの距離
	Math::Vector4	backGround;		//背景色
	bool			projectionFlag;	//景色のカメラ機能の切り替え
};