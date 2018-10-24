#pragma once
#include <d3d11.h>
#include <atlbase.h>
#include "../../src/DXEngine/Math/Math.h"



//!@brief	�萔�o�b�t�@�\����
struct CBuffer 
{
	DirectX::XMFLOAT4X4	world;
	DirectX::XMFLOAT4X4	view;
	DirectX::XMFLOAT4X4	projection;
	DirectX::XMFLOAT4	lightDirection;
	DirectX::XMFLOAT4	lightColor;
};


//���W�n�ϊ��s��f�[�^
struct TransMatrix
{
	DirectX::XMMATRIX	worldMat;
	DirectX::XMMATRIX	viewMat;
	DirectX::XMMATRIX	projMat;

	//�q�[�v�Ŋ��蓖�Ă�ꂽ�I�u�W�F�N�g��16�ɃA���C�����g����Ă��Ȃ�
	//XMMATRIX��ێ����Ă���ƁA���̂悤��Warning���o��
	//�ێ�����Ƃ��́AXMFLOAT4X4���g�p����
	/*DirectX::XMFLOAT4X4	worldMat;
	DirectX::XMFLOAT4X4	viewMat;
	DirectX::XMFLOAT4X4	projMat;*/
};

//-------------------------------------------------------
//!@class		ConstantBuffer
//!@brief	���ʂ̒萔�o�b�t�@��ێ�����
//-------------------------------------------------------
class ConstantBuffer
{
public:
	//!@brief	�R���X�g���N�^
	//!@brief	���ʂ̒萔�o�b�t�@�̏ꍇ
	ConstantBuffer();
	//!@brief	�R���X�g���N�^
	//!@brief	�萔�o�b�t�@�̃T�C�Y�����n��
	ConstantBuffer(const size_t& bufferSize);
	//!@brief	�R���X�g���N�^
	//!@brief	�Ǝ��̒萔�o�b�t�@�̏ꍇ
	ConstantBuffer(const D3D11_BUFFER_DESC& cBufferDesc);
	//!@brief	�f�X�g���N�^
	~ConstantBuffer();
public:
	//!@brief	�X�V
	//!@param[in]	constantBuffer	��`�����萔�o�b�t�@
	void	UpDate(void* constantBuffer);
	//!@brief	�`��
	void	Render();
	//!@brief	�萔�o�b�t�@�̐ݒ�
	//!@param[in]	cBuffer	�萔�o�b�t�@
	//void	SetConstantBuffer(const CBuffer& cBuffer);
private:
	ATL::CComPtr<ID3D11Buffer>	constantBuf;
};
