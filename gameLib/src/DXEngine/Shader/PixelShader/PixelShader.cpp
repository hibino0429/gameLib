#include "PixelShader.h"
#include "../../src/Utility/Utility.hpp"
#include "../../src/Engine/Engine.h"

//----------------------------------------------------------------
//!@brief	コンストラクタ
//----------------------------------------------------------------
PixelShader::PixelShader()
	: pixelShader(nullptr)
{
	entryPointName = "main";
	versionName = "ps_5_0";
}

//-----------------------------------------------------------------
//!@brief	デストラクタ
//-----------------------------------------------------------------
PixelShader::~PixelShader()
{
	Utility::SafeRelease(pixelShader);
}

//-----------------------------------------------------------------
//!@brief		作成
//!@param[in]	fileName	ファイル名
//!@return		成功 true 失敗 false
//-----------------------------------------------------------------
bool	PixelShader::Create(const std::string& fileName)
{
	ID3DBlob*	pixelBlob = nullptr;

	//シェーダファイルの読み込み
	auto result = D3DX11CompileFromFileA(
		(fileName + ".hlsl").c_str(), nullptr, nullptr,
		entryPointName.c_str(), versionName.c_str(),
		D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR | D3D10_SHADER_SKIP_VALIDATION,
		0, nullptr,
		&pixelBlob, nullptr, nullptr);
		
	if (FAILED(result))
	{
		Utility::SafeRelease(pixelBlob);
		MessageBoxA(nullptr, "シェーダファイルの読み込みに失敗", "Pixel::Create()", MB_OK);
		return false;
	}

	//シェーダの作成
	result = Engine<DXDevice>::GetDevice().GetDevice3D().CreatePixelShader(
		pixelBlob->GetBufferPointer(),
		pixelBlob->GetBufferSize(),
		nullptr,
		&pixelShader);

	Utility::SafeRelease(pixelBlob);

	if (FAILED(result))
	{
		return false;
	}
	return true;
}

//------------------------------------------------------------------
//!@brief		設定
//------------------------------------------------------------------
void	PixelShader::Set()
{
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().PSSetShader(pixelShader, nullptr, 0);
}

//------------------------------------------------------------------
//!@brief	エントリーポイント名の設定
//!@param[in]	entryPointName	エントリーポイント名
//------------------------------------------------------------------
void	PixelShader::SetEntryPointName(const std::string& entryPointName)
{
	this->entryPointName = entryPointName;
}