#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define warning (disable : 4819)	

#include<ode/ode.h>


#if defined(_DEBUG)
#pragma comment(lib,"oded.lib")
#else
#pragma comment(lib,"ode.lib")
#endif

//----------------------------------------------------------------------------------------
//�T�v: RigidBody(����)�N���X
//----------------------------------------------------------------------------------------
class RigidBody
{
public:
	RigidBody();
	~RigidBody();
	//�T�v: ���̂̐���
	void		Create();

	class Vec3
	{
	public:
		Vec3() {}
		Vec3(float x, float y, float z)
			: x(x),y(y),z(z)
		{}

	public:
		float x;
		float y;
		float z;
	};
private:
	dBodyID		rigidBody;	//����
	dGeomID		geometory;	//�Փˌ��m
	dMass		mass;		//����
};