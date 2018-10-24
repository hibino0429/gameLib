#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"


//----------------------------------------------------------------------------
//!@class		MeshRender
//!@brief	Meshを描画するためのコンポーネント
//!@brief	複数のマテリアルなどをつけることができる
//----------------------------------------------------------------------------
class MeshRender : public Component
{
public:
	//!@brief	コンストラクタ
	MeshRender() {  }
	~MeshRender() {}
private:

};