#include "Collision.h"

//�R���X�g���N�^
Collision::Collision()
{
	geometory = dCreateBox(0, 0, 0, 0);	//�X�y�[�X,x,y,z
	dGeomSetPosition(geometory, 0, 0, 0);
}

//�f�X�g���N�^
Collision::~Collision()
{
	if (geometory != nullptr)
	{
		dGeomDestroy(geometory);
		geometory = nullptr;
	}
}