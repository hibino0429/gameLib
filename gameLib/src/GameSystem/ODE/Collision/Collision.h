#pragma once

#include <ode/ode.h>

#if defined(_DEBUG)
#pragma comment(lib,"oded.lib")
#else
#pragma comment(lib,"ode.lib")
#endif

//----------------------------------------------------------------------------------------
//!@class		Collision
//!@brief	�R���W�����������N���X
//!@brief	�Փ˔�����s���`��
//----------------------------------------------------------------------------------------
class Collision
{
public:
	//!@brief	�R���X�g���N�^
	Collision();
	//!@brief	�f�X�g���N�^
	~Collision();

private:
	dGeomID		geometory;

};