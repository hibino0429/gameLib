#pragma once
#include "../../src/Component/Material/MaterialData.h"



//----------------------------------------------------------------
//!@class		Shader
//!@brief	シェーダをクラス
//----------------------------------------------------------------
class Shader
{
public:
	Shader() = delete;
	Shader(const std::string& filePath);
	~Shader();
public:
	//!@brief	シェーダのパラメータの生成
//!@param[in]	inputDesc	インプットレイアウトの作成
	bool	CreateShaderParam(D3D11_INPUT_ELEMENT_DESC* inputDesc, const UINT elemNum);
	//!@brief	テクスチャ用のシェーダパラメータの生成
	//!@note	デフォルトの設定
	bool	CreateTextureShaderParam();
	//!@brief	色のシェーダパラメータの生成
	//!@note	デフォルトの設定
	bool	CreateColorShaderParam();
	//!@brief	更新
	void	UpDate();
private:
	VertexShader*	vertexShader;
	PixelShader*	pixelShader;
	std::string		filePath;
};