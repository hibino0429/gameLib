#pragma once

#include <ode/ode.h>

#if defined(_DEBUG)
#pragma comment(lib,"oded.lib")
#else
#pragma comment(lib,"ode.lib")
#endif

//----------------------------------------------------------------------------------------
//�T�v: �R���W����
//----------------------------------------------------------------------------------------
class Collision
{
public:
	Collision();
	~Collision();

private:
	dGeomID		geometory;

};