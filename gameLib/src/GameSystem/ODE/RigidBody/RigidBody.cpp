#include "RigidBody.h"
#include "../../src/Utility/Utility.hpp"

//コンストラクタ
RigidBody::RigidBody(DynamicShape* dynamicShape)
{
	this->dynamicShape = dynamicShape;
}

//デストラクタ
RigidBody::~RigidBody()
{
	Utility::SafeDelete(dynamicShape);
}

//!@brief	剛体の取得
//!@return	保持している剛体の形状を返す
DynamicShape&	RigidBody::GetShape() const
{
	return *dynamicShape;
}