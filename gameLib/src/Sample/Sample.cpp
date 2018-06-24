#include "Sample.h"


Sample::Sample()
{
	Vertex vertexData[] {
		{ { -0.5f,  0.5f, 0.5f },{ 1.0f, 0.0f, 0.0f, 1.0f } },
		{ { 0.5f, -0.5f, 0.5f },{ 0.0f, 1.0f, 0.0f, 1.0f } },
		{ { -0.5f, -0.5f, 0.5f },{ 0.0f, 0.0f, 1.0f, 1.0f } }
	};

	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(Vertex) * 3;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA	subResourceData;
	memset(&subResourceData, 0, sizeof(subResourceData));
	subResourceData.pSysMem = vertexData;
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	vertexBuffer = nullptr;
	auto hr = Engine<DXDevice>::GetDevice().GetDevice3D().CreateBuffer(&bufferDesc, &subResourceData, &vertexBuffer);

	if (FAILED(hr)) { return; }

	//ì¸óÕçÄñ⁄
	D3D11_INPUT_ELEMENT_DESC inputLayout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	

	if (!vertexShader.Create("./data/shaderData/VertexShader", inputLayout, 2))
	{
		MessageBoxA(nullptr, "é∏îs", "Ç±Ç±Vertex", MB_OK);
	}

	if (!pixelShader.Create("./data/shaderData/PixelShader"))
	{
		MessageBoxA(nullptr, "é∏îs", "Ç±Ç±Pixel", MB_OK);
	}


}

Sample::~Sample()
{

}


void	Sample::UpDate()
{
	stride = sizeof(Vertex);
	offset = 0;

	vertexShader.Set();
	pixelShader.Set();
}

void	Sample::Render()
{
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	Engine<DXDevice>::GetDevice().GetDeviceContext3D().Draw(4, 0);
}