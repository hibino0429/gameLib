#pragma once
#include <string>
#include "../../src/Engine/Engine.h"

#include "../../src/Engine/DXEngine/DXEngine.h"



//----------------------------------------------------------------
//!@brief エンジンの生成を担当
//----------------------------------------------------------------
class EngineCreator
{
public:
	EngineCreator();
	~EngineCreator();

	//概要: エンジンの生成
	//static Engine*	CreateEngine(const std::string& engineName);
private:
	//static Engine*	dxEngine;
};