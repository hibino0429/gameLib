#include "Material.h"

#include <fstream>
#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")
#include "../../src/Utility/Utility.hpp"
#include "../../src/Engine/Engine.h"


//-----------------------------------------------------------------------------
//!@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
Material::Material()
	: vertexShader(new VertexShader())
	, pixelShader(new PixelShader())
{

}

//-----------------------------------------------------------------------------
//!@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
Material::~Material()
{
	Utility::SafeDelete(vertexShader);
	Utility::SafeDelete(pixelShader);
}

//-----------------------------------------------------------------------------
//!@brief	�V�F�[�_�[�t�@�C����ǂݍ���
//!@param[in]	filePath	�t�@�C���p�X
//-----------------------------------------------------------------------------
void	Material::Load(const std::string& filePath)
{
	//�t�@�C���ǂݍ���
	std::ifstream sourceFile(filePath.c_str());
	std::istreambuf_iterator<char> iterator(sourceFile);
	std::istreambuf_iterator<char> last;
	std::string source(iterator, last);
	sourceFile.close();
	//�}�e���A��(�V�F�[�_)�̍쐬
	Create(source);
}

//-----------------------------------------------------------------------------
//!@brief	�}�e���A���̐���
//!@param[in]	shaderSource	�V�F�[�_�[�̃\�[�X
//-----------------------------------------------------------------------------
void	Material::Create(const std::string& shaderSource)
{
	std::vector<D3D11_INPUT_ELEMENT_DESC>	inputElementDesc;

	inputElementDesc.push_back({
		"POSITION",
		0,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		0,
		0,
		D3D11_INPUT_PER_VERTEX_DATA,
		0 });
	inputElementDesc.push_back({
		"NORMAL",
		0,
		DXGI_FORMAT_R32G32B32_FLOAT,
		0,
		12,
		D3D11_INPUT_PER_VERTEX_DATA,
		0 });
	inputElementDesc.push_back({
		"TEXCOORD",
		0,
		DXGI_FORMAT_R32G32_FLOAT,
		0,
		24,
		D3D11_INPUT_PER_VERTEX_DATA,
		0 });
	inputElementDesc.push_back({
		"BLENDINDICES",
		0,
		DXGI_FORMAT_R32G32B32A32_UINT,
		0,
		32,
		D3D11_INPUT_PER_VERTEX_DATA,
		0 });
	inputElementDesc.push_back({
		"BLENDINDICES",
		1,
		DXGI_FORMAT_R32G32B32A32_UINT,
		0,
		48,
		D3D11_INPUT_PER_VERTEX_DATA,
		0 });
	inputElementDesc.push_back({
		"BLENDWEIGHT",
		0,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		0,
		64,
		D3D11_INPUT_PER_VERTEX_DATA,
		0 });
	inputElementDesc.push_back({
		"BLENDWEIGHT",
		1,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		0,
		80,
		D3D11_INPUT_PER_VERTEX_DATA,
		0 });

	if (!vertexShader->Create("./data/shaderData/testShader", inputElementDesc.data(), inputElementDesc.size()))
	{
		MessageBoxA(nullptr, "���s", "���_�V�F�[�_", MB_OK);
	}
	if (!pixelShader->Create("./data/shaderData/testShader"))
	{
		MessageBoxA(nullptr, "���s", "�s�N�Z���V�F�[�_", MB_OK);
	}

}

//-----------------------------------------------------------------------------
//!@brief	�V�F�[�_�[�Ŏg�p����R���X�^���g�o�b�t�@�̐ݒ�
//!@param[in]	slot	�ݒ肷��ԍ�
//!@param[in]	constantBuf	�R���X�^���g�o�b�t�@
//!@param[in]	size	�o�b�t�@�̑傫��
//-----------------------------------------------------------------------------
void	Material::SetConstantBuffer(const int slot, void* constantBuf, size_t size)
{
	constantBuffer[slot].ptr = constantBuf;
	if (constantBuffer[slot].buffer != nullptr)
	{
		constantBuffer[slot].buffer->Release();
	}
	D3D11_BUFFER_DESC	constantDesc;
	SecureZeroMemory(&constantDesc, sizeof(constantDesc));
	constantDesc.ByteWidth = size;
	constantDesc.Usage = D3D11_USAGE_DEFAULT;
	constantDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	auto result = Engine<DXDevice>::GetDevice().GetDevice3D().CreateBuffer(
		&constantDesc,
		nullptr,
		&constantBuffer[slot].buffer
	);
	if (FAILED(result))
	{
		//�G���[
	}
}

//-----------------------------------------------------------------------------
//!@brief	�V�F�[�_�[�Ŏg�p����e�N�X�`���̐ݒ�
//!@param[in]	slot	�ݒ肷��ԍ�
//!@param[in]	texture	�e�N�X�`��
//-----------------------------------------------------------------------------
void	Material::SetTexture(const int slot, Texture* texture)
{
	textures[slot] = texture;
}

//-----------------------------------------------------------------------------
//!@brief	�V�F�[�_�[���O���t�B�b�N�X�ɃA�^�b�`
//-----------------------------------------------------------------------------
void	Material::Attach()
{
	vertexShader->Set();
	pixelShader->Set();
	
	for (int i = 0; i < 10; ++i)
	{
		if (constantBuffer[i].ptr != nullptr)
		{
			Engine<DXDevice>::GetDevice().GetDeviceContext3D().UpdateSubresource(constantBuffer[i].buffer, 0, nullptr, constantBuffer[i].ptr, 0,0);
			Engine<DXDevice>::GetDevice().GetDeviceContext3D().VSSetConstantBuffers(i, 1, &constantBuffer[i].buffer);
			Engine<DXDevice>::GetDevice().GetDeviceContext3D().HSSetConstantBuffers(i, 1, &constantBuffer[i].buffer);
			Engine<DXDevice>::GetDevice().GetDeviceContext3D().DSSetConstantBuffers(i, 1, &constantBuffer[i].buffer);
			Engine<DXDevice>::GetDevice().GetDeviceContext3D().GSSetConstantBuffers(i, 1, &constantBuffer[i].buffer);
			Engine<DXDevice>::GetDevice().GetDeviceContext3D().PSSetConstantBuffers(i, 1, &constantBuffer[i].buffer);
		}
	}
	for (int i = 0; i < 10; ++i)
	{
		if (textures[i] != nullptr)
		{
			textures[i]->Attach(i);
		}
	}
}