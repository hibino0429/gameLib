#include "Texture.h"
#include "../../src/Utility/Utility.hpp"
#include "../../src/Engine/Engine.h"




//!@brief	コンストラクタ
//!@param[in]	filePath	ファイルパス
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
//!@brief		レンダーテクスチャの取得[const]
//!@return		レンダーテクスチャ
//----------------------------------------------------------------------
ID3D11Texture2D*	Texture::Get() const
{
	return texture2D;
}

//-----------------------------------------------------------------------
//!@brief		テクスチャのアタッチ
//!@param[in]	slot	テクスチャをどこのスロットにセットするか指定
//-----------------------------------------------------------------------
void	Texture::Attach(const int slot)
{
	if (texture2D == nullptr) { return; }

	Engine<DXDevice>::GetDevice().GetDeviceContext3D().PSSetShaderResources(slot, 1, &texResourceView);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().PSSetSamplers(slot, 1, &textureSampler);
}

//----------------------------------------------------------------------
//!@brief		テクスチャのサイズを取得
//!@return		textureSize	テクスチャのサイズ
//----------------------------------------------------------------------
DirectX::XMINT2	Texture::GetSize() const
{
	return DirectX::XMINT2(static_cast<int>(size.x), static_cast<int>(size.y));
}

//----------------------------------------------------------------------
//!@brief		テクスチャのインターフェイスの取得
//!@return		ID3D11Texture2D&	テクスチャのインターフェイス
//----------------------------------------------------------------------
ID3D11Texture2D&	Texture::GetInterface()
{
	return *texture2D;
}


//---------------------------------------------------------------------------
//!@brief	画像ファイルからシェーダ・リソース・ビューの作成
//---------------------------------------------------------------------------
bool	Texture::CreateShaderResourceView()
{
	HRESULT hr = S_OK;
	D3DX11CreateShaderResourceViewFromFile(
		&Engine<DXDevice>::GetDevice().GetDevice3D(), L"./data/image/texture.png", nullptr, nullptr, &texResourceView, &hr);

	if (FAILED(hr))
	{
		//テクスチャの生成に失敗しました
		return false;
	}
	return true;
}

//----------------------------------------------------------------------
//!@brief	サンプラーの作成
//!@return	成功ならtrue
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
		//失敗しました
		MessageBoxA(nullptr, "サンプラーの作成に失敗", "Texture::CreateSampler()", MB_OK);
		return false;
	}
	return true;
}



//!@brief	読み込み
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
		MessageBoxA(nullptr, "デコーダの生成に失敗", "CreateDecoderFromFile()", MB_OK);
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
		MessageBoxA(nullptr, "テクスチャの形式取得に失敗", "PixelFormat()", MB_OK);
	}

	std::unique_ptr<BYTE[]>	buffer(new BYTE[width * height * 4]);

	if (pixelFormat != GUID_WICPixelFormat32bppRGBA)
	{
		//Direct2Dはビットマップしか描画できないため変換を行う
		IWICFormatConverter*	formatConverter = nullptr;
		hr = Engine<DXDevice>::GetDevice().GetTextureFactory().CreateFormatConverter(&formatConverter);
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "コンバーターの作成に失敗", "CreateConverter()", MB_OK);
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
			MessageBoxA(nullptr, "テクスチャのコンバートに失敗", "Initialize()", MB_OK);
		}

		hr = formatConverter->CopyPixels(0, width * 4, width * height * 4, buffer.get());
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "テクスチャの情報の取得に失敗", "CopyPixels()", MB_OK);
		}
		Utility::SafeRelease(formatConverter);
	}
	else
	{
		hr = frame->CopyPixels(0, width * 4, width * height * 4, buffer.get());
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "テクスチャの情報の取得に失敗", "CopyPixels()", MB_OK);
		}
	}

	SetParam(buffer.get(), width, height);

	Utility::SafeRelease(decoder);
	Utility::SafeRelease(frame);

	return true;
}
//!@brief	設定
void	Texture::SetParam(const BYTE* const buffer,int width,int height)
{
	D3D11_TEXTURE2D_DESC	textureDesc;
	SecureZeroMemory(&textureDesc, sizeof(textureDesc));
	textureDesc.Width				= width;
	textureDesc.Height				= height;
	textureDesc.MipLevels			= 1;
	textureDesc.ArraySize			= 1;
	textureDesc.Format				= DXGI_FORMAT_R8G8B8A8_UNORM;	//フォーマットがBlue,Green,Redの順でないと色が逆さになり、いろがおかしくなる
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

//!@brief	テクスチャを送る(シェーダ側へ)
void	Texture::Send()
{
	Attach(0);	//デフォルト
}

//!@brief	シェーダリソースビュー(texture用)の設定
void	Texture::SetShaderResourceView()
{
	D3D11_SHADER_RESOURCE_VIEW_DESC	shaderResViewDesc;
	SecureZeroMemory(&shaderResViewDesc, sizeof(shaderResViewDesc));
	shaderResViewDesc.Format				= DXGI_FORMAT_R8G8B8A8_UNORM;
	shaderResViewDesc.ViewDimension			= D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResViewDesc.Texture2D.MipLevels	= 1;
	Engine<DXDevice>::GetDevice().GetDevice3D().CreateShaderResourceView(texture2D, &shaderResViewDesc, &texResourceView);
}
//!@brief	描画
void	Texture::Render()
{
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().PSSetShaderResources(0, 1, &texResourceView);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().PSSetSamplers(0, 1, &textureSampler);
}