#include "Sample.h"
#include "../../src/Component/Camera/Camera.h"
#include "../../src/Utility/Utility.hpp"

Sample::Sample()
	: pos(Math::Vector3(0,0,0))
	, angle(Math::Vector3(0,0,0))
	, scale(Math::Vector3(1,1,1))
{
	vertexBuffer = nullptr;
	this->indexBuffer = nullptr;

	Vex	vexDatas[] =
	{
		{ { -0.5f,  0.5f, 0.5f },{ 0.0f, 0.0f } },
	{ { 0.5f, -0.5f, 0.5f },{ 1.0f, 1.0f } },
	{ { -0.5f, -0.5f, 0.5f },{ 0.0f, 1.0f } },
	{ { 0.5f,  0.5f, 0.5f },{ 1.0f, 0.0f } }
	};

	int	inList[] = {
		0,1,2,
		0,3,1
	};

	//index�o�b�t�@�̍쐬
	D3D11_BUFFER_DESC	indexBufferDesc;
	indexBufferDesc.ByteWidth			= sizeof(int) * 6;
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
	
	//���_�o�b�t�@�̍쐬
	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(bufferDesc));
	bufferDesc.Usage				= D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth			= sizeof(Vex) * 4;
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
	
	////���͍���
	//D3D11_INPUT_ELEMENT_DESC inLayout[] = {
	//	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//	{ "COLOR",    0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//};

	//���͍���
	D3D11_INPUT_ELEMENT_DESC inLayout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	this->inputLayout = inLayout;

	vertexShader.SetEntryPointName("VS_main");
	pixelShader.SetEntryPointName("PS_main");

	//�V�F�[�_�̍쐬
	vertexShader.Create("./data/shaderData/textureShader", this->inputLayout, 2);
	pixelShader.Create("./data/shaderData/textureShader");
	
	//�萔�o�b�t�@�̍쐬
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
	
	//�r���[��Ԃ�
	DirectX::XMVECTOR	eye		= DirectX::XMVectorSet(2.0f, 2.0f, -2.0f, 1.0f);
	DirectX::XMVECTOR	focus	= DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	DirectX::XMVECTOR	up		= DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixLookAtLH(eye, focus, up);
	
	//�ˉe��Ԃ�
	float	fov = DirectX::XMConvertToRadians(45.0f);
	float	width = Engine<DXDevice>::GetDevice().GetViewPort().Width;
	float	height = Engine<DXDevice>::GetDevice().GetViewPort().Height;
	float    aspect = width / height;
	float    nearZ = 0.1f;
	float    farZ = 1000.0f;
	DirectX::XMMATRIX projMatrix = DirectX::XMMatrixPerspectiveFovLH(fov, aspect, nearZ, farZ);
	
	//�}�g���b�N�X�̐ݒ�
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
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
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