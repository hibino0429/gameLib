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
	//!@brief	2Dのボックスを扱う
	//!@brief	x,y:ボックスの座標, w,h:ボックスの幅高
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
		//!@brief	正方形のベクトルの検出(右回り)
		const Math::Vector2&	GetVector(const VectorNo& no) const;

	public:
		float x, y;
		float width;
		float height;
	};

}



//--------------------------------------------------------------------
//!@class		Sprite2D
//!@brief	スプライトを2D空間で扱う
//!@detail	画像のファイルパスは日本語では読み込み不可
//!@detail	画像の回転位置はデフォルトで中心
//--------------------------------------------------------------------
class Sprite2D
{
public:
	//!@brief	コンストラクタ
	//!@param[in]	filePath	使用する画像ファイルパス
	Sprite2D(const std::string& filePath);
	//!@brief	デストラクタ
	~Sprite2D();
public:
	//!@brief	描画
	//!@param[in]	draw	描画位置(x,y,width,height)
	//!@param[in]	src		ソースの範囲(x,y,width,height)
	//!@param[in]	isCenter	true:draw画像の中心座標  false:左上の座標
	//!@param[in]	color	色(r,g,b,a)
	void	Draw(const Math::Box2D& draw, const Math::Box2D& src, bool isCenter = true, const Math::Color& color = Math::Color(1, 1, 1, 1));
	//!@brief	回転量の調節
	//!@param[in]	rotate	回転量(度数法)
	void	SetRotation(const float rotate);
private:
	DirectX::SpriteBatch*		spriteBatch;
	ID3D11ShaderResourceView*	textureResourceView;
	ID3D11Resource*	resource;
	float			rotate;
	Math::Vector2	pivot;
};

