#include "PixelShader.h"
#include "../../src/Utility/Utility.hpp"
#include "../../src/Engine/Engine.h"

//----------------------------------------------------------------
//!@brief	�R���X�g���N�^
//----------------------------------------------------------------
PixelShader::PixelShader()
	: pixelShader(nullptr)
{

}

//-----------------------------------------------------------------
//!@brief	�f�X�g���N�^
//-----------------------------------------------------------------
PixelShader::~PixelShader()
{
	Utility::SafeRelease(pixelShader);
}

//-----------------------------------------------------------------
//!@brief		�쐬
//!@param[in]	fileName	�t�@�C����
//!@return		���� true ���s false
//-----------------------------------------------------------------
bool	PixelShader::Create(const std::string& fileName)
{
	ID3DBlob*	pixelBlob = nullptr;

	//�V�F�[�_�t�@�C���̓ǂݍ���
	auto result = D3DX11CompileFromFileA(
		(fileName + ".hlsl").c_str(), nullptr, nullptr,
		"PS_main", "ps_5_0",
		D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR | D3D10_SHADER_SKIP_VALIDATION,
		0, nullptr,
		&pixelBlob, nullptr, nullptr);
		
	if (FAILED(result))
	{
		Utility::SafeRelease(pixelBlob);
		MessageBoxA(nullptr, "�V�F�[�_�t�@�C���̓ǂݍ��݂Ɏ��s", "Pixel::Create()", MB_OK);
		return false;
	}

	//�V�F�[�_�̍쐬
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
//!@brief		�ݒ�
//------------------------------------------------------------------
void	PixelShader::Set()
{
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().PSSetShader(pixelShader, nullptr, 0);
}