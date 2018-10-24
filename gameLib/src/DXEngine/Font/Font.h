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
//!@brief	DirectX Tool Kit�𗘗p�����t�H���g
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

		//�e�N�X�`�����̎擾
		D3D11_TEXTURE2D_DESC	texDesc;
		texture2D->GetDesc(&texDesc);

		//�V�F�[�_���\�[�X�r���[�̍쐬
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		memset(&srvDesc, 0, sizeof(srvDesc));
		srvDesc.Format = texDesc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = texDesc.MipLevels;

		result = Engine<DXDevice>::GetDevice().GetDevice3D().CreateShaderResourceView(texture2D, &srvDesc, &resourceView);

		//�T���v���̍쐬
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

		//�e�N�X�`�������擾
		D3D11_TEXTURE2D_DESC	texDesc;
		tex2D->GetDesc(&texDesc);

		//�V�F�[�_���\�[�X�r���[���쐬����
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		memset(&srvDesc, 0, sizeof(srvDesc));
		srvDesc.Format = texDesc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = texDesc.MipLevels;

		auto result = Engine<DXDevice>::GetDevice().GetDevice3D().CreateShaderResourceView(tex2D, &srvDesc, &resourceView);

		//�T���v���̍쐬
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
		
		//�f�o�C�X�R���e�L�X�g�擾
		HDC hdc = GetDC(nullptr);
		HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

		//�����R�[�h�̎擾
		UINT code = 0;
#if _UNICODE
		//code = (UINT)*c;
#else
		//�}���`�o�C�g�����̏ꍇ
		//1�o�C�g�����̃R�[�h��1�o�C�g�ڂ�UINT�ϊ�
		//2�o�C�g�����̃R�[�h��[�擱�R�[�h]*256 + [�����R�[�h]
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

		//�f�o�C�X�R���e�L�X�g�ƃt�H���g�n���h���̉��
		SelectObject(hdc, oldFont);
		DeleteObject(hFont);
		ReleaseDC(nullptr, hdc);

	}
	~FontTTF()
	{
		RemoveFontResourceExA(fontName.c_str(), FR_PRIVATE, &design);
	}

	//!@brief	�e�N�X�`���̍쐬
	void	CreateTexture(const GLYPHMETRICS& gm,const TEXTMETRIC& tm,BYTE* ptr)
	{
		// �e�N�X�`���쐬
		D3D11_TEXTURE2D_DESC desc;
		memset(&desc, 0, sizeof(desc));
		desc.Width = gm.gmCellIncX;
		desc.Height = tm.tmHeight;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// RGBA(255,255,255,255)�^�C�v
		desc.SampleDesc.Count = 1;
		desc.Usage = D3D11_USAGE_DYNAMIC;			// ���I�i�������݂��邽�߂̕K�{�����j
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	// �V�F�[�_���\�[�X�Ƃ��Ďg��
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// CPU����A�N�Z�X���ď�������OK

		ID3D11Texture2D* tex2D;					///< 2�c�e�N�X�`��
		auto result = Engine<DXDevice>::GetDevice().GetDevice3D().CreateTexture2D(&desc, 0, &tex2D);

		D3D11_MAPPED_SUBRESOURCE hMappedResource;
		result = Engine<DXDevice>::GetDevice().GetDeviceContext3D().Map(
			tex2D,
			0,
			D3D11_MAP_WRITE_DISCARD,
			0,
			&hMappedResource);
		
		// �����ŏ�������
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

