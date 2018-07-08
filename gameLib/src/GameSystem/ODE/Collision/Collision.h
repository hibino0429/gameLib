#pragma once

#include <ode/ode.h>

#if defined(_DEBUG)
#pragma comment(lib,"oded.lib")
#else
#pragma comment(lib,"ode.lib")
#endif

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
	//!@brief	デストラクタ
	~Collision();

private:
	dGeomID		geometory;

};