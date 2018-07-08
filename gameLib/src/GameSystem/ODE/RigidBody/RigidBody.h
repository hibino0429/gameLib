#pragma once
#include "../../src/GameSystem/ODE/DynamicShape/DynamicShape.h"


//修正箇所
//依存性のない数学ライブラリを作成し、適用させる必要がある

//----------------------------------------------------------------------------------------
//!@class		RigidBody
//!@brief	剛体を扱うクラス
//!@brief	適用させることで物理挙動をさせることができる
//!@brief	剛体の形状(dynamicShape)の解放を行う
//----------------------------------------------------------------------------------------
class RigidBody
{
public:
	//!@brief	コンストラクタ
	//!@param[in]	dynamicShape	形状
	RigidBody(DynamicShape* dynamicShape);
	//!@brief	デストラクタ
	//!@brief	形状の解放責任を持つ
	virtual ~RigidBody();
public:
	//!@brief	剛体の取得
	//!@return	保持している剛体の形状を返す
	DynamicShape&	GetShape() const;

	//アライメント対策
	void*	operator new(size_t size)
	{
		return _mm_malloc(size, 16);
	}
	void	operator delete(void* p)
	{
		_mm_free(p);
	}
private:
	DynamicShape*	dynamicShape;	//剛体の形状
};

