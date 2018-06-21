#pragma once
#include "../../src/Device/DXDevice/DXDevice.h"


//----------------------------------------------------------------------------------
//!@class		VertexShader
//!@brief	頂点シェーダを扱います
//----------------------------------------------------------------------------------
class VertexShader
{
public:
	//!@brief	コンストラクタ
	VertexShader();
	//!@brief	デストラクタ
	~VertexShader();

	//!@brief		作成
	//!@param[in]	fileName			ファイル名
	//!@param[in]	inputElementDesc	インプットレイアウト情報
	//!@param[in]	inputElementDescNum	インプットレイアウト情報の数
	bool	Create(const std::string& fileName, D3D11_INPUT_ELEMENT_DESC* inputElementDesc, int elementNum);

	//!@brief		設定
	void	Set();

private:
	ID3D11VertexShader*		vertexShader;	//頂点シェーダ
	ID3D11InputLayout*		inputLayout;	//インプットレイアウト
};