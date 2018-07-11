#include "Sprite.h"


//!@brief	コンストラクタ
Sprite::Sprite()
{
	position = Math::Vector3(0.0f, 0.0f, 0.0f);
	rotation = Math::Vector3(0.0f, 0.0f, 0.0f);
	scale = Math::Vector3(1.0f, 1.0f, 1.0f);
	color = Math::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
}

//!@brief	デストラクタ
Sprite::~Sprite()
{

}

//!@brief	読み込み処理
//!@param[in]	filePath	ファイルパス
void	Sprite::LoadTexture(const std::string& filePath)
{
	texture.Load(filePath);
	SetPivot(Math::Vector2(0, 0));
}

//!@brief	生成
//!@param[in]	buffer	バッファ
//!@param[in]	width	テクスチャの幅
//!@param[in]	height	テクスチャの高さ
void	Sprite::Create(const BYTE* const buffer, int width, int height)
{
	//texture.Create(buffer, width, height);
	SetPivot(Math::Vector2(0, 0));
}

//!@brief	テクスチャのサイズの取得
//!@return	テクスチャのサイズ
DirectX::XMINT2	Sprite::GetSize() const
{
	return texture.GetSize();
}

//!@brief	スプライトの[軸]の設定
//!@param[in]	pivot	回転の軸
void	Sprite::SetPivot(const Math::Vector2& pivot)
{
	Math::Vector2	textureSize(static_cast<float>(texture.GetSize().x), static_cast<float>(texture.GetSize().y));
	Math::Vector2	offset = textureSize / 2.0f * -pivot;

	mesh.CreatePlane(textureSize / 2.0f, Math::Vector3(offset.x, offset.y, 0.0f));
}

//!@brief	マテリアルの取得

//!@brief	描画
void	Sprite::Draw()
{
	mesh.SetParams(position, rotation, scale);
	mesh.Draw();
}