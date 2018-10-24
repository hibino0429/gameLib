#pragma once
#include "../../src/Component/Material/MaterialData.h"



//----------------------------------------------------------------
//!@class		Shader
//!@brief	�V�F�[�_���N���X
//----------------------------------------------------------------
class Shader
{
public:
	Shader() = delete;
	Shader(const std::string& filePath);
	~Shader();
public:
	//!@brief	�V�F�[�_�̃p�����[�^�̐���
//!@param[in]	inputDesc	�C���v�b�g���C�A�E�g�̍쐬
	bool	CreateShaderParam(D3D11_INPUT_ELEMENT_DESC* inputDesc, const UINT elemNum);
	//!@brief	�e�N�X�`���p�̃V�F�[�_�p�����[�^�̐���
	//!@note	�f�t�H���g�̐ݒ�
	bool	CreateTextureShaderParam();
	//!@brief	�F�̃V�F�[�_�p�����[�^�̐���
	//!@note	�f�t�H���g�̐ݒ�
	bool	CreateColorShaderParam();
	//!@brief	�X�V
	void	UpDate();
private:
	VertexShader*	vertexShader;
	PixelShader*	pixelShader;
	std::string		filePath;
};