#include "Texture.h"
#include "../../src/Utility/Utility.hpp"
#include "../../src/Engine/Engine.h"


//!@brief �R���X�g���N�^
Texture::Texture()
	: texture2D(nullptr)
	, texResourceView(nullptr)
	, textureSampler(nullptr)
{
	size = Math::Vector2(1, 1);
}

//!@brief	�R���X�g���N�^
//!@param[in]	filePath	�t�@�C���p�X
Texture::Texture(const std::string& filePath)
	: texture2D(nullptr)
	, texResourceView(nullptr)
	, textureSampler(nullptr)
{
	Load(filePath);
	size = Math::Vector2(1, 1);
}
//!@brief	�R���X�g���N�^
//!@param[in]	buffer	�o�b�t�@
//!@param[in]	width	�e�N�X�`���̕�
//!@param[in]	height	�e�N�X�`���̕�
Texture::Texture(const BYTE* const buffer, int width, int height)
{
	size.x = static_cast<float>(width);
	size.y = static_cast<float>(height);

	texture2D->Release();
	D3D11_TEXTURE2D_DESC textureDesc = {};
	textureDesc.Width = width;
	textureDesc.Height = height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA textureSubresourceData = {};
	textureSubresourceData.pSysMem = buffer;
	textureSubresourceData.SysMemPitch = width * 4;
	textureSubresourceData.SysMemSlicePitch = width * height * 4;
	Engine<DXDevice>::GetDevice().GetDevice3D().CreateTexture2D(&textureDesc, &textureSubresourceData, &texture2D);

	texResourceView->Release();
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = {};
	shaderResourceViewDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;
	Engine<DXDevice>::GetDevice().GetDevice3D().CreateShaderResourceView(texture2D, &shaderResourceViewDesc, &texResourceView);

	textureSampler->Release();
	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0.0f;
	samplerDesc.BorderColor[1] = 0.0f;
	samplerDesc.BorderColor[2] = 0.0f;
	samplerDesc.BorderColor[3] = 0.0f;
	samplerDesc.MinLOD = 0.0f;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	Engine<DXDevice>::GetDevice().GetDevice3D().CreateSamplerState(&samplerDesc, &textureSampler);
}

//!@brief �f�X�g���N�^
Texture::~Texture()
{
	Utility::SafeRelease(texResourceView);
	Utility::SafeRelease(textureSampler);
	Utility::SafeRelease(texture2D);
}


//------------------------------------------------------------------------
//!@brief	�e�N�X�`���̃��[�h
//!@param[in]	filePath	�t�@�C���p�X
//!@return	�����Ȃ� true ���s�Ȃ� false
//------------------------------------------------------------------------
bool	Texture::Load(const std::string& filePath)
{
	HRESULT hr;
	D3DX11CreateShaderResourceViewFromFile(
		&Engine<DXDevice>::GetDevice().GetDevice3D(), L"./data/image/texture.png", nullptr, nullptr, &texResourceView, &hr);

	if (FAILED(hr))
	{
		//�e�N�X�`���̐����Ɏ��s���܂���
		MessageBoxA(nullptr, "�e�N�X�`���̐����Ɏ��s", "Load", MB_OK);
		return false;
	}
	const wchar_t* const path = L"./data/image/texture.png";

	IWICBitmapDecoder*	decoder = nullptr;
	Engine<DXDevice>::GetDevice().GetTextureFactory().CreateDecoderFromFilename(
		path,
		0, GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&decoder
	);

	IWICBitmapFrameDecode*	frame = nullptr;
	decoder->GetFrame(0, &frame);
	UINT width, height;
	frame->GetSize(&width, &height);

	WICPixelFormatGUID	pixelFormat;
	hr = frame->GetPixelFormat(&pixelFormat);

	if (FAILED(hr))
	{
		return false;
	}
	std::unique_ptr<BYTE[]> buffer(new BYTE[width * height * 4]);

	if (pixelFormat != GUID_WICPixelFormat32bppBGRA)
	{
		IWICFormatConverter*	formatConverter = nullptr;
		Engine<DXDevice>::GetDevice().GetTextureFactory().CreateFormatConverter(&formatConverter);
		formatConverter->Initialize(frame, GUID_WICPixelFormat32bppBGRA, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom);
		formatConverter->CopyPixels(0, width * 4, width * height * 4, buffer.get());

		Utility::SafeRelease(formatConverter);
	}
	else
	{
		frame->CopyPixels(0, width * 4, width * height * 4, buffer.get());
	}

	Create(buffer.get(), width, height);

	Utility::SafeRelease(frame);
	return true;
}

//------------------------------------------------------------------------
//!@brief		�쐬
//!@return		���� true ���s false
//------------------------------------------------------------------------
bool	Texture::Create()
{
	//�X���b�v�`�F�C���ɗp�ӂ��ꂽ2D�e�N�X�`���̎擾
	auto result = Engine<DXDevice>::GetDevice().GetSwapChain().GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&texture2D);
	if (FAILED(result))
	{
		return false;
	}
	return true;
}

