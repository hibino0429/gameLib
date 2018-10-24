#pragma once
#include "../../src/DXEngine/DXDevice/DXDevice.h"
#include <string>
#include <memory>
#include "../../src/DXEngine/Math/Math.h"



//---------------------------------------------------------------------------------
//!@class		�e�N�X�`��
//!@brief	�e�N�X�`���������܂�
//---------------------------------------------------------------------------------
class Texture
{
public:
	//!@brief �R���X�g���N�^
	Texture() = delete;
	//!@brief	�R���X�g���N�^
	//!@param[in]	filePath	�t�@�C���p�X
	Texture(const std::string& filePath);

	//!@brief �f�X�g���N�^
	~Texture();
public:
	//!@brief		�e�N�X�`���̃A�^�b�`
	//!@param[in]	slot	�e�N�X�`�����ǂ��̃X���b�g�ɃZ�b�g���邩�w��
	void	Attach(const int slot);

	//!@brief		�e�N�X�`���̃T�C�Y���擾
	//!@return		textureSize	�e�N�X�`���̃T�C�Y
	DirectX::XMINT2	GetSize() const;
	//!@brief	�`��
	void	Render();
private:
	//!@brief		�����_�[�e�N�X�`���̎擾[const]
	//!@return		�����_�[�e�N�X�`��
	ID3D11Texture2D*	Get() const;
	//!@brief		�e�N�X�`���̃C���^�[�t�F�C�X�̎擾
	//!@return		ID3D11Texture2D&	�e�N�X�`���̃C���^�[�t�F�C�X
	ID3D11Texture2D&	GetInterface();
private:
	//!@brief	�ǂݍ���
	bool	LoadTex(const std::string& filePath);
	//!@brief	�ݒ�
	void	SetParam(const BYTE* const buffer,int width,int height);
	//!@brief	�e�N�X�`���𑗂�
	void	Send();
	//!@brief	�V�F�[�_���\�[�X�r���[(texture�p)�̐ݒ�
	void	SetShaderResourceView();

private:
	//!@brief	�摜�t�@�C������V�F�[�_�E���\�[�X�E�r���[���쐬
	bool	CreateShaderResourceView();
	//!@brief	�T���v���[�̍쐬
	//!@return	�����Ȃ�true
	bool	CreateSampler();
private:
	ID3D11ShaderResourceView*	texResourceView;	//�V�F�[�_�E���\�[�X�E�r���[���󂯎��
	ID3D11SamplerState*			textureSampler;		//�e�N�X�`���T���v���[
	ID3D11Texture2D*			texture2D;
	Math::Vector2				size;

	UINT						imageWidth;
	UINT						imageHeight;
};



//�e�N�X�`���Ȃǂ̐F�̎w���RGBA�̏��ԂȂǂɒ��ӂ���
