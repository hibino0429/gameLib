#pragma once
#include "../../src/DXEngine/DXDevice/DXDevice.h"


//----------------------------------------------------------------------------------
//�T�v: �V�F�[�_������
//----------------------------------------------------------------------------------
class GeometryShader
{
public:
	GeometryShader();
	~GeometryShader();
private:
	ID3D11GeometryShader*	geometryShader;
};