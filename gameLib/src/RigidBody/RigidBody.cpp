#include "RigidBody.h"

//�R���X�g���N�^
RigidBody::RigidBody()
{
	rigidBody = dBodyCreate(0);		//������worldID������
	dMassSetZero(&mass);
	
	Create();
}

//�f�X�g���N�^
RigidBody::~RigidBody()
{
	if (geometory != nullptr)
	{
		dGeomDestroy(geometory);
		geometory = nullptr;
	}
	if (rigidBody != nullptr)
	{
		dBodyDestroy(rigidBody);
		rigidBody = nullptr;
	}
}


//����
void	RigidBody::Create()
{
	Vec3 pos = Vec3(0, 0, 0);
	Vec3 scale = Vec3(1, 1, 1);
	dReal	totalMass = 0;

	rigidBody = dBodyCreate(0);		//������worldID������
	dMassSetZero(&mass);
	dMassSetBoxTotal(&mass, totalMass, scale.x, scale.y, scale.z);
	dBodySetMass(rigidBody, &mass);

	//�W�I���g���̍쐬�A�{�f�B�ɃR���W�����𔽉f
	geometory = dCreateBox(0, scale.x, scale.y, scale.z);
	dGeomSetBody(geometory, rigidBody);

	//�{�f�B�̈ʒu�ݒ�
	dBodySetPosition(rigidBody, pos.x, pos.y, pos.z);

}