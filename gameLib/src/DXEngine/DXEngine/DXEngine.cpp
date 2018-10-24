#include "DXEngine.h"


DXDevice*	DXEngine::device = nullptr;

DXEngine::DXEngine()
{
	
}

DXEngine::~DXEngine()
{
	if (device != nullptr)
	{
		delete device;
		device = nullptr;
	}
}



//ŠT—v: “o˜^ˆ—
void	DXEngine::RegistDevice(DXDevice* device_)
{
	device = device_;
}
//ŠT—v: Žæ“¾ˆ—
DXDevice*	DXEngine::GetDevice()
{
	return device;
}


ID3D11Device&			DXEngine::GetDevice3D()
{
	return device->GetDevice3D();
}
ID3D11DeviceContext&		DXEngine::GetDeviceContext3D()
{
	return device->GetDeviceContext3D();
}

ID2D1Device&				DXEngine::GetDevice2D()
{
	return device->GetDevice2D();
}
ID2D1DeviceContext&		DXEngine::GetDeviceContext2D()
{
	return device->GetDeviceContext2D();
}
IDXGISwapChain&			DXEngine::GetSwapChain()
{
	return device->GetSwapChain();
}
IWICImagingFactory&		DXEngine::GetTextureFactory()
{
	return device->GetTextureFactory();
}
IDWriteFactory&			DXEngine::GetTextFactory()
{
	return device->GetTextFactory();
}
ID3D11RenderTargetView*	DXEngine::GetRenderTargetView()
{
	return device->GetRenderTargetView();
}
ID3D11Texture2D*		DXEngine::GetTexture2D()
{
	return device->GetTexture2D();
}
ID3D11DepthStencilView*	DXEngine::GetDepthStencilView()
{
	return device->GetDepthStencilView();
}

