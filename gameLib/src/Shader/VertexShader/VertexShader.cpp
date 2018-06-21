#include "VertexShader.h"
#include "../../src/Utility/Utility.hpp"
#include "../../src/Engine/Engine.h"

//------------------------------------------------------------------
//!@brief	コンストラクタ
//------------------------------------------------------------------
VertexShader::VertexShader()
	: vertexShader(nullptr),inputLayout(nullptr)
{

}

//-----------------------------------------------------------------
//!@brief	デストラクタ
//-----------------------------------------------------------------
VertexShader::~VertexShader()
{
	Utility::SafeRelease(inputLayout);
	Utility::SafeRelease(vertexShader);
}


//------------------------------------------------------------------
//!@brief		作成
//!@param[in]	fileName		ファイル名
//!@param[in]	inputElementDesc	インプットレイアウト情報
//!@param[in]	inputElementDescNum	インプットレイアウト情報の数
//------------------------------------------------------------------
bool	VertexShader::Create(const std::string& fileName, D3D11_INPUT_ELEMENT_DESC* inputElementDesc, int elementNum)
{
	ID3DBlob*	vertexBlob = nullptr;

	//シェーダファイルの読み込み
	auto result = D3DX11CompileFromFileA(
		(fileName + ".hlsl").c_str(), nullptr, nullptr,
		"main", "vs_4_0",
		D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR | D3D10_SHADER_SKIP_VALIDATION,
		0, nullptr,
		&vertexBlob,
		nullptr, nullptr);

	if (FAILED(result))
	{
		Utility::SafeRelease(vertexBlob);
		return false;
	}

	//シェーダの作成
	result = Engine<DXDevice>::GetDevice().GetDevice3D().CreateVertexShader(
		vertexBlob->GetBufferPointer(),
		vertexBlob->GetBufferSize(),
		nullptr,
		&vertexShader
	);

	if (FAILED(result))
	{
		Utility::SafeRelease(vertexBlob);
		return false;
	}

	//インプットレイアウトの作成
	result = Engine<DXDevice>::GetDevice().GetDevice3D().CreateInputLayout(
		inputElementDesc, elementNum,
		vertexBlob->GetBufferPointer(),
		vertexBlob->GetBufferSize(),
		&inputLayout
	);



	if (FAILED(result))
	{
		Utility::SafeRelease(vertexBlob);
		return false;
	}

	Utility::SafeRelease(vertexBlob);
	return true;
}


//----------------------------------------------------------------
//!@brief		設定
//----------------------------------------------------------------
void	VertexShader::Set()
{
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetInputLayout(inputLayout);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().VSSetShader(vertexShader, nullptr,0);
}