#pragma once
#include "../../src/GameSystem/Fbx/Fbx.h"
#include "../../src/DXEngine/PrimitiveData/PrimitiveData.h"
#include "../../src/Component/AnimationData/AnimationData.h"
#include "../../src/DXEngine/Math/Math.h"

//!@class モデルのデータ
struct ModelData
{
	Primitive*		primitive;
	FbxModel*		fbxModel;
	Math::Vector3	pos;
	Math::Vector3	angle;
	Math::Vector3	scale;
	AnimationData*	animationData;
};

