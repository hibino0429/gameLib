#pragma once
#include "../../src/Device/DXDevice/DXDevice.h"


//----------------------------------------------------------------------------------
//!@class		VertexShader
//!@brief	���_�V�F�[�_�������܂�
//----------------------------------------------------------------------------------
class VertexShader
{
public:
	//!@brief	�R���X�g���N�^
	VertexShader();
	//!@brief	�f�X�g���N�^
	~VertexShader();

	//!@brief		�쐬
	//!@param[in]	fileName			�t�@�C����
	//!@param[in]	inputElementDesc	�C���v�b�g���C�A�E�g���
	//!@param[in]	inputElementDescNum	�C���v�b�g���C�A�E�g���̐�
	bool	Create(const std::string& fileName, D3D11_INPUT_ELEMENT_DESC* inputElementDesc, int elementNum);

	//!@brief		�ݒ�
	void	Set();

private:
	ID3D11VertexShader*		vertexShader;	//���_�V�F�[�_
	ID3D11InputLayout*		inputLayout;	//�C���v�b�g���C�A�E�g
};