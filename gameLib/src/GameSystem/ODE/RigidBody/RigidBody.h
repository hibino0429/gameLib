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
//概要: RigidBody(剛体)クラス
//----------------------------------------------------------------------------------------
class RigidBody
{
public:
	RigidBody();
	~RigidBody();
	//概要: 剛体の生成
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
	dBodyID		rigidBody;	//剛体
	dGeomID		geometory;	//衝突検知
	dMass		mass;		//質量
};