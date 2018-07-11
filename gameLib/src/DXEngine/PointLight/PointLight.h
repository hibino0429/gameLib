#pragma once
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/DXEngine/DXDevice/DXDevice.h"

//------------------------------------------------------------------
//!@class		PointLight
//!@brief	�_����
//------------------------------------------------------------------
class PointLight
{
public:
	//!@brief	�R���X�g���N�^
	PointLight();
	//!@brief	�f�X�g���N�^
	virtual ~PointLight();
public:
	//!@brief	�X�V
	void	UpDate();


private:
	struct ConstantBuffer
	{
		DirectX::XMFLOAT4X4	world;
		DirectX::XMFLOAT4X4	view;
		DirectX::XMFLOAT4X4	projection;
		DirectX::XMFLOAT4	lightPos;
		DirectX::XMFLOAT4	attenuation;
	};
private:
	Math::Vector4	position;		//�ʒu
	Math::Vector4	attenuation;	//������
	Math::Vector4	color;			//�F
};