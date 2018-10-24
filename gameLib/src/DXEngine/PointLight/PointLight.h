#pragma once
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/DXEngine/DXDevice/DXDevice.h"
#include "../../src/DXEngine/Shader/VertexShader/VertexShader.h"
#include "../../src/DXEngine/Shader/PixelShader/PixelShader.h"

//
////------------------------------------------------------------------
////!@class		PointLight
////!@brief	�_����
////------------------------------------------------------------------
//class PointLight
//{
//public:
//	//!@brief	�R���X�g���N�^
//	PointLight();
//	//!@brief	�f�X�g���N�^
//	virtual ~PointLight();
//public:
//	//!@brief	�X�V
//	void	UpDate(Camera* camera);
//
//
//private:
//	struct ConstantBuffer
//	{
//		DirectX::XMFLOAT4X4	world;
//		DirectX::XMFLOAT4X4	view;
//		DirectX::XMFLOAT4X4	projection;
//		DirectX::XMFLOAT4	lightPos;
//		DirectX::XMFLOAT4	attenuation;
//	};
//private:
//	Math::Vector4	position;		//�ʒu
//	Math::Vector4	attenuation;	//������
//	Math::Vector4	color;			//�F
//	ID3D11Buffer*	constantBuf;	//�萔�o�b�t�@
//	ConstantBuffer	constant;
//	VertexShader*	vertexShader;
//	PixelShader*	pixelShader;
//};
//
