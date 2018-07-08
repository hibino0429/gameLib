#pragma once

#include <ode/ode.h>
#include <memory>
#include <vector>


#if defined(_DEBUG)
#pragma comment(lib,"oded.lib")
#else
#pragma comment(lib,"ode.lib")
#endif


//--------------------------------------------------------------------
//!@class		PhysicsData
//!@brief	�����Ɋւ���f�[�^�������N���X
//!@brief	���������̃p�����[�^��ێ�����
//--------------------------------------------------------------------
class PhysicsData
{
public:
	//!@brief	�R���X�g���N�^
	PhysicsData();
	//!@brief	�f�X�g���N�^
	~PhysicsData();
public:
	////////////////////////////////////////////////////////////////////
	//�ݒ菈��
	////////////////////////////////////////////////////////////////////
	//!@brief	�����d��(x)�̐ݒ�
	void	SetHorizonGravity(const double& horizonGravity);
	//!@brief	�����d��(y)�̐ݒ�
	void	SetVerticalGravity(const double& verticalGravity);
	//!@brief	���s�d��(z)�̐ݒ�
	void	SetDeepGravity(const double& deepGravity);
	//!@brief	��C��R(���s�ړ����x)�̐ݒ�
	void	SetAirResistanceSpeed(const double& airResistanceSpeed);
	//!@brief	��C��R(�p���x)�̐ݒ�
	void	SetAirResistanceAngleVelocity(const double& airResistanceAngleVelocity);
	//!@brief	�ő�p���x�̐ݒ�
	void	SetMaxAirAngleVelocity(const double& maxAirAngleVelocity);
	//!@brief	�ڐG�w�̌���
	void	SetContactSurfaceLayerThickness(const double& constactSurfaceLayerThickness);
	//!@brief	�X�e�b�v���Ԃ̐ݒ�
	void	SetStepTime(const double& stepTime);

	////////////////////////////////////////////////////////////////////
	//�擾����
	////////////////////////////////////////////////////////////////////
	//!@brief	�����d��(x)�̎擾
	const double&	GetHorizonGravity() const;
	//!@brief	�����d��(y)�̎擾
	const double&	GetVerticalGravity() const;
	//!@brief	���s�d��(z)�̎擾
	const double&	GetDeepGravity() const;
	//!@brief	��C��R(���s�ړ����x)�̎擾
	const double&	GetAirResistanceSpeed() const;
	//!@brief	��C��R(�p���x)�̎擾
	const double&	GetAirResistanceAngleVelocity() const;
	//!@brief	�ő�p���x�̎擾
	const double&	GetMaxAirAngleVelocity() const;
	//!@brief	�ڐG�w�̌����̎擾
	const double&	GetContactSurfaceLayerThickness() const;
	//!@brief	�X�e�b�v���Ԃ̎擾
	const double&	GetStepTime() const;

private:
	//�����f�[�^
	double			horizonGravity;				//�����d��(x)
	double			verticalGravity;			//�����d��(y)
	double			deepGravity;				//���s�d��(z)
	double			airResistanceSpeed;			//��C��R(���s�ړ����x)
	double			airResistanceAngleVelocity;	//��C��R(�p���x)
	double			maxAirAngleVelocity;		//�ő�p���x
	//�Փˋ����f�[�^
	double			contactSurfaceLayerThickness;	//�ڐG�w�̌���
	//�X�e�b�v���ԃf�[�^
	double			stepTime;					//�X�e�b�v����

};