#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define warning (disable : 4819)	

#include <ode/ode.h>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ODE/Physics/Physics.h"

//------------------------------------------------------------------------------
//!@class		DynamicShape
//!@brief	�`��������̃N���X
//!@brief	�`���\�����̂��������ۓI�Ȃ���
//------------------------------------------------------------------------------
class DynamicShape
{
public:
	//!@brief	�R���X�g���N�^
	DynamicShape();
	//!@brief	�f�X�g���N�^
	virtual ~DynamicShape();
public:
	//!@brief	���̂̍쐬
	void		Create();
	//!@brief	���W(x,y,z)�̎擾
	virtual const Math::Vector3&	GetPosition() const;
	//!@brief	���̂̑��x�̎擾
	virtual	const Math::Vector3&	GetVelocity() const;
	//!brief	���̂̎p���̉�]�s��̎擾
	virtual const dMatrix4&	GetRotationMatrix() const;

	//!@brief	���W�̐ݒ�
	virtual	void	SetPosition(const Math::Vector3& position);
	//!@brief	�C�ӎ�1�ɑ΂��Ă̎p���̐ݒ�
	virtual void	SetAxisAngle();

	//!@brief	�{�f�B�̏d�S�ɍ�p����͂̐ݒ�
	//!@brief	���̂��Ƃɏd�͂�������
	//!@param[in]	force	�����ɑ΂��Ă̗^�����
	virtual	void	AddForce(const Math::Vector3& force);
	//!@brief	���̂ɑ��x��^����
	//!@param[in]	�����ɑ΂��Ă̗^���鑬�x
	virtual	void	AddVelocity(const Math::Vector3& velocity);
	//!@brief	���̂̕������Z�̃t���O��ݒ肷��
	//!@param[in]	physicsOperationFlag	�������Z�̗L��(true)/����(false)�t���O
	virtual	void	SetPhysicsOperation(bool physicsOperationFlag);
	//!@brief	�`��̕\��
	virtual void	Draw() = 0;

	////////////////////////////////////////////////////////////////////
	//�擾����
	////////////////////////////////////////////////////////////////////
	//!@brief	���̂̎擾
	const dBodyID&	GetRigidBody() const;
	//!@brief	�Փˌ��m(�W�I���g��)�̎擾
	const dGeomID&	GetGeometory() const;
	//!@brief	���ʂ̎擾
	const dMass&	GetMass() const;
	//!@brief	���ʂ̎擾(���ʂ̕ύX��)
	dMass*		ChangeMass();
	////////////////////////////////////////////////////////////////////
	//�ݒ菈��
	////////////////////////////////////////////////////////////////////
	//!@brief	���̂̐ݒ�
	void		SetRigidBody(const dBodyID& rigidBody);
	//!@brief	�Փˌ��m(�W�I���g��)�̐ݒ�
	void		SetGeometory(const dGeomID& geometory);
	//!@brief	���ʂ̐ݒ�
	void		SetMass(const dMass& mass);
private:
	dBodyID			rigidBody;		//����
	dGeomID			geometory;		//�Փˌ��m
	dMass			mass;			//����
};

