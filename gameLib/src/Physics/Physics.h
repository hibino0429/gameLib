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
//�T�v: �����G���W���N���X
//--------------------------------------------------------------------
class Physics
{
public:
	//�T�v: �R���X�g���N�^
	Physics();
	//�T�v: �f�X�g���N�^
	~Physics();

	//�T�v: �������E�̎擾
	//�߂�l: �������E
	dWorldID		GetWorld() const;
	//�T�v: ODE��Ԃ̎擾
	//�߂�l: ODE�̋��
	dSpaceID		GetCollisionSpace() const;
	//�T�v: �W���C���g�O���[�v�̎擾
	//�߂�l: �W���C���g�O���[�v�̎擾
	dJointGroupID	GetJointGroupID() const;

	//�T�v: ���͊w�v�Z�̎��{
	void	WorldStep();

private:
	dWorldID			world;			//ODE���E
	dSpaceID		collisionSpace;		//ODE���
	dJointGroupID	jointGroup;			//�W���C���g�O���[�v
	float			horizonGravity;		//�����d��(x)
	float			verticalGravity;	//�����d��(y)
	float			deepGravity;		//���s�d��(z)
	float			stepTime;			//�X�e�b�v����
};