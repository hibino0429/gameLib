#pragma once
#include <string>
#include <iostream>
#include <../Texture/Inc/SpriteBatch.h>
#include <../Texture/Inc/WICTextureLoader.h>

#include "../../src/DXEngine/Math/Math.h"
#include "../../src/DXEngine/DXEngine/DXEngine.h"
#include "../../src/Utility/Utility.hpp"

#pragma comment(lib,"DirectXTK.lib")


namespace Math
{
	//----------------------------------------------------------------------------
	//!@class		Box2D
	//!@brief	2D�̃{�b�N�X������
	//!@brief	x,y:�{�b�N�X�̍��W, w,h:�{�b�N�X�̕���
	//----------------------------------------------------------------------------
	class Box2D : public RECT
	{
	public:
		Box2D() {}
		Box2D(const Box2D& box2D)
		{
			x = box2D.x;
			y = box2D.y;
			width = box2D.width;
			height = box2D.height;
			this->left = (LONG)x;
			this->top = (LONG)y;
			this->bottom = (LONG)y + (LONG)height;
			this->right = (LONG)x + (LONG)width;
		}
		Box2D(float x, float y, float w, float h)
		{
			this->x = x;
			this->y = y;
			this->width = w;
			this->height = h;

			this->left = (LONG)x;
			this->top = (LONG)y;
			this->bottom = (LONG)y + (LONG)height;
			this->right = (LONG)x + (LONG)width;
		}

		enum class VectorNo
		{
			No1,
			No2,
			No3,
			No4,
		};
		//!@brief	�����`�̃x�N�g���̌��o(�E���)
		const Math::Vector2&	GetVector(const VectorNo& no) const;

	public:
		float x, y;
		float width;
		float height;
	};

}



//--------------------------------------------------------------------
//!@class		Sprite2D
//!@brief	�X�v���C�g��2D��Ԃň���
//!@detail	�摜�̃t�@�C���p�X�͓��{��ł͓ǂݍ��ݕs��
//!@detail	�摜�̉�]�ʒu�̓f�t�H���g�Œ��S
//--------------------------------------------------------------------
class Sprite2D
{
public:
	//!@brief	�R���X�g���N�^
	//!@param[in]	filePath	�g�p����摜�t�@�C���p�X
	Sprite2D(const std::string& filePath);
	//!@brief	�f�X�g���N�^
	~Sprite2D();
public:
	//!@brief	�`��
	//!@param[in]	draw	�`��ʒu(x,y,width,height)
	//!@param[in]	src		�\�[�X�͈̔�(x,y,width,height)
	//!@param[in]	isCenter	true:draw�摜�̒��S���W  false:����̍��W
	//!@param[in]	color	�F(r,g,b,a)
	void	Draw(const Math::Box2D& draw, const Math::Box2D& src, bool isCenter = true, const Math::Color& color = Math::Color(1, 1, 1, 1));
	//!@brief	��]�ʂ̒���
	//!@param[in]	rotate	��]��(�x���@)
	void	SetRotation(const float rotate);
private:
	DirectX::SpriteBatch*		spriteBatch;
	ID3D11ShaderResourceView*	textureResourceView;
	ID3D11Resource*	resource;
	float			rotate;
	Math::Vector2	pivot;
};

