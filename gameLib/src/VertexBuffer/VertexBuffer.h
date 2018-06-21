#pragma once
#include <vector>
#include "../../src/Device/DXDevice/DXDevice.h"



//---------------------------------------------------------------------
//!@brief ���_�o�b�t�@
//---------------------------------------------------------------------
class VertexBuffer
{
public:

	//!@brief	�x�N�g��
	class Vec3
	{
	public:
		Vec3() { x = 0; y = 0; z = 0; }
		Vec3(float x, float y, float z)
			: x(x),y(y),z(z)
		{

		}
		float x, y, z;
	};

	//!@brief	���_1�̏��
	struct Vertex
	{
		Vec3		position;	//���W
	};

public:
	//!@brief	�R���X�g���N�^
	VertexBuffer(const int& vertexNum);
	~VertexBuffer();

	//!@brief	 ���_�o�b�t�@�̕`��
	void	Render();


public:
	//!@brief		���_�f�[�^�̍쐬
	void	Create();

	//!@brief		�C���v�b�g���C�A�E�g�̎擾
	D3D11_INPUT_ELEMENT_DESC* GetInputLayout();

	
private:
	int					vertexNum;
	ID3D11Buffer*		vertexBuf;

	UINT	stride;		//�X�g���C�h
	UINT	offset;		//�I�t�Z�b�g

	D3D11_INPUT_ELEMENT_DESC	layout[7];
};
