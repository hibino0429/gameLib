#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define warning (disable : 4819)	

#include <ode/ode.h>

#if defined(_DEBUG)
#pragma comment(lib,"oded.lib")
#else
#pragma comment(lib,"ode.lib")
#endif

#include "../../src/GameSystem/ODE/DynamicShape/DynamicShape.h"
#include "../../src/GameSystem/ODE/Physics/Physics.h"

//----------------------------------------------------------------------------------------
//!@class		Collision
//!@brief	コリジョンを扱うクラス
//!@brief	衝突判定を行う形状
//----------------------------------------------------------------------------------------
class Collision
{
public:
	//!@brief	コンストラクタ
	Collision();
	//!@brief	コンストラクタ
	//!@param[in]	dynamicShape	形状
	Collision(DynamicShape* dynamicShape);
	//!@brief	デストラクタ
	~Collision();
public:
	//!@brief	形状の取得
	//!@return	保持している形状
	const DynamicShape&	GetDynamicShape() const;

public:
	//!@brief	衝突したかを判定
	//!@brief	コリジョン同士が触れた瞬間
	//!@param[in]	collision	相手のコリジョン
	//!@return	true: 衝突した false: 衝突していない
	bool	OnCollisionEnter(Collision* collision);
	//!@brief	衝突しているかを判定
	//!@brief	コリジョン同士が触れている間
	//!@return	true: 衝突している false: 衝突していない
	bool	OnCollisionStay(Collision* collision);
	//!@brief	衝突をやめたかを判定
	//!@brief	コリジョン同士が離れたとき
	//!@return	true: 衝突しなくなった false: 衝突している
	bool	OnCollisionExit(Collision* collision);
private:
	DynamicShape*			dynamicShape;
};