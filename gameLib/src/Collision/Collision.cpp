#include "Collision.h"

//コンストラクタ
Collision::Collision()
{
	geometory = dCreateBox(0, 0, 0, 0);	//スペース,x,y,z
	dGeomSetPosition(geometory, 0, 0, 0);
}

//デストラクタ
Collision::~Collision()
{
	if (geometory != nullptr)
	{
		dGeomDestroy(geometory);
		geometory = nullptr;
	}
}