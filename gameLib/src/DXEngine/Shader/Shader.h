#pragma once
#include "../../src/Engine/Device/Device.h"
#include "../../src/DXEngine/DXEngine/DXEngine.h"

//----------------------------------------------------------------------------------
//概要: シェーダを扱う
//----------------------------------------------------------------------------------
class Shader
{
public:
	//概要:　コンストラクタ
	Shader();
	//概要: デストラクタ
	~Shader();

	//概要: 頂点シェーダのコードコンパイル
	//戻り値: 成功ならtrue
	bool	ComplieVertexShader();
	//概要: ピクセルシェーダのコードコンパイル
	//戻り値: 成功ならtrue
	bool	CompliePixelShader();
	//概要: ジオメトリのコードコンパイル
	//戻り値: 成功ならtrue
	bool	ComplieGeometryShader();

	//概要: 頂点シェーダの作成
	//戻り値: 成功ならtrue
	bool	CreateVertexShader();
	//概要: ピクセルシェーダの作成
	//戻り値: 成功ならtrue
	bool	CreatePixelShader();
	//概要: ジオメトリシェーダの作成
	//戻り値: 成功ならtrue
	bool	CreateGeometryShader();
	
public:
	//概要: シェーダの定数バッファの設定
	void	SetShaderConstantBuffer();

	//概要: 頂点インプットレイアウトの作成
	//戻り値: 成功ならtrue
	bool	CreateInputLayout();

	//概要: 頂点シェーダオブジェクトの取得
	ID3D11VertexShader*	GetVertexShader() const;
	//概要: ピクセルシェーダオブジェクトの取得
	ID3D11PixelShader*	GetPixelShader() const;

	//概要: ブレンド・ステート・オブジェクトの作成
	//戻り値: 成功ならtrue
	bool	CreateBlendState();
	//概要: ラスタライザ・ステート・オブジェクトの作成
	//戻り値: 成功ならtrue
	bool	CreateRasterizerState();
	//概要: 深度/ステンシル・ステート・オブジェクトの作成
	//戻り値: 成功ならtrue
	bool	CreateDepthStencilState();
private:
	ID3DBlob*			vertexBlob;			//頂点シェーダブロブ
	ID3DBlob*			pixelBlob;			//ピクセルブロブ
	ID3DBlob*			geometryBlob;		//ジオメトリブロブ
	ID3D11InputLayout*	inputLayout;		//インプットレイアウト
private:
	ID3D11VertexShader*		vertexShader;	//頂点シェーダオブジェクト
	ID3D11PixelShader*		pixelShader;	//ピクセルシェーダオブジェクト
	ID3D11GeometryShader*	geometryShader;	//ジオメトリシェーダオブジェクト
	ID3D11BlendState*		blendState;		//ブレンドステートオブジェクト
	ID3D11RasterizerState*	rasterizerState;//ラスタライザステートオブジェクト
	ID3D11DepthStencilState*	depthStencilState;	//深度・ステンシルステートオブジェクト

private:
	UINT			compileOption;			//コンパイルオプション
};