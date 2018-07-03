#pragma once
#include <vector>


//---------------------------------------------------------------------
//!@class		Vertex
//!@brief	���_�f�[�^�����f�[�^
//!@brief	�f�o�C�X�ȂǂɈˑ����Ȃ��f�[�^
//---------------------------------------------------------------------
class Vertex
{
public:
	Vertex();
	Vertex(float x, float y, float z);
	Vertex(float x, float y, float z, float color0, float color1);
	Vertex(const Vertex& vertex);

	~Vertex();
public:
	float	x;
	float	y;
	float	z;
	float	color[2];
};