#pragma once
#pragma warning (disable : 4005)
#pragma warning (disable : 4305)

#include <d3d11.h>
#include <d3dx11.h>
#include <DxErr.h>
#include <dxgi.h>
#include <Windows.h>
#include <DXGI.h>
#include <d2d1_1.h>
#include <dwrite.h>
#include <wrl.h>
#include <wincodec.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11d.lib")
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dxerr.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dwrite.lib")
#pragma comment(lib,"Windowscodecs.lib")

#include "../../src/Device/Device.h"
#include <array>
#include "../../src/Screen/Screen.h"



//-------------------------------------------------------------
//!@class		DXDevice
//!@brief	DirectXのデバイスを扱う
//!@brief	一番初めでDirectXのデバイスの初期化を行う
//!@brief	そのあとで、Engineに作成したデータを渡す
//!@brief	DirectXの機能などを提供します
//-------------------------------------------------------------
class DXDevice : public Device
{
public:
	//!@brief コンストラクタ
	DXDevice(Screen* screen);
	//!@brief デストラクタ
	virtual ~DXDevice();
public:
	ID3D11Device&			GetDevice3D() const;
	ID3D11DeviceContext&	GetDeviceContext3D() const;
	ID2D1Device&			GetDevice2D() const;
	ID2D1DeviceContext&		GetDeviceContext2D() const;
	IDXGISwapChain&			GetSwapChain() const;
	IWICImagingFactory&		GetTextureFactory() const;
	IDWriteFactory&			GetTextFactory() const;
	ID3D11RenderTargetView*	GetRenderTargetView() const;
	ID3D11Texture2D*		GetTexture2D() const;
	ID3D11DepthStencilView*	GetDepthStencilView() const;
	
	//!@brief 生成
	bool	Create();
	//!@brief 更新
	void	Run();
	//!@brief 終了
	bool	CleanUp();
	//!@brief 消失
	bool	Remove();
	


private:
	bool	CreateDirect3D();
	bool	CreateBackBuffer();
	bool	CreateSwapChain();
	bool	CreateBlendState();
	bool	CreateDirect2D();
	void	SetViewPort(float width,float height);
	bool	ChangeScreenSize();
	bool	AcquireBackBuffer();

private:
	ID3D11Device*			device3D;
	ID3D11DeviceContext*	deviceContext3D;
	ID2D1Device*			device2D;
	ID2D1DeviceContext*		deviceContext2D;
	IDXGISwapChain*			swapChain;
	IWICImagingFactory*		textureFactory;
	Microsoft::WRL::ComPtr<IDWriteFactory>		textFactory;
	ID3D11RenderTargetView*	renderTargetView;
	ID3D11Texture2D*		texture2D;
	ID3D11DepthStencilView*	depthStencilView;
	Screen*					screen;
};

