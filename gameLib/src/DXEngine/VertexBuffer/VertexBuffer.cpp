#include "VertexBuffer.h"
#include "../../src/Utility/Utility.hpp"
#include "../../src/Engine/Engine.h"

//�T�v: �R���X�g���N�^
VertexBuffer::VertexBuffer(const int& vertexNum)
	: vertexNum(vertexNum)
{
	Create();
}
VertexBuffer::~VertexBuffer()
{
	Utility::SafeRelease(vertexBuf);
}

//�T�v: ���_�o�b�t�@�̕`��
void	VertexBuffer::Render()
{
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetVertexBuffers(0, 1, &vertexBuf, &stride, &offset);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().Draw(vertexNum, 0);
}






//!@brief		���_�f�[�^�̍쐬
void	VertexBuffer::Create()
{
	//�O�p�`
	Vertex	verteXData[] =
	{
		Vec3{0.0f,0.5f,0.0f},
		Vec3{0.5f,-0.5f,0.0f},
		Vec3{-0.5f,-0.5f,0.0f},
	};

	

	D3D11_BUFFER_DESC	bufferDesc;
	SecureZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(Vertex) * 3;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA	subData;
	SecureZeroMemory(&subData, sizeof(subData));
	subData.pSysMem = verteXData;
	subData.SysMemPitch = 0;
	subData.SysMemSlicePitch = 0;

	vertexBuf = nullptr;
	auto result = Engine<DXDevice>::GetDevice().GetDevice3D().CreateBuffer(&bufferDesc, &subData, &vertexBuf);

	if (FAILED(result))
	{
		return ;
	}

	D3D11_INPUT_ELEMENT_DESC	inputLayout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
	};

	for (int i = 0; i < 7; ++i)
	{
		layout[i] = inputLayout[i];
	}

	stride = sizeof(Vertex);
	offset = 0;
	
	
}


//!@brief		�C���v�b�g���C�A�E�g�̎擾
D3D11_INPUT_ELEMENT_DESC* VertexBuffer::GetInputLayout()
{
	return layout;
}