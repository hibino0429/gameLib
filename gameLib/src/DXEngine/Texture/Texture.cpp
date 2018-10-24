#include "Texture.h"
#include "../../src/Utility/Utility.hpp"
#include "../../src/Engine/Engine.h"




//!@brief	�R���X�g���N�^
//!@param[in]	filePath	�t�@�C���p�X
Texture::Texture(const std::string& filePath)
	: texture2D(nullptr)
	, texResourceView(nullptr)
	, textureSampler(nullptr)
{
	this->LoadTex(filePath);
	this->Send();
	this->SetShaderResourceView();
}

Texture::~Texture()
{
	Utility::SafeRelease(texture2D);
	Utility::SafeRelease(texResourceView);
	Utility::SafeRelease(textureSampler);
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

	auto hr = Engine<DXDevice>::GetDevice().GetDevice3D().CreateSamplerState(&samplerDesc, &textureSampler);
	if (FAILED(hr))
	{
		//���s���܂���
		MessageBoxA(nullptr, "�T���v���[�̍쐬�Ɏ��s", "Texture::CreateSampler()", MB_OK);
		return false;
	}
	return true;
}



//!@brief	�ǂݍ���
bool	Texture::LoadTex(const std::string& filePath)
{
	IWICBitmapDecoder*	decoder = nullptr;
	std::wstring wstr = std::wstring(filePath.begin(), filePath.end());
	LPCWSTR sw = wstr.c_str();
	auto hr = Engine<DXDevice>::GetDevice().GetTextureFactory().CreateDecoderFromFilename(
		sw,
		0,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&decoder
	);
	if (FAILED(hr))
	{
		MessageBoxA(nullptr, "�f�R�[�_�̐����Ɏ��s", "CreateDecoderFromFile()", MB_OK);
	}

	IWICBitmapFrameDecode*	frame = nullptr;
	decoder->GetFrame(0, &frame);
	UINT width, height;
	frame->GetSize(&width, &height);
	size.x = static_cast<float>(width);
	size.y = static_cast<float>(height);

	WICPixelFormatGUID	pixelFormat;
	hr = frame->GetPixelFormat(&pixelFormat);
	if (FAILED(hr))
	{
		MessageBoxA(nullptr, "�e�N�X�`���̌`���擾�Ɏ��s", "PixelFormat()", MB_OK);
	}

	std::unique_ptr<BYTE[]>	buffer(new BYTE[width * height * 4]);

	if (pixelFormat != GUID_WICPixelFormat32bppRGBA)
	{
		//Direct2D�̓r�b�g�}�b�v�����`��ł��Ȃ����ߕϊ����s��
		IWICFormatConverter*	formatConverter = nullptr;
		hr = Engine<DXDevice>::GetDevice().GetTextureFactory().CreateFormatConverter(&formatConverter);
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "�R���o�[�^�[�̍쐬�Ɏ��s", "CreateConverter()", MB_OK);
		}
		hr = formatConverter->Initialize(
			frame,
			GUID_WICPixelFormat32bppRGBA,
			WICBitmapDitherTypeErrorDiffusion,
			0,
			0,
			WICBitmapPaletteTypeCustom
		);
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "�e�N�X�`���̃R���o�[�g�Ɏ��s", "Initialize()", MB_OK);
		}

		hr = formatConverter->CopyPixels(0, width * 4, width * height * 4, buffer.get());
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "�e�N�X�`���̏��̎擾�Ɏ��s", "CopyPixels()", MB_OK);
		}
		Utility::SafeRelease(formatConverter);
	}
	else
	{
		hr = frame->CopyPixels(0, width * 4, width * height * 4, buffer.get());
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "�e�N�X�`���̏��̎擾�Ɏ��s", "CopyPixels()", MB_OK);
		}
	}

	SetParam(buffer.get(), width, height);

	Utility::SafeRelease(decoder);
	Utility::SafeRelease(frame);

	return true;
}
//!@brief	�ݒ�
void	Texture::SetParam(const BYTE* const buffer,int width,int height)
{
	D3D11_TEXTURE2D_DESC	textureDesc;
	SecureZeroMemory(&textureDesc, sizeof(textureDesc));
	textureDesc.Width				= width;
	textureDesc.Height				= height;
	textureDesc.MipLevels			= 1;
	textureDesc.ArraySize			= 1;
	textureDesc.Format				= DXGI_FORMAT_R8G8B8A8_UNORM;	//�t�H�[�}�b�g��Blue,Green,Red�̏��łȂ��ƐF���t���ɂȂ�A���낪���������Ȃ�
	textureDesc.SampleDesc.Count	= 1;
	textureDesc.SampleDesc.Quality	= 0;
	textureDesc.Usage				= D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags			= D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	textureDesc.CPUAccessFlags		= 0;
	textureDesc.MiscFlags			= 0;

	D3D11_SUBRESOURCE_DATA	subResourceData;
	SecureZeroMemory(&subResourceData, sizeof(subResourceData));
	subResourceData.pSysMem				= buffer;
	subResourceData.SysMemPitch			= width * 4;
	subResourceData.SysMemSlicePitch	= width * height * 4;
	Engine<DXDevice>::GetDevice().GetDevice3D().CreateTexture2D(&textureDesc, &subResourceData, &texture2D);

	D3D11_SAMPLER_DESC	samplerDesc;
	SecureZeroMemory(&samplerDesc, sizeof(samplerDesc));
	samplerDesc.Filter			= D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU		= samplerDesc.AddressV = samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.BorderColor[0]	= 0.0f;
	samplerDesc.BorderColor[1]	= 0.0f;
	samplerDesc.BorderColor[2]	= 0.0f;
	samplerDesc.BorderColor[3]	= 0.0f;
	samplerDesc.MaxAnisotropy	= 1;
	samplerDesc.ComparisonFunc	= D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD			= 0.0f;
	samplerDesc.MaxLOD			= D3D11_FLOAT32_MAX;

	Engine<DXDevice>::GetDevice().GetDevice3D().CreateSamplerState(&samplerDesc, &textureSampler);
}

//!@brief	�e�N�X�`���𑗂�(�V�F�[�_����)
void	Texture::Send()
{
	Attach(0);	//�f�t�H���g
}

//!@brief	�V�F�[�_���\�[�X�r���[(texture�p)�̐ݒ�
void	Texture::SetShaderResourceView()
{
	D3D11_SHADER_RESOURCE_VIEW_DESC	shaderResViewDesc;
	SecureZeroMemory(&shaderResViewDesc, sizeof(shaderResViewDesc));
	shaderResViewDesc.Format				= DXGI_FORMAT_R8G8B8A8_UNORM;
	shaderResViewDesc.ViewDimension			= D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResViewDesc.Texture2D.MipLevels	= 1;
	Engine<DXDevice>::GetDevice().GetDevice3D().CreateShaderResourceView(texture2D, &shaderResViewDesc, &texResourceView);
}
//!@brief	�`��
void	Texture::Render()
{
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().PSSetShaderResources(0, 1, &texResourceView);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().PSSetSamplers(0, 1, &textureSampler);
}