#include "Collision.h"

//コンストラクタ
Collision::Collision()
{
	
}
//!@brief	コンストラクタ
//!@param[in]	dynamicShape	形状
Collision::Collision(DynamicShape* dynamicShape)
{
	this->dynamicShape = dynamicShape;
}

//デストラクタ
Collision::~Collision()
{
	//形状の解放責任をもつ
	delete dynamicShape;
}


//!@brief	形状の取得
//!@return	保持している形状
const DynamicShape&	Collision::GetDynamicShape() const
{
	return *dynamicShape;
}

//!@brief	衝突したかを判定
//!@brief	コリジョン同士が触れた瞬間
//!@param[in]	collision	相手のコリジョン
//!@return	true: 衝突した false: 衝突していない
bool	Collision::OnCollisionEnter(Collision* collision)
{
	return true;
}
//!@brief	衝突しているかを判定
//!@brief	コリジョン同士が触れている間
//!@return	true: 衝突している false: 衝突していない
bool	Collision::OnCollisionStay(Collision* collision)
{
	return true;
}
//!@brief	衝突をやめたかを判定
//!@brief	コリジョン同士が離れたとき
//!@return	true: 衝突しなくなった false: 衝突している
bool	Collision::OnCollisionExit(Collision* collision)
{
	return true;
}