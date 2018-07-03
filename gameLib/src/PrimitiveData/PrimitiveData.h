#pragma once
#include <vector>
#include "../../src/Device/DXDevice/DXDevice.h"
#include "../../src/Shader/VertexShader/VertexShader.h"
#include "../../src/Shader/PixelShader/PixelShader.h"
#include "../../src/Utility/Utility.hpp"
#include "../../src/Vertex/Vertex.h"


//-------------------------------------------------------------------------
//!@class		PrimitiveData
//!@brief	���_�o�b�t�@��C���f�b�N�X�o�b�t�@������
//!@brief	���_�̃f�[�^��C���f�b�N�X�̃f�[�^��ێ�����
//-------------------------------------------------------------------------
class Primitive
{
public:
	Primitive();
	~Primitive();
public:

	//!@�K�p������
	void	Attach();
	//!@brief	���_�f�[�^��ǉ�����
	void	AddVertexData(const Vertex& vertexData);
	//!@brief	�C���f�b�N�X�f�[�^��ǉ�����
	void	AddIndexData(const WORD& indexData);

	//!@brief	���_�f�[�^��ǉ�����
	void	AddVertexDatas(const std::vector<Vertex>&	vertexData);
	//!@brief	�C���f�b�N�X�f�[�^��ǉ�
	void	AddIndexDatas(const std::vector<int>& indexData);
	//!@brief	���_�o�b�t�@�̍쐬
	void	CreateVertexBuffer();
	//!@brief	�C���f�b�N�X�o�b�t�@�̍쐬
	void	CreateIndexBuffer();
private:
	ID3D11Buffer*	vertexBuffer;
	ID3D11Buffer*	indexBuffer;

	std::vector<Vertex>	vertices;	//���_�f�[�^
	std::vector<int>	indices;	//�C���f�b�N�X�f�[�^
};