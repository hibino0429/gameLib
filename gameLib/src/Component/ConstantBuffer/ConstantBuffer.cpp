#include "ConstantBuffer.h"
#include "../../src/DXEngine/DXEngine/DXEngine.h"
#include "../../Utility/Utility.hpp"



ConstantBuffer::ConstantBuffer()
{
	Engine<DXDevice>::GetDevice().COMInitialize();

	D3D11_BUFFER_DESC	constantBufDesc;
	memset(&constantBufDesc, 0, sizeof(constantBufDesc));
	constantBufDesc.ByteWidth	= sizeof(CBuffer);
	constantBufDesc.BindFlags	= D3D11_BIND_CONSTANT_BUFFER;
	constantBufDesc.Usage		= D3D11_USAGE_DEFAULT;

	Engine<DXDevice>::GetDevice().GetDevice3D().CreateBuffer(&constantBufDesc, nullptr, &constantBuf.p);
}

ConstantBuffer::ConstantBuffer(const size_t & bufferSize)
{
	Engine<DXDevice>::GetDevice().COMInitialize();

	D3D11_BUFFER_DESC	constantBufDesc;
	memset(&constantBufDesc, 0, sizeof(constantBufDesc));
	constantBufDesc.ByteWidth = bufferSize;
	constantBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufDesc.Usage = D3D11_USAGE_DEFAULT;

	Engine<DXDevice>::GetDevice().GetDevice3D().CreateBuffer(&constantBufDesc, nullptr, &constantBuf.p);
}

ConstantBuffer::ConstantBuffer(const D3D11_BUFFER_DESC& cBufferDesc)
{
	Engine<DXDevice>::GetDevice().COMInitialize();
	Engine<DXDevice>::GetDevice().GetDevice3D().CreateBuffer(&cBufferDesc, nullptr, &constantBuf.p);
}

ConstantBuffer::~ConstantBuffer()
{

}

void ConstantBuffer::UpDate(void* constantBuffer)
{
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().UpdateSubresource(constantBuf.p, 0, nullptr, constantBuffer, 0, 0);
}

void ConstantBuffer::Render()
{
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().VSSetConstantBuffers(0, 1, &constantBuf.p);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().HSSetConstantBuffers(0, 1, &constantBuf.p);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().DSSetConstantBuffers(0, 1, &constantBuf.p);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().GSSetConstantBuffers(0, 1, &constantBuf.p);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().PSSetConstantBuffers(0, 1, &constantBuf.p);
}

