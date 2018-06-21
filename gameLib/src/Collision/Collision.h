#pragma once

#include <ode/ode.h>

#if defined(_DEBUG)
#pragma comment(lib,"oded.lib")
#else
#pragma comment(lib,"ode.lib")
#endif

//----------------------------------------------------------------------------------------
//概要: コリジョン
//----------------------------------------------------------------------------------------
class Collision
{
public:
	Collision();
	~Collision();

private:
	dGeomID		geometory;

};