#pragma once
#include <string>
#include <iostream>
#include <../Texture/Inc/SpriteBatch.h>
#include <../Texture/Inc/WICTextureLoader.h>
#include <../Texture/Inc/SpriteFont.h>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/DXEngine/DXEngine/DXEngine.h"
#include "../../src/Utility/Utility.hpp"
#include <Shlwapi.h>

#pragma comment(lib,"DirectXTK.lib")

//----------------------------------------------------------------------------
//!@class		Font
//!@brief	DirectX Tool Kitを利用したフォント
//!@brief	
//----------------------------------------------------------------------------
class Font
{
public:
	Font(const std::string& fontName)
	{
		spriteBatch = new DirectX::SpriteBatch(&Engine<DXDevice>::GetDevice().GetDeviceContext3D());
		std::wstring wstr = std::wstring(fontName.begin(), fontName.end());
		LPCWSTR sw = wstr.c_str();
		spriteFont = new DirectX::SpriteFont(&Engine<DXDevice>::GetDevice().GetDevice3D(), sw);
	}
	~Font()
	{

	}
public:
	void	Draw(const std::string& text,const Math::Vector2& pos)
	{
		std::wstring wstr = std::wstring(text.begin(), text.end());
		LPCWSTR sw = wstr.c_str();
		spriteFont->DrawString(spriteBatch, sw, pos);
	}
private:
	DirectX::SpriteBatch*	spriteBatch;
	DirectX::SpriteFont*	spriteFont;
};



class TextureData
{
public:
	void	Read(const std::string& filePath)
	{
		name = filePath;
		ID3D11Resource*	resource;

		auto result = D3DX11CreateTextureFromFileA(
			&Engine<DXDevice>::GetDevice().GetDevice3D(),
			name.c_str(),
			nullptr,
			nullptr,
			&resource,
			nullptr);

		texture2D = static_cast<ID3D11Texture2D*>(resource);

		//テクスチャ情報の取得
		D3D11_TEXTURE2D_DESC	texDesc;
		texture2D->GetDesc(&texDesc);

		//シェーダリソースビューの作成
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		memset(&srvDesc, 0, sizeof(srvDesc));
		srvDesc.Format = texDesc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = texDesc.MipLevels;

		result = Engine<DXDevice>::GetDevice().GetDevice3D().CreateShaderResourceView(texture2D, &srvDesc, &resourceView);

		//サンプラの作成
		D3D11_SAMPLER_DESC	samDesc;
		memset(&samDesc, 0, sizeof(samDesc));
		samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samDesc.AddressU = samDesc.AddressV = samDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samDesc.MaxAnisotropy = 1;
		samDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samDesc.MaxLOD = D3D11_FLOAT32_MAX;

		result = Engine<DXDevice>::GetDevice().GetDevice3D().CreateSamplerState(&samDesc, &samplerState);
	}

	void	SetData(const std::string& name, ID3D11Texture2D* tex2D)
	{
		this->texture2D = tex2D;

		//テクスチャ情報を取得
		D3D11_TEXTURE2D_DESC	texDesc;
		tex2D->GetDesc(&texDesc);

		//シェーダリソースビューを作成する
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		memset(&srvDesc, 0, sizeof(srvDesc));
		srvDesc.Format = texDesc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = texDesc.MipLevels;

		auto result = Engine<DXDevice>::GetDevice().GetDevice3D().CreateShaderResourceView(tex2D, &srvDesc, &resourceView);

		//サンプラの作成
		D3D11_SAMPLER_DESC sampDesc;
		memset(&sampDesc, 0, sizeof(sampDesc));
		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU = sampDesc.AddressV = sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.MaxAnisotropy = 1;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

		result = Engine<DXDevice>::GetDevice().GetDevice3D().CreateSamplerState(&sampDesc, &samplerState);
	}
	const std::string& GetName() const
	{
		return name;
	}
	ID3D11ShaderResourceView** GetResourceView()
	{
		return &resourceView;
	}
	ID3D11SamplerState**	GetSamplerState()
	{
		return &samplerState;
	}
	ID3D11Texture2D*	GetTexture()
	{
		return texture2D;
	}
private:
	std::string					name;
	ID3D11Texture2D*			texture2D;
	ID3D11ShaderResourceView*	resourceView;
	ID3D11SamplerState*			samplerState;
};




