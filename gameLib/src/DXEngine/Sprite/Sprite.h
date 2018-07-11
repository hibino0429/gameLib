#pragma once

#include <string>
#include <vector>
#include "../../src/DXEngine/DXDevice/DXDevice.h"
#include "../../src/DXEngine/Mesh/Mesh.h"
#include "../../src/DXEngine/Texture/Texture.h"

//---------------------------------------------------------------------
//!@brief �X�v���C�g
//---------------------------------------------------------------------
class Sprite
{
public:
	//!@brief	�R���X�g���N�^
	Sprite();
	//!@brief	�f�X�g���N�^
	~Sprite();

	//!@brief	�ǂݍ��ݏ���
	//!@param[in]	filePath	�t�@�C���p�X
	void	LoadTexture(const std::string& filePath);

	//!@brief	����
	//!@param[in]	buffer	�o�b�t�@
	//!@param[in]	width	�e�N�X�`���̕�
	//!@param[in]	height	�e�N�X�`���̍���
	void	Create(const BYTE* const buffer, int width, int height);

	//!@brief	�e�N�X�`���̃T�C�Y�̎擾
	//!@return	�e�N�X�`���̃T�C�Y
	DirectX::XMINT2	GetSize() const;

	//!@brief	�X�v���C�g��[��]�̐ݒ�
	//!@param[in]	pivot	��]�̎�
	void	SetPivot(const Math::Vector2& pivot);

	//!@brief	�}�e���A���̎擾

	//!@brief	�`��
	void	Draw();


private:
	Math::Vector3	position;
	Math::Vector3	rotation;
	Math::Vector3	scale;
	Math::Vector3	color;
	Mesh			mesh;
	Texture			texture;
};