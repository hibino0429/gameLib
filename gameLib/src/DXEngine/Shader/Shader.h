#pragma once
#include "../../src/Engine/Device/Device.h"
#include "../../src/DXEngine/DXEngine/DXEngine.h"

//----------------------------------------------------------------------------------
//�T�v: �V�F�[�_������
//----------------------------------------------------------------------------------
class Shader
{
public:
	//�T�v:�@�R���X�g���N�^
	Shader();
	//�T�v: �f�X�g���N�^
	~Shader();

	//�T�v: ���_�V�F�[�_�̃R�[�h�R���p�C��
	//�߂�l: �����Ȃ�true
	bool	ComplieVertexShader();
	//�T�v: �s�N�Z���V�F�[�_�̃R�[�h�R���p�C��
	//�߂�l: �����Ȃ�true
	bool	CompliePixelShader();
	//�T�v: �W�I���g���̃R�[�h�R���p�C��
	//�߂�l: �����Ȃ�true
	bool	ComplieGeometryShader();

	//�T�v: ���_�V�F�[�_�̍쐬
	//�߂�l: �����Ȃ�true
	bool	CreateVertexShader();
	//�T�v: �s�N�Z���V�F�[�_�̍쐬
	//�߂�l: �����Ȃ�true
	bool	CreatePixelShader();
	//�T�v: �W�I���g���V�F�[�_�̍쐬
	//�߂�l: �����Ȃ�true
	bool	CreateGeometryShader();
	
public:
	//�T�v: �V�F�[�_�̒萔�o�b�t�@�̐ݒ�
	void	SetShaderConstantBuffer();

	//�T�v: ���_�C���v�b�g���C�A�E�g�̍쐬
	//�߂�l: �����Ȃ�true
	bool	CreateInputLayout();

	//�T�v: ���_�V�F�[�_�I�u�W�F�N�g�̎擾
	ID3D11VertexShader*	GetVertexShader() const;
	//�T�v: �s�N�Z���V�F�[�_�I�u�W�F�N�g�̎擾
	ID3D11PixelShader*	GetPixelShader() const;

	//�T�v: �u�����h�E�X�e�[�g�E�I�u�W�F�N�g�̍쐬
	//�߂�l: �����Ȃ�true
	bool	CreateBlendState();
	//�T�v: ���X�^���C�U�E�X�e�[�g�E�I�u�W�F�N�g�̍쐬
	//�߂�l: �����Ȃ�true
	bool	CreateRasterizerState();
	//�T�v: �[�x/�X�e���V���E�X�e�[�g�E�I�u�W�F�N�g�̍쐬
	//�߂�l: �����Ȃ�true
	bool	CreateDepthStencilState();
private:
	ID3DBlob*			vertexBlob;			//���_�V�F�[�_�u���u
	ID3DBlob*			pixelBlob;			//�s�N�Z���u���u
	ID3DBlob*			geometryBlob;		//�W�I���g���u���u
	ID3D11InputLayout*	inputLayout;		//�C���v�b�g���C�A�E�g
private:
	ID3D11VertexShader*		vertexShader;	//���_�V�F�[�_�I�u�W�F�N�g
	ID3D11PixelShader*		pixelShader;	//�s�N�Z���V�F�[�_�I�u�W�F�N�g
	ID3D11GeometryShader*	geometryShader;	//�W�I���g���V�F�[�_�I�u�W�F�N�g
	ID3D11BlendState*		blendState;		//�u�����h�X�e�[�g�I�u�W�F�N�g
	ID3D11RasterizerState*	rasterizerState;//���X�^���C�U�X�e�[�g�I�u�W�F�N�g
	ID3D11DepthStencilState*	depthStencilState;	//�[�x�E�X�e���V���X�e�[�g�I�u�W�F�N�g

private:
	UINT			compileOption;			//�R���p�C���I�v�V����
};