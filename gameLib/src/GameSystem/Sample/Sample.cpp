#include "Sample.h"
#include "../../src/DXEngine/Camera/Camera.h"
#include "../../src/Utility/Utility.hpp"

Sample::Sample()
	: pos(Math::Vector3(0,0,0))
	, angle(Math::Vector3(0,0,0))
	, scale(Math::Vector3(1,1,1))
{
	vertexBuffer = nullptr;
	this->indexBuffer = nullptr;

	Vertex vertexData[] {
		{ { -0.5f,  0.5f, -0.5f },{ 1.0f, 0.0f, 0.0f, 1.0f } },
		{ { 0.5f,  0.5f, -0.5f },{ 1.0f, 0.0f, 0.0f, 1.0f }},
		{ { -0.5f, -0.5f, -0.5f },{ 1.0f, 0.0f, 0.0f, 1.0f }},
		{ { 0.5f, -0.5f, -0.5f },{ 1.0f, 0.0f, 0.0f, 1.0f } },

		{ { -0.5f,  0.5f,  0.5f },{ 0.0f, 1.0f, 1.0f, 1.0f } },
		{ { -0.5f, -0.5f,  0.5f },{ 0.0f, 1.0f, 1.0f, 1.0f } },
		{ { 0.5f,  0.5f,  0.5f },{ 0.0f, 1.0f, 1.0f, 1.0f } },
		{ { 0.5f, -0.5f,  0.5f },{ 0.0f, 1.0f, 1.0f, 1.0f } },

		{ { -0.5f,  0.5f,  0.5f },{ 1.0f, 1.0f, 0.0f, 1.0f } },
		{ { -0.5f,  0.5f, -0.5f },{ 1.0f, 1.0f, 0.0f, 1.0f } },
		{ { -0.5f, -0.5f,  0.5f },{ 1.0f, 1.0f, 0.0f, 1.0f } },
		{ { -0.5f, -0.5f, -0.5f },{ 1.0f, 1.0f, 0.0f, 1.0f } },

		{ { 0.5f,  0.5f,  0.5f },{ 0.0f, 0.0f, 1.0f, 1.0f } },
		{ { 0.5f, -0.5f,  0.5f },{ 0.0f, 0.0f, 1.0f, 1.0f } },
		{ { 0.5f,  0.5f, -0.5f },{ 0.0f, 0.0f, 1.0f, 1.0f } },
		{ { 0.5f, -0.5f, -0.5f },{ 0.0f, 0.0f, 1.0f, 1.0f } },

		{ { -0.5f,  0.5f,  0.5f },{ 1.0f, 0.0f, 1.0f, 1.0f } },
		{ { 0.5f,  0.5f,  0.5f },{ 1.0f, 0.0f, 1.0f, 1.0f } },
		{ { -0.5f,  0.5f, -0.5f },{ 1.0f, 0.0f, 1.0f, 1.0f } },
		{ { 0.5f,  0.5f, -0.5f },{ 1.0f, 0.0f, 1.0f, 1.0f } },

		{ { -0.5f, -0.5f,  0.5f },{ 0.0f, 1.0f, 0.0f, 1.0f } },
		{ { -0.5f, -0.5f, -0.5f },{ 0.0f, 1.0f, 0.0f, 1.0f } },
		{ { 0.5f, -0.5f,  0.5f },{ 0.0f, 1.0f, 0.0f, 1.0f } },
		{ { 0.5f, -0.5f, -0.5f },{ 0.0f, 1.0f, 0.0f, 1.0f } },
	};


	WORD	indexList[] = {
		0,  1,  2,     3,  2,  1,
		4,  5,  6,     7,  6,  5,
		8,  9, 10,    11, 10,  9,
		12, 13, 14,    15, 14, 13,
		16, 17, 18,    19, 18, 17,
		20, 21, 22,    23, 22, 21,
	};

	Vex	vexDatas[] =
	{
		{ { -0.5f,  0.5f, 0.5f },{ 0.0f, 0.0f } },
	{ { 0.5f, -0.5f, 0.5f },{ 1.0f, 0.0f } },
	{ { -0.5f, -0.5f, 0.5f },{ 1.0f, 1.0f } },
	{ { 0.5f,  0.5f, 0.5f },{ 0.0f, 1.0f } }
	};

	WORD	inList[] = {
		0,1,2,
		0,3,1
	};

	//indexバッファの作成
	D3D11_BUFFER_DESC	indexBufferDesc;
	indexBufferDesc.ByteWidth			= sizeof(WORD) * 6;
	indexBufferDesc.Usage				= D3D11_USAGE_DEFAULT;
	indexBufferDesc.BindFlags			= D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags		= 0;
	indexBufferDesc.MiscFlags			= 0;
	indexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA	indexSubData;
	indexSubData.pSysMem			= inList;
	indexSubData.SysMemPitch		= 0;
	indexSubData.SysMemSlicePitch	= 0;

	Engine<DXDevice>::GetDevice().GetDevice3D().CreateBuffer(&indexBufferDesc, &indexSubData, &indexBuffer);
	
	//頂点バッファの作成
	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(bufferDesc));
	bufferDesc.Usage				= D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth			= sizeof(Vertex) * 4;
	bufferDesc.BindFlags			= D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags		= 0;
	bufferDesc.MiscFlags			= 0;
	bufferDesc.StructureByteStride	= 0;

	D3D11_SUBRESOURCE_DATA	subResourceData;
	memset(&subResourceData, 0, sizeof(subResourceData));
	subResourceData.pSysMem				= vexDatas;
	subResourceData.SysMemPitch			= 0;
	subResourceData.SysMemSlicePitch	= 0;

	Engine<DXDevice>::GetDevice().GetDevice3D().CreateBuffer(&bufferDesc, &subResourceData, &vertexBuffer);
	
	//入力項目
	D3D11_INPUT_ELEMENT_DESC inLayout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	this->inputLayout = inLayout;

	//シェーダの作成
	vertexShader.Create("./data/shaderData/VertexShader", this->inputLayout, 2);
	pixelShader.Create("./data/shaderData/PixelShader");
	
	//定数バッファの作成
	D3D11_BUFFER_DESC	cbDesc;
	std::memset(&cbDesc, 0, sizeof(cbDesc));
	cbDesc.ByteWidth		= sizeof(ConstantBuf);
	cbDesc.Usage			= D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags		= D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags	= 0;
	cbDesc.MiscFlags		= 0;
	cbDesc.StructureByteStride = 0;

	Engine<DXDevice>::GetDevice().GetDevice3D().CreateBuffer(&cbDesc, nullptr, &constantBuffer);
}

