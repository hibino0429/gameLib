#include "Model.h"
#include "../../src/Utility/Utility.hpp"
#include "../../src/DXEngine/DXEngine/DXEngine.h"

//!@brief	�R���X�g���N�^
Model::Model()
	: pos(Math::Vector3(0,0,0))
	, angle(Math::Vector3(0,0,0))
	, scale(Math::Vector3(1,1,1))
	, constantBuf(nullptr)
{
	fbxModel = new FbxModel("./data/image/ball.fbx");
	animationData = new AnimationData();
	vertexShader = new VertexShader();
	pixelShader = new PixelShader();
	primitive = new Primitive();

	primitive->AddVertexDatas(fbxModel->GetVertexData());
	primitive->AddIndexDatas(fbxModel->GetVertexPolygonVertices());

	primitive->CreateVertexBuffer();
	primitive->CreateIndexBuffer();

	CreateInputLayout();
	CreateConstantBuffer();
}

//!@brief	�R���X�g���N�^
//!@param[in]	filePath	�t�@�C���p�X
Model::Model(const std::string& filePath)
	: pos(Math::Vector3(0,0,0))
	, angle(Math::Vector3(0,0,0))
	, scale(Math::Vector3(1,1,1))
	, constantBuf(nullptr)
{
	fbxModel = new FbxModel(filePath);
	animationData = new AnimationData();
	vertexShader = new VertexShader();
	pixelShader = new PixelShader();
	primitive = new Primitive();
	//fbx����A�j���[�V�����ԍ����󂯎��
	animationData->SetAnimationNumber(fbxModel->GetNowAnimationNumber());
	animationData->SetAnimationName(fbxModel->GetNowAnimationName());
	//�v���~�e�B�u�̐����ƒǉ�
	primitive->AddVertexDatas(fbxModel->GetVertexData());
	primitive->AddIndexDatas(fbxModel->GetVertexPolygonVertices());
	primitive->CreateVertexBuffer();
	primitive->CreateIndexBuffer();
	//�C���v�b�g���C�A�E�g�ƒ萔�o�b�t�@
	CreateInputLayout();
	CreateConstantBuffer();
}

//!@brief	�f�X�g���N�^
Model::~Model()
{
	//Delete
	Utility::SafeDelete(vertexShader);
	Utility::SafeDelete(pixelShader);
	Utility::SafeDelete(primitive);
	Utility::SafeDelete(fbxModel);
	Utility::SafeDelete(animationData);
	//Release
	Utility::SafeRelease(constantBuf);
}

//!@brief	�ʒu�̐ݒ�
void	Model::SetPos(const Math::Vector3& pos)
{
	this->pos = pos;
}
//!@brief	�X�P�[���̐ݒ�
void	Model::SetScale(const Math::Vector3& scale)
{
	this->scale = scale;
}
void	Model::UpDate()
{
	vertexShader->Set();
	pixelShader->Set();
	//Fbx�̃A�j���[�V�����s��̍X�V
	if (fbxModel->IsAnimation())
	{
		fbxModel->AnimationMatrix();
	}
	primitive->UpDateVertexDatas(fbxModel->GetVertexData());
	//���_�f�[�^�ƃC���f�b�N�X�f�[�^�̍Đݒ�
	primitive->CreateVertexBuffer();
	primitive->CreateIndexBuffer();
	//�A�j���[�V�����ԍ��̐ݒ�
	animationData->SetAnimationNumber(fbxModel->GetNowAnimationNumber());
	animationData->SetAnimationName(fbxModel->GetNowAnimationName());
	//animationData->Output();
}

void	Model::Render()
{
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().VSSetConstantBuffers(0, 1, &constantBuf);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().HSSetConstantBuffers(0, 1, &constantBuf);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().DSSetConstantBuffers(0, 1, &constantBuf);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().GSSetConstantBuffers(0, 1, &constantBuf);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().PSSetConstantBuffers(0, 1, &constantBuf);
	primitive->Attach();
}

//!@brief	�C���v�b�g���C�A�E�g�̍쐬
void	Model::CreateInputLayout()
{
	//���͍���
	D3D11_INPUT_ELEMENT_DESC inputLayout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	vertexShader->Create("./data/shaderData/VertexShader", inputLayout, 2);
	pixelShader->Create("./data/shaderData/PixelShader");
}

//!@brief	�萔�o�b�t�@�̍쐬
void	Model::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC	constantBufDesc;
	memset(&constantBufDesc, 0, sizeof(constantBufDesc));
	constantBufDesc.ByteWidth	= sizeof(ConstantBuffer);
	constantBufDesc.BindFlags	= D3D11_BIND_CONSTANT_BUFFER;
	constantBufDesc.Usage		= D3D11_USAGE_DEFAULT;

	Engine<DXDevice>::GetDevice().GetDevice3D().CreateBuffer(&constantBufDesc, nullptr, &constantBuf);
}

//!@brief	�A�j���[�V�����̍X�V
//!@param[in]	upDateAnimationNumber	�X�V����A�j���[�V�����ԍ�
void	Model::UpDateAnimation(const int& upDateAnimationNumber)
{
	fbxModel->SetAnimationNumber(upDateAnimationNumber);
	fbxModel->CreateAnimation();
	fbxModel->CreateAnimationTime();
}

//!@brief	�}�g���b�N�X�̐ݒ�
//void	Model::SetMatrix(Camera* camera)
//{
//	DirectX::XMMATRIX	matT = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
//	DirectX::XMMATRIX	matR = DirectX::XMMatrixRotationRollPitchYaw(
//		DirectX::XMConvertToRadians(angle.y),
//		DirectX::XMConvertToRadians(angle.x), 
//		DirectX::XMConvertToRadians(angle.z));
//	DirectX::XMMATRIX	matS = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
//	
//	DirectX::XMMATRIX worldMatrix = matS * matR * matT;
//	
//	//�}�g���b�N�X�̐ݒ�
//	ConstantBuffer cb;
//	DirectX::XMStoreFloat4x4(&cb.world, DirectX::XMMatrixTranspose(worldMatrix));
//	DirectX::XMStoreFloat4x4(&cb.view, camera->GetView());
//	DirectX::XMStoreFloat4x4(&cb.projection, camera->GetProj());
//	Engine<DXDevice>::GetDevice().GetDeviceContext3D().UpdateSubresource(constantBuf, 0, nullptr, &cb, 0, 0);
//}