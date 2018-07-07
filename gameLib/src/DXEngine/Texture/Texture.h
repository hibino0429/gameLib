#pragma once


#include "../../src/DXEngine/DXDevice/DXDevice.h"
#include <string>
#include <memory>
#include "../../src/DXEngine/Math/Math.h"

//---------------------------------------------------------------------------------
//!@class		テクスチャ
//!@brief	テクスチャを扱います
//---------------------------------------------------------------------------------
class Texture
{
public:
	//!@brief コンストラクタ
	Texture();
	//!@brief	コンストラクタ
	//!@param[in]	filePath	ファイルパス
	Texture(const std::string& filePath);
	//!@brief	コンストラクタ
	//!@param[in]	buffer	バッファ
	//!@param[in]	width	テクスチャの幅
	//!@param[in]	height	テクスチャの幅
	Texture(const BYTE* const buffer, int width, int height);

	//!@brief デストラクタ
	~Texture();

	//!@brief	テクスチャのロード
	//!@param[in]	filePath	ファイルパス
	//!@return	成功なら true 失敗なら false
	bool	Load(const std::string& filePath);

	//!@brief		作成
	//!@return		成功 true 失敗 false
	bool	Create();

	//!@brief		作成
	//!@param[in]	buffer	Byteバッファ
	//!@param[in]	width	幅
	//!@param[in]	height	高さ
	void	Create(const BYTE* const buffer, int width, int height);

	//!@brief		テクスチャのアタッチ
	//!@param[in]	slot	テクスチャをどこのスロットにセットするか指定
	void	Attach(const int slot);

	//!@brief		レンダーテクスチャの取得[const]
	//!@return		レンダーテクスチャ
	ID3D11Texture2D*	Get() const;

	//!@brief		テクスチャのサイズを取得
	//!@return		textureSize	テクスチャのサイズ
	DirectX::XMINT2	GetSize() const;

	//!@brief		テクスチャのインターフェイスの取得
	//!@return		ID3D11Texture2D&	テクスチャのインターフェイス
	ID3D11Texture2D&	GetInterface();

	
public:
	//!@brief	読み込み
	bool	LoadTex(const std::string& filePath);
	//!@brief	設定
	void	SetParam(const BYTE* const buffer,int width,int height);
	//!@brief	テクスチャを送る
	void	Send();
	//!@brief	シェーダリソースビュー(texture用)の設定
	void	SetShaderResourceView();
	//!@brief	描画
	void	Render();

private:
	//!@brief	画像ファイルからシェーダ・リソース・ビューを作成
	bool	CreateShaderResourceView();
	//!@brief	サンプラーの作成
	//!@return	成功ならtrue
	bool	CreateSampler();
private:
	ID3D11ShaderResourceView*	texResourceView;	//シェーダ・リソース・ビューを受け取る
	ID3D11SamplerState*			textureSampler;		//テクスチャサンプラー
	ID3D11Texture2D*			texture2D;
	Math::Vector2				size;

	UINT						imageWidth;
	UINT						imageHeight;
};



//テクスチャなどの色の指定をRGBAの順番などに注意する
