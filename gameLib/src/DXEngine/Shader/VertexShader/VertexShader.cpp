#include "VertexShader.h"
#include "../../src/Utility/Utility.hpp"
#include "../../src/Engine/Engine.h"

//------------------------------------------------------------------
//!@brief	コンストラクタ
//------------------------------------------------------------------
VertexShader::VertexShader()
	: vertexShader(nullptr),inputLayout(nullptr)
{
	entryPointName = "main";
	versionName = "vs_5_0";
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
		entryPointName.c_str(), versionName.c_str(),
		D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR | D3D10_SHADER_SKIP_VALIDATION,
		0, nullptr,
		&vertexBlob,
		nullptr, nullptr);

	if (FAILED(result))
	{
		Utility::SafeRelease(vertexBlob);
		MessageBoxA(nullptr, "頂点シェーダでファイルが読み込み不可", "VertexShader::Create()", MB_OK);
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
		MessageBoxA(nullptr, "シェーダの作成に失敗しました", "CreateVertexShader()", MB_OK);
		return false;
	}

	//インプットレイアウトの作成
	result = Engine<DXDevice>::GetDevice().GetDevice3D().CreateInputLayout(
		inputElementDesc, elementNum,
		vertexBlob->GetBufferPointer(),
		vertexBlob->GetBufferSize(),
		&inputLayout
	);

	Utility::SafeRelease(vertexBlob);
	if (FAILED(result))
	{
		MessageBoxA(nullptr, "InputLayoutの作成に失敗", "CreateInputLayout()", MB_OK);
		return false;
	}
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

//----------------------------------------------------------------
//!@brief	エントリーポイント名の設定
//!@param[in]	entryPointName	エントリーポイント名
//----------------------------------------------------------------
void	VertexShader::SetEntryPointName(const std::string& entryPointName)
{
	this->entryPointName = entryPointName;
}