class FontTTF
{
public:
	FontTTF(const std::string& filePath)
	{
		fontName = filePath;
		AddFontResourceExA(filePath.c_str(), FR_PRIVATE, &design);

		int fontSize = 0;
		LOGFONTA lf = {
			fontSize,0,0,0,0,0,0,0,
			SHIFTJIS_CHARSET,
			OUT_TT_ONLY_PRECIS,
			CLIP_DEFAULT_PRECIS,
			PROOF_QUALITY,
			FIXED_PITCH | FF_MODERN,
			"Aria.spritFont"
		};
		HFONT hFont = CreateFontIndirectA(&lf);
		
		//デバイスコンテキスト取得
		HDC hdc = GetDC(nullptr);
		HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

		//文字コードの取得
		UINT code = 0;
#if _UNICODE
		//code = (UINT)*c;
#else
		//マルチバイト文字の場合
		//1バイト文字のコードは1バイト目のUINT変換
		//2バイト文字のコードは[先導コード]*256 + [文字コード]
		if (IsDBCLeadByte(*c))
		{
			code = (BYTE)c[0] << 8 | (BYTE)c[1];
		}
		else
		{
			code = c[0];
		}
#endif

		TEXTMETRIC	tm;
		GetTextMetrics(hdc, &tm);
		GLYPHMETRICS	gm;
		const MAT2 mat = { {0,1},{0,0},{0,0},{0,1} };
		DWORD size = GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &gm, 0, nullptr, &mat);
		BYTE* ptr = new BYTE[size];
		GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &gm, size, ptr, &mat);

		//デバイスコンテキストとフォントハンドルの解放
		SelectObject(hdc, oldFont);
		DeleteObject(hFont);
		ReleaseDC(nullptr, hdc);

	}
	~FontTTF()
	{
		RemoveFontResourceExA(fontName.c_str(), FR_PRIVATE, &design);
	}

	//!@brief	テクスチャの作成
	void	CreateTexture(const GLYPHMETRICS& gm,const TEXTMETRIC& tm,BYTE* ptr)
	{
		// テクスチャ作成
		D3D11_TEXTURE2D_DESC desc;
		memset(&desc, 0, sizeof(desc));
		desc.Width = gm.gmCellIncX;
		desc.Height = tm.tmHeight;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// RGBA(255,255,255,255)タイプ
		desc.SampleDesc.Count = 1;
		desc.Usage = D3D11_USAGE_DYNAMIC;			// 動的（書き込みするための必須条件）
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	// シェーダリソースとして使う
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// CPUからアクセスして書き込みOK

		ID3D11Texture2D* tex2D;					///< 2Ｄテクスチャ
		auto result = Engine<DXDevice>::GetDevice().GetDevice3D().CreateTexture2D(&desc, 0, &tex2D);

		D3D11_MAPPED_SUBRESOURCE hMappedResource;
		result = Engine<DXDevice>::GetDevice().GetDeviceContext3D().Map(
			tex2D,
			0,
			D3D11_MAP_WRITE_DISCARD,
			0,
			&hMappedResource);
		
		// ここで書き込む
		BYTE* pBits = (BYTE*)hMappedResource.pData;

		int offsetX = gm.gmptGlyphOrigin.x;
		int offsetY = tm.tmAscent - gm.gmptGlyphOrigin.y;
		int fontBitmapWidth = gm.gmBlackBoxX + (4 - (gm.gmBlackBoxX % 4)) % 4;
		int fontBitmapHeight = gm.gmBlackBoxY;
		int level = 17;
		
		int x, y;
		DWORD alpha, color;
		memset(pBits, 0, hMappedResource.RowPitch * tm.tmHeight);
		for (y = offsetY; y < offsetY + fontBitmapHeight; ++y)
		{
			for (x = offsetX; x < offsetX + fontBitmapWidth; ++x)
			{
				alpha = (255 * ptr[x - offsetX + fontBitmapWidth * (y - offsetY)]) / (level - 1);
				color = 0x00ffffff | alpha << 24;
				memset((BYTE*)pBits + hMappedResource.RowPitch * y + 4 * x, color, sizeof(DWORD));
			}
		}

		Engine<DXDevice>::GetDevice().GetDeviceContext3D().Unmap(tex2D, 0);

		textureData->SetData(fontName.c_str(), tex2D);

		delete[] ptr;
	}

private:
	DESIGNVECTOR	design;
	std::string		fontName;
	TextureData*	textureData;
};