//----------------------------------------------------------------------
//!@brief		�쐬
//!@param[in]	buffer	Byte�o�b�t�@
//!@param[in]	width	��
//!@param[in]	height	����
//----------------------------------------------------------------------
void	Texture::Create(const BYTE* const buffer, int width, int height)
{
	size = Math::Vector2(static_cast<float>(width), static_cast<float>(height));

	if (texture2D != nullptr)
	{
		texture2D->Release();
	}

	D3D11_TEXTURE2D_DESC textureDesc = {};
	textureDesc.Width = width;
	textureDesc.Height = height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	
	D3D11_SUBRESOURCE_DATA textureSubresourceData = {};
	textureSubresourceData.pSysMem = buffer;
	textureSubresourceData.SysMemPitch = width * 4;
	textureSubresourceData.SysMemSlicePitch = width * height * 4;
	Engine<DXDevice>::GetDevice().GetDevice3D().CreateTexture2D(&textureDesc, &textureSubresourceData, &texture2D);
	
	if (texResourceView != nullptr)
	{
		texResourceView->Release();
	}
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = {};
	shaderResourceViewDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;
	Engine<DXDevice>::GetDevice().GetDevice3D().CreateShaderResourceView(texture2D, &shaderResourceViewDesc, &texResourceView);
	
	if (textureSampler != nullptr)
	{
		textureSampler->Release();
	}
	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0.0f;
	samplerDesc.BorderColor[1] = 0.0f;
	samplerDesc.BorderColor[2] = 0.0f;
	samplerDesc.BorderColor[3] = 0.0f;
	samplerDesc.MinLOD = 0.0f;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	Engine<DXDevice>::GetDevice().GetDevice3D().CreateSamplerState(&samplerDesc, &textureSampler);
}

//----------------------------------------------------------------------
//!@brief		�����_�[�e�N�X�`���̎擾[const]
//!@return		�����_�[�e�N�X�`��
//----------------------------------------------------------------------
ID3D11Texture2D*	Texture::Get() const
{
	return texture2D;
}

//-----------------------------------------------------------------------
//!@brief		�e�N�X�`���̃A�^�b�`
//!@param[in]	slot	�e�N�X�`�����ǂ��̃X���b�g�ɃZ�b�g���邩�w��
//-----------------------------------------------------------------------
void	Texture::Attach(const int slot)
{
	if (texture2D == nullptr) { return; }

	Engine<DXDevice>::GetDevice().GetDeviceContext3D().PSSetShaderResources(slot, 1, &texResourceView);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().PSSetSamplers(slot, 1, &textureSampler);
}

//----------------------------------------------------------------------
//!@brief		�e�N�X�`���̃T�C�Y���擾
//!@return		textureSize	�e�N�X�`���̃T�C�Y
//----------------------------------------------------------------------
DirectX::XMINT2	Texture::GetSize() const
{
	return DirectX::XMINT2(static_cast<int>(size.x), static_cast<int>(size.y));
}

//----------------------------------------------------------------------
//!@brief		�e�N�X�`���̃C���^�[�t�F�C�X�̎擾
//!@return		ID3D11Texture2D&	�e�N�X�`���̃C���^�[�t�F�C�X
//----------------------------------------------------------------------
ID3D11Texture2D&	Texture::GetInterface()
{
	return *texture2D;
}


//---------------------------------------------------------------------------
//!@brief	�摜�t�@�C������V�F�[�_�E���\�[�X�E�r���[�̍쐬
//---------------------------------------------------------------------------
bool	Texture::CreateShaderResourceView()
{
	HRESULT hr = S_OK;
	D3DX11CreateShaderResourceViewFromFile(
		&Engine<DXDevice>::GetDevice().GetDevice3D(), L"./data/image/texture.png", nullptr, nullptr, &texResourceView, &hr);

	if (FAILED(hr))
	{
		//�e�N�X�`���̐����Ɏ��s���܂���
		return false;
	}
	return true;
}

//----------------------------------------------------------------------
//!@brief	�T���v���[�̍쐬
//!@return	�����Ȃ�true
//----------------------------------------------------------------------
bool	Texture::CreateSampler()
{
	D3D11_SAMPLER_DESC		samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 2;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.BorderColor[0] = 0.0f;
	samplerDesc.BorderColor[1] = 0.0f;
	samplerDesc.BorderColor[2] = 0.0f;
	samplerDesc.BorderColor[3] = 0.0f;
	samplerDesc.MinLOD = -FLT_MAX;
	samplerDesc.MaxLOD = FLT_MAX;

	HRESULT hr;
	hr = Engine<DXDevice>::GetDevice().GetDevice3D().CreateSamplerState(&samplerDesc, &textureSampler);
	if (FAILED(hr))
	{
		//���s���܂���
		return false;
	}
	return true;
}