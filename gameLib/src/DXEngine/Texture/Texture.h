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
	Texture() = delete;
	//!@brief	コンストラクタ
	//!@param[in]	filePath	ファイルパス
	Texture(const std::string& filePath);

	//!@brief デストラクタ
	~Texture();
public:
	//!@brief		テクスチャのアタッチ
	//!@param[in]	slot	テクスチャをどこのスロットにセットするか指定
	void	Attach(const int slot);

	//!@brief		テクスチャのサイズを取得
	//!@return		textureSize	テクスチャのサイズ
	DirectX::XMINT2	GetSize() const;
	//!@brief	描画
	void	Render();
private:
	//!@brief		レンダーテクスチャの取得[const]
	//!@return		レンダーテクスチャ
	ID3D11Texture2D*	Get() const;
	//!@brief		テクスチャのインターフェイスの取得
	//!@return		ID3D11Texture2D&	テクスチャのインターフェイス
	ID3D11Texture2D&	GetInterface();
private:
	//!@brief	読み込み
	bool	LoadTex(const std::string& filePath);
	//!@brief	設定
	void	SetParam(const BYTE* const buffer,int width,int height);
	//!@brief	テクスチャを送る
	void	Send();
	//!@brief	シェーダリソースビュー(texture用)の設定
	void	SetShaderResourceView();

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
