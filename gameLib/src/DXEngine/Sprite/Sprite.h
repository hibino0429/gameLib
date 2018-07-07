#pragma once

#include <string>
#include <vector>
#include "../../src/DXEngine/DXDevice/DXDevice.h"
#include "../../src/DXEngine/Mesh/Mesh.h"
#include "../../src/DXEngine/Texture/Texture.h"

//---------------------------------------------------------------------
//!@brief スプライト
//---------------------------------------------------------------------
class Sprite
{
public:
	//!@brief	コンストラクタ
	Sprite();
	//!@brief	デストラクタ
	~Sprite();

	//!@brief	読み込み処理
	//!@param[in]	filePath	ファイルパス
	void	LoadTexture(const std::string& filePath);

	//!@brief	生成
	//!@param[in]	buffer	バッファ
	//!@param[in]	width	テクスチャの幅
	//!@param[in]	height	テクスチャの高さ
	void	Create(const BYTE* const buffer, int width, int height);

	//!@brief	テクスチャのサイズの取得
	//!@return	テクスチャのサイズ
	DirectX::XMINT2	GetSize() const;

	//!@brief	スプライトの[軸]の設定
	//!@param[in]	pivot	回転の軸
	void	SetPivot(const Math::Vector2& pivot);

	//!@brief	マテリアルの取得

	//!@brief	描画
	void	Draw();


private:
	Math::Vector3	position;
	Math::Vector3	rotation;
	Math::Vector3	scale;
	Math::Vector3	color;
	Mesh			mesh;
	Texture			texture;
};