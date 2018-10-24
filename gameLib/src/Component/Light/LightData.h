#pragma once
#include "../../src/DXEngine/Math/Math.h"


//���C�g�̎��
enum LightType
{
	Point = 1,
	Spot = 2,
	Directional = 3,
};

//���C�g�̍\����
struct LightData
{
	LightType		type;			//���C�g�̎��
	Math::Vector3	color;			//���C�g�̐F
};




//���s�����̒萔�o�b�t�@
struct DirLightCBuffer
{
	DirectX::XMFLOAT4X4	world;
	DirectX::XMFLOAT4X4	view;
	DirectX::XMFLOAT4X4	projection;
	DirectX::XMFLOAT4	lightDirection;
	DirectX::XMFLOAT4	lightColor;
};

//-------------------------------------------
//!@class		���s�����f�[�^
//-------------------------------------------
struct DirectinalLightData
{
	Math::Vector3	lightDir;		//���̌���
};


//�|�C���g���C�g�̒萔�o�b�t�@
struct PointLightCBuffer
{
	DirectX::XMFLOAT4X4	world;
	DirectX::XMFLOAT4X4	view;
	DirectX::XMFLOAT4X4	projection;
	DirectX::XMFLOAT4	lightPos;
	DirectX::XMFLOAT4	attenuation;
	DirectX::XMFLOAT4	lightColor;
};

//-------------------------------------------
//!@class		�_�����f�[�^
//-------------------------------------------
struct PointLightData
{
	Math::Vector3	pos;			//�����ʒu
	Math::Vector3	attenuation;	//�����p�����[�^
};
