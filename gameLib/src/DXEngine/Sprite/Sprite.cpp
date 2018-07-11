#include "Sprite.h"


//!@brief	�R���X�g���N�^
Sprite::Sprite()
{
	position = Math::Vector3(0.0f, 0.0f, 0.0f);
	rotation = Math::Vector3(0.0f, 0.0f, 0.0f);
	scale = Math::Vector3(1.0f, 1.0f, 1.0f);
	color = Math::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
}

//!@brief	�f�X�g���N�^
Sprite::~Sprite()
{

}

//!@brief	�ǂݍ��ݏ���
//!@param[in]	filePath	�t�@�C���p�X
void	Sprite::LoadTexture(const std::string& filePath)
{
	texture.Load(filePath);
	SetPivot(Math::Vector2(0, 0));
}

//!@brief	����
//!@param[in]	buffer	�o�b�t�@
//!@param[in]	width	�e�N�X�`���̕�
//!@param[in]	height	�e�N�X�`���̍���
void	Sprite::Create(const BYTE* const buffer, int width, int height)
{
	//texture.Create(buffer, width, height);
	SetPivot(Math::Vector2(0, 0));
}

//!@brief	�e�N�X�`���̃T�C�Y�̎擾
//!@return	�e�N�X�`���̃T�C�Y
DirectX::XMINT2	Sprite::GetSize() const
{
	return texture.GetSize();
}

//!@brief	�X�v���C�g��[��]�̐ݒ�
//!@param[in]	pivot	��]�̎�
void	Sprite::SetPivot(const Math::Vector2& pivot)
{
	Math::Vector2	textureSize(static_cast<float>(texture.GetSize().x), static_cast<float>(texture.GetSize().y));
	Math::Vector2	offset = textureSize / 2.0f * -pivot;

	mesh.CreatePlane(textureSize / 2.0f, Math::Vector3(offset.x, offset.y, 0.0f));
}

//!@brief	�}�e���A���̎擾

//!@brief	�`��
void	Sprite::Draw()
{
	mesh.SetParams(position, rotation, scale);
	mesh.Draw();
}