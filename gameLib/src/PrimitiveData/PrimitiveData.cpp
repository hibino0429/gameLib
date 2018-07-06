#include "PrimitiveData.h"
#include "../../src/Engine/Engine.h"



//!@brief	�R���X�g���N�^
Primitive::Primitive()
	: vertexBuffer(nullptr)
	, indexBuffer(nullptr)
{

}


//!@brief	�f�X�g���N�^
Primitive::~Primitive()
{
	Utility::SafeRelease(vertexBuffer);
	Utility::SafeRelease(indexBuffer);
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
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().DrawIndexed(indices.size(), 0, 0);
}




//!@brief	���_�o�b�t�@�̍쐬
void	Primitive::CreateVertexBuffer()
{
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