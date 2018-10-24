#pragma once
#include <vector>
#include "../../src/DXEngine/DXDevice/DXDevice.h"
#include "../../src/DXEngine/Texture/Texture.h"
#include "../../src/DXEngine/Shader/VertexShader/VertexShader.h"
#include "../../src/DXEngine/Shader/PixelShader/PixelShader.h"

//-------------------------------------------------------------------
//!@class		Materials
//!@brief	�}�e���A����������
//!@brief	�V�F�[�_���g�p���ĐF���������܂�
//-------------------------------------------------------------------
class Materials
{
public:
	//!@brife	�萔�o�b�t�@�̒�`
	struct ConstantBuffer
	{
		ConstantBuffer() : ptr(nullptr), buffer(nullptr) {};
		void*			ptr;
		ID3D11Buffer*	buffer;
	};

public:
	//!@brief	�R���X�g���N�^
	Materials();
	//!@brief	�f�X�g���N�^
	~Materials();

	//!@brief	�V�F�[�_�[�t�@�C����ǂݍ���
	//!@param[in]	filePath	�t�@�C���p�X
	void	Load(const std::string& filePath);
	
	//!@brief	�}�e���A���̐���
	//!@param[in]	shaderSource	�V�F�[�_�[�̃\�[�X
	void	Create(const std::string& shaderSource);

	//!@brief	�V�F�[�_�[�Ŏg�p����R���X�^���g�o�b�t�@�̐ݒ�
	//!@param[in]	slot	�ݒ肷��ԍ�
	//!@param[in]	constantBuf	�R���X�^���g�o�b�t�@
	//!@param[in]	size	�o�b�t�@�̑傫��
	void	SetConstantBuffer(const int slot, void* constantBuf, size_t size);

	//!@brief	�V�F�[�_�[�Ŏg�p����e�N�X�`���̐ݒ�
	//!@param[in]	slot	�ݒ肷��ԍ�
	//!@param[in]	texture	�e�N�X�`��
	void	SetTexture(const int slot, Texture* texture);

	//!@brief	�V�F�[�_�[���O���t�B�b�N�X�ɃA�^�b�`
	void	Attach();
private:
	Texture*		textures[10];
	ConstantBuffer	constantBuffer[10];
	VertexShader*	vertexShader;
	PixelShader*	pixelShader;
};