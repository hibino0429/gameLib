#pragma once

#include <ode/ode.h>
#include <memory>
#include <vector>
#include "../../src/GameSystem/ODE/Collision/Collision.h"
#include "../../src/GameSystem/ODE/RigidBody/RigidBody.h"

#if defined(_DEBUG)
#pragma comment(lib,"oded.lib")
#else
#pragma comment(lib,"ode.lib")
#endif


//--------------------------------------------------------------------
//!@class		�����G���W���N���X
//!@brief	�����������N���X
//!@brief	����������񋟂����肷��
//--------------------------------------------------------------------
class Physics
{
public:
	//!@brief	�R���X�g���N�^
	Physics();
	//!@brief	�f�X�g���N�^
	~Physics();
public:
	//!@brief	�������E�̎擾
	//!@return	�������E
	static dWorldID		GetWorld();
	//!@brief	ODE��Ԃ̎擾
	//!@return	ODE�̋��
	static dSpaceID		GetCollisionSpace();
	//!@brief	�W���C���g�O���[�v�̎擾
	//!@return	�W���C���g�O���[�v�̎擾
	static dJointGroupID	GetJointGroupID();

	//!@brief	���͊w�v�Z�̎��{
	static void	WorldStep();
public:
	//!@brief	�X�V
	static void	UpDate();

	//!@brief	�Փˌ��m
	//!@param[in]	data	�Փ˃f�[�^
	//!@param[in]	col		���g�̕���
	//!@param[in]	col2	����̕���
	static void	NearCallBack(void* data, const Collision& col, const Collision& col2);


private:
	static dWorldID			world;				//ODE���E
	static dSpaceID			collisionSpace;		//ODE���
	static dJointGroupID	contactGroup;		//�W���C���g�O���[�v

	std::vector<RigidBody*>	rigidBodys;
	std::vector<Collision*>	collsions;

	float			horizonGravity;		//�����d��(x)
	float			verticalGravity;	//�����d��(y)
	float			deepGravity;		//���s�d��(z)
	static float	stepTime;			//�X�e�b�v����
};