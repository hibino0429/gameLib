#pragma once

#include <string>
#include "../../src/Fbx/Fbx.h"
#include "../../src/PrimitiveData/PrimitiveData.h"
#include "../../src/Camera/Camera.h"

//----------------------------------------------------------------------------------------
//!@class		Mo
//!@brief	�T���v���ň����v���O�������쐬����t�@�C��
//----------------------------------------------------------------------------------------
class Model
{
public:
	Model();
	//!@brief	�R���X�g���N�^
	//!@param[in]	filePath	�t�@�C���p�X
	Model(const std::string& filePath);
	~Model();

	void	UpDate();
	void	Render();
private:
	//!@brief	�C���v�b�g���C�A�E�g�̍쐬
	void	CreateInputLayout();
	//!@brief	�萔�o�b�t�@�̍쐬
	void	CreateConstantBuffer();
public:
	//!@brief	�}�g���b�N�X�̐ݒ�
	void	SetMatrix(Camera* camera);

private:
	//�萔�o�b�t�@
	struct ConstantBuffer
	{
		DirectX::XMFLOAT4X4	world;
		DirectX::XMFLOAT4X4	view;
		DirectX::XMFLOAT4X4	projection;
	};
private:
	VertexShader*	vertexShader;
	PixelShader*	pixelShader;
	ID3D11Buffer*	constantBuf;
	Primitive*		primitive;
	FbxModel*		fbxModel;
	Math::Vector3	pos;
	Math::Vector3	angle;
	Math::Vector3	scale;
};