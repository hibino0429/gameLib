#include "PhysicsData.h"


//!@brief	�R���X�g���N�^
PhysicsData::PhysicsData()
{

}
//!@brief	�f�X�g���N�^
PhysicsData::~PhysicsData()
{

}

////////////////////////////////////////////////////////////////////
//�ݒ菈��
////////////////////////////////////////////////////////////////////
//!@brief	�����d��(x)�̐ݒ�
void	PhysicsData::SetHorizonGravity(const double& horizonGravity)
{

}
//!@brief	�����d��(y)�̐ݒ�
void	PhysicsData::SetVerticalGravity(const double& verticalGravity)
{

}
//!@brief	���s�d��(z)�̐ݒ�
void	PhysicsData::SetDeepGravity(const double& deepGravity)
{

}
//!@brief	��C��R(���s�ړ����x)�̐ݒ�
void	PhysicsData::SetAirResistanceSpeed(const double& airResistanceSpeed)
{

}
//!@brief	��C��R(�p���x)�̐ݒ�
void	PhysicsData::SetAirResistanceAngleVelocity(const double& airResistanceAngleVelocity)
{

}
//!@brief	�ő�p���x�̐ݒ�
void	PhysicsData::SetMaxAirAngleVelocity(const double& maxAirAngleVelocity)
{

}
//!@brief	�ڐG�w�̌���
void	PhysicsData::SetContactSurfaceLayerThickness(const double& constactSurfaceLayerThickness)
{

}
//!@brief	�X�e�b�v���Ԃ̐ݒ�
void	PhysicsData::SetStepTime(const double& stepTime)
{

}



////////////////////////////////////////////////////////////////////
//�擾����
////////////////////////////////////////////////////////////////////
//!@brief	�����d��(x)�̎擾
const double&	PhysicsData::GetHorizonGravity() const
{
	return horizonGravity;
}
//!@brief	�����d��(y)�̎擾
const double&	PhysicsData::GetVerticalGravity() const
{
	return verticalGravity;
}
//!@brief	���s�d��(z)�̎擾
const double&	PhysicsData::GetDeepGravity() const
{
	return deepGravity;
}
//!@brief	��C��R(���s�ړ����x)�̎擾
const double&	PhysicsData::GetAirResistanceSpeed() const
{
	return airResistanceSpeed;
}
//!@brief	��C��R(�p���x)�̎擾
const double&	PhysicsData::GetAirResistanceAngleVelocity() const
{
	return airResistanceAngleVelocity;
}
//!@brief	�ő�p���x�̎擾
const double&	PhysicsData::GetMaxAirAngleVelocity() const
{
	return maxAirAngleVelocity;
}
//!@brief	�ڐG�w�̌����̎擾
const double&	PhysicsData::GetContactSurfaceLayerThickness() const
{
	return contactSurfaceLayerThickness;
}
//!@brief	�X�e�b�v���Ԃ̎擾
const double&	PhysicsData::GetStepTime() const
{
	return stepTime;
}