Sample::~Sample()
{
	Utility::SafeRelease(vertexBuffer);
	Utility::SafeRelease(indexBuffer);
	Utility::SafeRelease(constantBuffer);
	
}


void	Sample::UpDate()
{
	DirectX::XMMATRIX worldMatrix = DirectX::XMMatrixTranslation(pos.x,pos.y, pos.z);
	
	//ビュー空間へ
	DirectX::XMVECTOR	eye		= DirectX::XMVectorSet(2.0f, 2.0f, -2.0f, 1.0f);
	DirectX::XMVECTOR	focus	= DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	DirectX::XMVECTOR	up		= DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixLookAtLH(eye, focus, up);
	
	//射影空間へ
	float	fov = DirectX::XMConvertToRadians(45.0f);
	float	width = Engine<DXDevice>::GetDevice().GetViewPort().Width;
	float	height = Engine<DXDevice>::GetDevice().GetViewPort().Height;
	float    aspect = width / height;
	float    nearZ = 0.1f;
	float    farZ = 1000.0f;
	DirectX::XMMATRIX projMatrix = DirectX::XMMatrixPerspectiveFovLH(fov, aspect, nearZ, farZ);
	
	//マトリックスの設定
	ConstantBuf cb;
	DirectX::XMStoreFloat4x4(&cb.world, DirectX::XMMatrixTranspose(worldMatrix));
	DirectX::XMStoreFloat4x4(&cb.view, DirectX::XMMatrixTranspose(viewMatrix));
	DirectX::XMStoreFloat4x4(&cb.projection, DirectX::XMMatrixTranspose(projMatrix));
	
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().UpdateSubresource(constantBuffer, 0, nullptr, &cb, 0, 0);
}

void	Sample::Render()
{
	stride = sizeof(Vertex);
	offset = 0;

	vertexShader.Set();
	pixelShader.Set();
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Engine<DXDevice>::GetDevice().GetDeviceContext3D().VSSetConstantBuffers(0, 1, &constantBuffer);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().HSSetConstantBuffers(0, 1, &constantBuffer);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().DSSetConstantBuffers(0, 1, &constantBuffer);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().GSSetConstantBuffers(0, 1, &constantBuffer);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().PSSetConstantBuffers(0, 1, &constantBuffer);

	Engine<DXDevice>::GetDevice().GetDeviceContext3D().DrawIndexed(4, 0, 0);
}


void	Sample::SetViewMat(const DirectX::XMFLOAT4X4& viewMat)
{
	//this->viewMat = viewMat;
}
void	Sample::SetProjMat(const DirectX::XMFLOAT4X4& projMat)
{
	//this->projMat = projMat;
}