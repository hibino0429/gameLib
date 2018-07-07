#pragma once
#include "../../src/Engine/Engine.h"
#include "../../src/DXEngine/DXDevice/DXDevice.h"
#include "../../src/Engine/Device/Device.h"
#include <string>


//----------------------------------------------------------------------------------------
//�T�v: DirectX�̃G���W�����g�p����
//----------------------------------------------------------------------------------------
class DXEngine
{
private:
	//!@brief	�R���X�g���N�^
	DXEngine();
	//!@brief	�f�X�g���N�^
	~DXEngine();

public:
	static ID3D11Device&				GetDevice3D();
	static ID3D11DeviceContext&			GetDeviceContext3D();
	static ID2D1Device&				GetDevice2D();
	static ID2D1DeviceContext&		GetDeviceContext2D();
	static IDXGISwapChain&				GetSwapChain();
	static IWICImagingFactory&		GetTextureFactory();
	static IDWriteFactory&			GetTextFactory();
	static ID3D11RenderTargetView*		GetRenderTargetView();
	static ID3D11Texture2D*				GetTexture2D();
	static ID3D11DepthStencilView*		GetDepthStencilView();

	//!@brief	�o�^����
	static void			RegistDevice(DXDevice* device);
	//!@brief	�擾����
	static DXDevice*	GetDevice();

	
private:
	static DXDevice*		device;		//�f�o�C�X
	static Device*			dev;
};
