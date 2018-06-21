#include "Camera.h"
#include "../../src/Engine/Engine.h"

//!@brief	�R���X�g���N�^
//!@brief	eyePos		���_
//!@brief	targetPos	�����_
//!@brief	upVec		��x�N�g��
Camera::Camera(const Math::Vector3& position, const Math::Vector3& angle)
	: position(position)
	, angle(angle)
	, constantBuf(nullptr)
{
	this->SetFovAngle(30.0f);
	this->SetAspect(640.0f / 480.0f);
	this->SetNearZ(1.0f);
	this->SetFarZ(20.0f);

	Create();
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
	constantBufDesc.ByteWidth = static_cast<UINT>(sizeof(constant));
	constantBufDesc.Usage = D3D11_USAGE_DEFAULT;
	constantBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufDesc.CPUAccessFlags = 0;
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
	constant.view = DirectX::XMMatrixTranspose(
		DirectX::XMMatrixInverse(
			nullptr,
			DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(angle.x)) *
			DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(angle.y)) *
			DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(angle.z)) *
			DirectX::XMMatrixTranslation(position.x, position.y, position.z)
		)
	);

	Engine<DXDevice>::GetDevice().GetDeviceContext3D().UpdateSubresource(constantBuf, 0, nullptr, &constant, 0, 0);

	//DXEngine::GetDeviceContext3D().UpdateSubresource(constantBuf, 0, nullptr, &constant, 0, 0);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().VSSetConstantBuffers(0, 1, &constantBuf);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().HSSetConstantBuffers(0, 1, &constantBuf);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().DSSetConstantBuffers(0, 1, &constantBuf);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().GSSetConstantBuffers(0, 1, &constantBuf);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().PSSetConstantBuffers(0, 1, &constantBuf);
}

//!@brief	Ortho�ϊ����s��
void	Camera::OrthoFovLH()
{
	float width = 0, height = 0;
	//Ortho�r���[�ϊ����s��
	constant.projection = DirectX::XMMatrixTranspose(
		DirectX::XMMatrixOrthographicLH(
			static_cast<float>(width),
			static_cast<float>(height),
			nearZ,
			farZ)
	);

	Engine<DXDevice>::GetDevice().GetDeviceContext3D().UpdateSubresource(constantBuf, 0, nullptr, &constant.projection, 0, 0);
}

//�T�v: Perspective�ϊ����s��
void	Camera::PerspectiveFovLH()
{
	constant.projection = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XMConvertToRadians(fovAngle),
		aspect,
		nearZ,
		farZ
	);

}



//�T�v: ���_�̐ݒ�
//����: eyePos_ ���_
void	Camera::SetEyePos(const Math::Vector3& eyePos_)
{
	//eyePos = eyePos_;
}
//�T�v: �����_�̐ݒ�
//����: targetPos_ �����_
void	Camera::SetTargetPos(const Math::Vector3& targetPos_)
{
	//targetPos = targetPos_;
}
//�T�v: ������x�N�g���̐ݒ�
//����: upVec_ ������x�N�g��
void	Camera::SetUpVec(const Math::Vector3& upVec_)
{
	//upVec = upVec_;
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



//!@brief �萔�o�b�t�@�̎擾
ID3D11Buffer**	Camera::GetConstantBuf()
{
	return &constantBuf;
}



//!@brief	�J�����̈ʒu�𓮂���
//!@param[in]	moveVec	�ړ���
void	Camera::AddVec(const Math::Vector3& moveVec)
{
	position += moveVec;
}