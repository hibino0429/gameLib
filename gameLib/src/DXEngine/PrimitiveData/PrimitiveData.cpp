#include "PrimitiveData.h"
#include "../../src/Engine/Engine.h"



//!@brief	�R���X�g���N�^
Primitive::Primitive()
	: vertexBuffer(nullptr)
	, indexBuffer(nullptr)
{
	Engine<DXDevice>::GetDevice().COMInitialize();
	SetDrawMode(D3D11_FILL_SOLID, D3D11_CULL_BACK);
}


//!@brief	�f�X�g���N�^
Primitive::~Primitive()
{
	
}

//!@brief	���_�f�[�^��ǉ�����
void	Primitive::AddVertexData(const Vertex& vertexData)
{
	vertices.push_back(vertexData);
}
//!@brief	�C���f�b�N�X�f�[�^��ǉ�����
void	Primitive::AddIndexData(const int& indexData)
{
	indices.push_back(indexData);
}

//!@brief	���_�f�[�^��ǉ�����
void	Primitive::AddVertexDatas(const std::vector<Vertex>&	vertexData)
{
	for (auto& vertex : vertexData)
	{
		vertices.push_back(vertex);
	}
}
//!@brief	�C���f�b�N�X�f�[�^��ǉ�
void	Primitive::AddIndexDatas(const std::vector<int>& indexData)
{
	for (auto& index : indexData)
	{
		indices.push_back(index);
	}
}

//!@�K�p������
void	Primitive::Attach()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetVertexBuffers(0, 1, &vertexBuffer.p, &stride, &offset);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().RSSetState(rasterizerState);

	if (indexBuffer == nullptr)
	{
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().Draw(vertices.size(), 0);
	}
	else
	{
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().DrawIndexed(indices.size(), 0, 0);
	}
}


//!@brief	���_�o�b�t�@�̍쐬
void	Primitive::CreateVertexBuffer()
{
	vertexBuffer.Release();
	if (vertices.size() <= 0) { return; }

	D3D11_BUFFER_DESC	vertexBufDesc;
	memset(&vertexBufDesc, 0, sizeof(vertexBufDesc));
	vertexBufDesc.ByteWidth		= sizeof(Vertex) * vertices.size();
	vertexBufDesc.Usage			= D3D11_USAGE_DEFAULT;
	vertexBufDesc.BindFlags		= D3D11_BIND_VERTEX_BUFFER;
	D3D11_SUBRESOURCE_DATA	vertexSubData;
	memset(&vertexSubData, 0, sizeof(vertexSubData));
	vertexSubData.pSysMem = vertices.data();

	Engine<DXDevice>::GetDevice().GetDevice3D().CreateBuffer(&vertexBufDesc, &vertexSubData, &vertexBuffer);
}
//!@brief	�C���f�b�N�X�o�b�t�@�̍쐬
void	Primitive::CreateIndexBuffer()
{
	indexBuffer.Release();
	if (indices.size() <= 0) { return; }

	D3D11_BUFFER_DESC		indexBufDesc;
	memset(&indexBufDesc, 0, sizeof(indexBufDesc));
	indexBufDesc.ByteWidth	= sizeof(int) * indices.size();
	indexBufDesc.Usage		= D3D11_USAGE_DEFAULT;
	indexBufDesc.BindFlags	= D3D11_BIND_INDEX_BUFFER;
	D3D11_SUBRESOURCE_DATA	indexSubData;
	memset(&indexSubData, 0, sizeof(indexSubData));
	indexSubData.pSysMem = indices.data();

	Engine<DXDevice>::GetDevice().GetDevice3D().CreateBuffer(&indexBufDesc, &indexSubData, &indexBuffer);
}

//!@brief	���_�f�[�^���X�V����
//!@param[in]	���_�f�[�^	vertexData
void	Primitive::UpDateVertexDatas(const std::vector<Vertex>& vertexData)
{
	vertices = vertexData;
}

void Primitive::SetDrawMode(const D3D11_FILL_MODE & fillMode, const D3D11_CULL_MODE & cullMode)
{
	D3D11_RASTERIZER_DESC	rasterizerDesc;
	memset(&rasterizerDesc, 0, sizeof(rasterizerDesc));
	rasterizerDesc.FillMode = fillMode;
	rasterizerDesc.CullMode = cullMode;
	rasterizerDesc.MultisampleEnable = false;
	rasterizerState.Release();
	Engine<DXDevice>::GetDevice().GetDevice3D().CreateRasterizerState(&rasterizerDesc, &rasterizerState);
}

