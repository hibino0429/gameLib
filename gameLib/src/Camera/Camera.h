#pragma once
#include "../../src/Math/Math.h"
#include "../../src/Device/DXDevice/DXDevice.h"

//----------------------------------------------------------------------------
//!@brief		�J����
//----------------------------------------------------------------------------
class Camera
{
public:
	//!@brief	�R���X�g���N�^
	//!@param[in]	position_	�ʒu
	//!@param[in]	angle_		����
	Camera(const Math::Vector3& eyePos, const Math::Vector3& targetPos,const Math::Vector3& upVec);
	//!@brief	�f�X�g���N�^
	~Camera();

	//!@brief	�J�����̐���
	bool	Create();
	//!@brief	View�ϊ����s��
	void	LookAtLH();
	//!@brief	Perspective�ϊ����s��
	void	PerspectiveFovLH();
	//!@brief	Ortho�ϊ����s��
	void	OrthoFovLH();

	//!@brief	���_�̐ݒ�
	//!@param[in]	eyePos_ ���_
	void	SetEyePos(const Math::Vector3& eyePos_);
	//!@brief	�����_�̐ݒ�
	//!@param[in]	 targetPos_ �����_
	void	SetTargetPos(const Math::Vector3& targetPos_);
	//!@brief	 ������x�N�g���̐ݒ�
	//!@param[in]	upVec_ ������x�N�g��
	void	SetUpVec(const Math::Vector3& upVec_);

	//!@brief	��	��p(�x��)�̐ݒ�
	//!@param[in] fovAngle_ ����p
	void	SetFovAngle(const float& fovAngle_);
	//!@brief	�A�X�y�N�g�̐ݒ�
	//!@param[in]	 aspect_ �A�X�y�N�g��
	void	SetAspect(const float& aspect_);
	//!@brief	�O�����e�ʂ܂ł̋����̐ݒ�
	//!@param[in]	nearZ_ �O�����e�ʂ܂ł̋���
	void	SetNearZ(const float& nearZ_);
	//!@brief	������e�ʂ܂ł̋����̐ݒ�
	//!@param[in]	farZ_ ������e�ʂ܂ł̋���
	void	SetFarZ(const float& farZ_);
	//!@brief	�J�����̈ʒu�𓮂���
	//!@param[in]	moveVec	�ړ���
	void	AddVec(const Math::Vector3& moveVec);

private:
	//!@brief	�萔�o�b�t�@�̒�`
	struct ConstantBuffer
	{
		DirectX::XMFLOAT4X4	world;
		DirectX::XMFLOAT4X4	view;
		DirectX::XMFLOAT4X4	projection;
	};

public:
	//!@brief	�r���[�s��̎擾
	DirectX::XMFLOAT4X4&	GetViewMatrix();
	//!@brief	�v���W�F�N�V�����s��̎擾
	DirectX::XMFLOAT4X4&	GetProjectionMatrix();


private:
	ID3D11Buffer*	constantBuf;//�萔�o�b�t�@
	ConstantBuffer	constant;	//��`�����o�b�t�@�̓��e

private:
	float			fovAngle;	//����p(�x��)
	float			aspect;		//�A�X�y�N�g��
	float			nearZ;		//�O�����e�ʂ܂ł̋���
	float			farZ;		//�L�񓊉e�ʂ܂ł̋���
	
	Math::Vector3			eyePos;
	Math::Vector3			targetPos;
	Math::Vector3			upVec;

	Math::Vector3			position;
	Math::Vector3			angle;
	Math::Vector3			color;

};