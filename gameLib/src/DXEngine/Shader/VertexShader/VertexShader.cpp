#include "VertexShader.h"
#include "../../src/Utility/Utility.hpp"
#include "../../src/Engine/Engine.h"

//------------------------------------------------------------------
//!@brief	�R���X�g���N�^
//------------------------------------------------------------------
VertexShader::VertexShader()
	: vertexShader(nullptr),inputLayout(nullptr)
{
	entryPointName = "main";
	versionName = "vs_5_0";
}

//-----------------------------------------------------------------
//!@brief	�f�X�g���N�^
//-----------------------------------------------------------------
VertexShader::~VertexShader()
{
	Utility::SafeRelease(inputLayout);
	Utility::SafeRelease(vertexShader);
}


//------------------------------------------------------------------
//!@brief		�쐬
//!@param[in]	fileName		�t�@�C����
//!@param[in]	inputElementDesc	�C���v�b�g���C�A�E�g���
//!@param[in]	inputElementDescNum	�C���v�b�g���C�A�E�g���̐�
//------------------------------------------------------------------
bool	VertexShader::Create(const std::string& fileName, D3D11_INPUT_ELEMENT_DESC* inputElementDesc, int elementNum)
{
	ID3DBlob*	vertexBlob = nullptr;

	//�V�F�[�_�t�@�C���̓ǂݍ���
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
		MessageBoxA(nullptr, "���_�V�F�[�_�Ńt�@�C�����ǂݍ��ݕs��", "VertexShader::Create()", MB_OK);
		return false;
	}

	//�V�F�[�_�̍쐬
	result = Engine<DXDevice>::GetDevice().GetDevice3D().CreateVertexShader(
		vertexBlob->GetBufferPointer(),
		vertexBlob->GetBufferSize(),
		nullptr,
		&vertexShader
	);

	if (FAILED(result))
	{
		Utility::SafeRelease(vertexBlob);
		MessageBoxA(nullptr, "�V�F�[�_�̍쐬�Ɏ��s���܂���", "CreateVertexShader()", MB_OK);
		return false;
	}

	//�C���v�b�g���C�A�E�g�̍쐬
	result = Engine<DXDevice>::GetDevice().GetDevice3D().CreateInputLayout(
		inputElementDesc, elementNum,
		vertexBlob->GetBufferPointer(),
		vertexBlob->GetBufferSize(),
		&inputLayout
	);

	Utility::SafeRelease(vertexBlob);
	if (FAILED(result))
	{
		MessageBoxA(nullptr, "InputLayout�̍쐬�Ɏ��s", "CreateInputLayout()", MB_OK);
		return false;
	}
	return true;
}


//----------------------------------------------------------------
//!@brief		�ݒ�
//----------------------------------------------------------------
void	VertexShader::Set()
{
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetInputLayout(inputLayout);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().VSSetShader(vertexShader, nullptr,0);
}

//----------------------------------------------------------------
//!@brief	�G���g���[�|�C���g���̐ݒ�
//!@param[in]	entryPointName	�G���g���[�|�C���g��
//----------------------------------------------------------------
void	VertexShader::SetEntryPointName(const std::string& entryPointName)
{
	this->entryPointName = entryPointName;
}