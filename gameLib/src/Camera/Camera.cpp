#include "Camera.h"
#include "../../src/Engine/Engine.h"

//!@brief	�R���X�g���N�^
//!@brief	eyePos		���_
//!@brief	targetPos	�����_
//!@brief	upVec		��x�N�g��
Camera::Camera(const Math::Vector3& eyePos, const Math::Vector3& targetPos, const Math::Vector3& upVec)
	: position(eyePos)
	, angle(targetPos)
	, eyePos(eyePos)
	, targetPos(targetPos)
	, upVec(upVec)
	, constantBuf(nullptr)
{
	float asp = Engine<DXDevice>::GetDevice().GetViewPort().Width / Engine<DXDevice>::GetDevice().GetViewPort().Height;

	this->SetFovAngle(45.0f);
	this->SetAspect(asp);
	this->SetNearZ(0.1f);
	this->SetFarZ(100.0f);	
	//Create();
}

//!@brief	�f�X�g���N�^
Camera::~Camera()
{

}


//!@brief	�J�����̐���
bool	Camera::Create()
{
	D3D11_BUFFER_DESC	constantBufDesc;
	SecureZeroMemory(&constantBufDesc,sizeof(constantBufDesc));
	constantBufDesc.ByteWidth	= sizeof(ConstantBuffer);
	constantBufDesc.Usage		= D3D11_USAGE_DEFAULT;
	constantBufDesc.BindFlags	= D3D11_BIND_CONSTANT_BUFFER;
	constantBufDesc.CPUAccessFlags		= 0;
	constantBufDesc.MiscFlags			= 0;
	constantBufDesc.StructureByteStride = 0;

	auto result = Engine<DXDevice>::GetDevice().GetDevice3D().CreateBuffer(
		&constantBufDesc,
		nullptr,
		&constantBuf
	);

	if (FAILED(result))
	{
		MessageBoxA(nullptr, "�o�b�t�@�̍쐬�Ɏ��s", "Camera.Create()", MB_OK);
		return false;
	}
	return true;
}

//!@brief	View�ϊ����s��
void	Camera::LookAtLH()
{
	//view�ϊ�����
	DirectX::XMMATRIX viewMat = DirectX::XMMatrixTranspose(
		DirectX::XMMatrixLookAtLH(eyePos, targetPos, upVec)
	);
	
	DirectX::XMStoreFloat4x4(&constant.view, viewMat);
}

//!@brief	Ortho�ϊ����s��
void	Camera::OrthoFovLH()
{
	DirectX::XMMATRIX orthoViewMat = DirectX::XMMatrixTranspose(
		DirectX::XMMatrixOrthographicLH(
			Engine<DXDevice>::GetDevice().GetViewPort().Width,
			Engine<DXDevice>::GetDevice().GetViewPort().Height,
			nearZ,
			farZ)
	);

	//Ortho�r���[�ϊ����s��
	DirectX::XMStoreFloat4x4(&constant.view,orthoViewMat);	
}

//!@brief	Perspective�ϊ����s��
void	Camera::PerspectiveFovLH()
{
	//perspective�̕ϊ����s��
	DirectX::XMMATRIX perspectiveMat = DirectX::XMMatrixTranspose(
		DirectX::XMMatrixPerspectiveFovLH(
			DirectX::XMConvertToRadians(fovAngle),
			aspect,
			nearZ,
			farZ
		)
	);

	DirectX::XMMATRIX worldMat = DirectX::XMMatrixTranspose(
		DirectX::XMMatrixTranslation(eyePos.x, eyePos.y, eyePos.z)
	);

	DirectX::XMStoreFloat4x4(&constant.projection, perspectiveMat);
	DirectX::XMStoreFloat4x4(&constant.world, worldMat);
	//Engine<DXDevice>::GetDevice().GetDeviceContext3D().UpdateSubresource(constantBuf, 0, nullptr, &constant, 0, 0);
}




//�T�v: ���_�̐ݒ�
//����: eyePos_ ���_
void	Camera::SetEyePos(const Math::Vector3& eyePos_)
{
	eyePos = eyePos_;
}
//�T�v: �����_�̐ݒ�
//����: targetPos_ �����_
void	Camera::SetTargetPos(const Math::Vector3& targetPos_)
{
	targetPos = targetPos_;
}
//�T�v: ������x�N�g���̐ݒ�
//����: upVec_ ������x�N�g��
void	Camera::SetUpVec(const Math::Vector3& upVec_)
{
	upVec = upVec_;
}

//�T�v: ����p(�x��)�̐ݒ�
//����: fovAngle_ ����p
void	Camera::SetFovAngle(const float& fovAngle_)
{
	fovAngle = fovAngle_;
}
//�T�v: �A�X�y�N�g�̐ݒ�
//����: aspect_ �A�X�y�N�g��
void	Camera::SetAspect(const float& aspect_)
{
	aspect = aspect_;
}
//�T�v: �O�����e�ʂ܂ł̋����̐ݒ�
//����: nearZ_ �O�����e�ʂ܂ł̋���
void	Camera::SetNearZ(const float& nearZ_)
{
	nearZ = nearZ_;
}
//�T�v: ������e�ʂ܂ł̋����̐ݒ�
//����: farZ_ ������e�ʂ܂ł̋���
void	Camera::SetFarZ(const float& farZ_)
{
	farZ = farZ_;
}

//!@brief	�J�����̈ʒu�𓮂���
//!@param[in]	moveVec	�ړ���
void	Camera::AddVec(const Math::Vector3& moveVec)
{
	position += moveVec;
}

//!@brief	�r���[�s��̎擾
DirectX::XMFLOAT4X4&	Camera::GetViewMatrix()
{
	return this->constant.view;
}
//!@brief	�v���W�F�N�V�����s��̎擾
DirectX::XMFLOAT4X4&	Camera::GetProjectionMatrix()
{
	return this->constant.projection;
}