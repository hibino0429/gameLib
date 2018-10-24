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
	dWorldID		GetWorld();
	//!@brief	ODE��Ԃ̎擾
	//!@return	ODE�̋��
	dSpaceID		GetCollisionSpace();
	//!@brief	�W���C���g�O���[�v�̎擾
	//!@return	�W���C���g�O���[�v�̎擾
	dJointGroupID	GetJointGroupID();
	//!@brief	�X�e�b�v���Ԃ̎擾
	float	GetStepTime() const;

private:
	dWorldID			world;				//ODE���E
	dSpaceID			collisionSpace;		//ODE���
	dJointGroupID		contactGroup;		//�W���C���g�O���[�v

	float			horizonGravity;		//�����d��(x)
	float			verticalGravity;	//�����d��(y)
	float			deepGravity;		//���s�d��(z)
	float			stepTime;			//�X�e�b�v����
};



//������Ԃ������N���X
//��{�I�ɁAstatic�ȃO���[�o���ϐ�
//�������E�̏Փˌ��m���s��
class PhysicsWorld
{
public:
	//!@brief	��������������Ԃ�K�p
	//!@param[in]	physics	�������
	static void	Attach(Physics* physics);
	//!@brief	�Փˌ��m�̃R�[���o�b�N
	//!@param[in]	data	�Փ˃f�[�^
	//!@param[in]	col		���g�̕���
	//!@param[in]	col2	����̕���
	static void	NearCallBack(void* data, dGeomID geometory1, dGeomID geometory2);
	//!@brief	�������E�̍X�V
	static void	UpDate();
	//!@brief	�Փ˂��Ă��邩��Ԃ�
	static bool	Hit();
	//!@brief	1�O�̏Փ˂������������`�F�b�N
	static bool	PreHit();
	//!@brief	�ێ����Ă��镨����Ԃ��擾����
	//!@return	�������
	static Physics&	GetPhysics();
public:
	static int num;					//���݂̏Փˌ�
	static int preNum;				//1�O�̏Փˌ�
	static Physics*	physicsWorld;	//�������
};

