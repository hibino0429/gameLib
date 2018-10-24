#pragma once
#include "../../src/DXEngine/DXDevice/DXDevice.h"


//----------------------------------------------------------------------------------
//概要: シェーダを扱う
//----------------------------------------------------------------------------------
class GeometryShader
{
public:
	GeometryShader();
	~GeometryShader();
private:
	ID3D11GeometryShader*	geometryShader;
};