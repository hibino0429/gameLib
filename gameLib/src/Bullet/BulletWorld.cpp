#include "BulletWorld.h"




namespace Physics
{
	BulletWorld::BulletWorld()
	{
		bulletWorld = nullptr;
		solver = nullptr;
		broadphase = nullptr;
		dispatcher = nullptr;
		config = nullptr;

		if (!Initialize())
		{
			throw std::runtime_error("Physics Initialize Error");
		}
	}

	BulletWorld::~BulletWorld()
	{
		Finalize();
	}

	bool BulletWorld::Initialize()
	{
		try {
			Finalize();

			config = new btDefaultCollisionConfiguration;
			dispatcher = new btCollisionDispatcher(config);
			solver = new btSequentialImpulseConstraintSolver;
			broadphase = new btDbvtBroadphase();
			bulletWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,config);

			//デバッグ描画の生成
			debugDraw = new BulletDebugDraw();
			//物理世界にデバッグ描画を設定
			bulletWorld->setDebugDrawer(debugDraw);
			bulletWorld->setGravity(btVector3(0.0f, -10.0f, 0.0f));
			skyVector = btVector3(0.0f, 1.0f, 0.0f);
		}
		catch (...)
		{
			Finalize();
			return false;
		}
		return true;
	}

	void BulletWorld::Finalize()
	{
		if (bulletWorld)
		{
			bulletWorld->setDebugDrawer(nullptr);
			bulletWorld = nullptr;
		}

		for (int i = 0; i < shapeArray.size(); ++i)
		{
			delete shapeArray[i];
			shapeArray[i] = nullptr;
		}
		
		if (bulletWorld != nullptr)
		{
			for (int i = bulletWorld->getNumCollisionObjects() - 1; i >= 0; --i)
			{
				btCollisionObject* obj = bulletWorld->getCollisionObjectArray()[i];
				RemoveBulletCollisionObject(obj);
			}
			delete bulletWorld;
			bulletWorld = nullptr;
		}
		if (solver != nullptr)
		{
			delete solver;
			solver = nullptr;
		}
		if (broadphase != nullptr)
		{
			delete broadphase;
			broadphase = nullptr;
		}
		if (dispatcher != nullptr)
		{
			delete dispatcher;
			dispatcher = nullptr;
		}
		if (config != nullptr)
		{
			delete config;
			config = nullptr;
		}
		if (debugDraw != nullptr)
		{
			delete debugDraw;
			debugDraw = nullptr;
		}
	}

	void BulletWorld::Run()
	{
		bulletWorld->stepSimulation(1.0f / 60.0f, 10);
	}

	void BulletWorld::SetDebugDraw(BulletDebugDraw& debugDraw)
	{
		bulletWorld->setDebugDrawer(&debugDraw);
	}

	void BulletWorld::DebugDraw()
	{
		debugDraw->Draw();
		bulletWorld->debugDrawWorld();
	}

	void BulletWorld::SetViewMatrix(const DirectX::XMMATRIX & viewMatrix)
	{
		debugDraw->SetViewMatrix(viewMatrix);
	}

	void BulletWorld::SetProjMatrix(const DirectX::XMMATRIX & projMatrix)
	{
		debugDraw->SetProjMatrix(projMatrix);
	}

	/*void BulletWorld::SetCameraMatrix(Camera & camera)
	{
		debugDraw->SetCameraMatrix(camera);
	}*/

	CollisionShape* BulletWorld::CreateTriangleShape(const Math::Vector3 & point1, const Math::Vector3 & point2,const Math::Vector3& point3)
	{
		btScalar points[9] =
		{
			point1.x,point1.y,point1.z,
			point2.x,point2.y,point2.z,
			point3.x,point3.y,point3.z
		};
		btCollisionShape*	shape = new btConvexHullShape(points, 3, 3 * sizeof(btScalar));
		shapeArray.push_back(shape);
		return shape;
	}

	CollisionShape* BulletWorld::CreateTriangleMeshShape(btTriangleMesh * triangleMesh)
	{
		btBvhTriangleMeshShape*	byhMesh = new btBvhTriangleMeshShape(triangleMesh, true);
		shapeArray.push_back(byhMesh);
		return byhMesh;
	}

	CollisionShape* BulletWorld::CreateShpereShape(const float radius)
	{
		btCollisionShape*	shape = new btSphereShape(radius);
		shapeArray.push_back(shape);
		debugDraw->CreateSphere();
		return shape;
	}

	CollisionShape* BulletWorld::CreateCapsuleShape(const float radius, const float height)
	{
		btCollisionShape*	shape = new btCapsuleShape(radius, height);
		shapeArray.push_back(shape);
		debugDraw->CreateCapsule();
		return shape;
	}

	btTriangleMesh* BulletWorld::CreateTriangleMeshShape(Math::Vector3 * vertics, const int triangleNum)
	{
		btTriangleMesh*	mesh = new btTriangleMesh;
		for (int i = 0; i < triangleNum; ++i)
		{
			mesh->addTriangle(
				btVector3(vertics[i * 3].x, vertics[i * 3].y, vertics[i * 3].z),
				btVector3(vertics[i * 3 + 1].x, vertics[i * 3 + 1].y, vertics[i * 3 + 1].z),
				btVector3(vertics[i * 3 + 2].x, vertics[i * 3 + 2].y, vertics[i * 3 + 2].z));
		}
		return mesh;
	}

	CollisionShape* BulletWorld::CreateBoxShape(const float halfWidth, const float halfHeight, const float halfDepth)
	{
		btCollisionShape* shape = new btBoxShape(btVector3(halfWidth, halfHeight, halfDepth));
		shapeArray.push_back(shape);
		debugDraw->CreateBox();
		return shape;
	}

	RigidBody* BulletWorld::CreateRigidBody(CollisionShape* shape, const float mass, bool ghost,const int myselfMask, const int giveMask, const Math::Vector3 & pos, const Math::Vector3 & rotate)
	{
		RigidBody*	rigidBody = new RigidBody(shape, mass,ghost,myselfMask, giveMask, pos, rotate);
		bulletWorld->addRigidBody(const_cast<btRigidBody*>(rigidBody->GetRigidBody()), myselfMask, giveMask);
		return rigidBody;
	}

	CollisionObject* BulletWorld::CreateCollisionObject(CollisionShape * shape, bool ghost,const int myselfMask, const int giveMask, const Math::Vector3 & pos, const Math::Vector3 & rotate)
	{
		CollisionObject*	collision = new CollisionObject(shape, ghost, myselfMask, giveMask,pos,rotate);
		bulletWorld->addCollisionObject(const_cast<btCollisionObject*>(collision->GetCollisionPtr()),myselfMask,giveMask);
		return collision;
	}

	void BulletWorld::RemoveRigidBody(RigidBody* rigidBody)
	{
		RemoveBulletCollisionObject(const_cast<btCollisionObject*>(rigidBody->GetCollisionPtr()));
		rigidBody = nullptr;
	}

	void BulletWorld::RemoveCollision(CollisionObject* collision)
	{
		RemoveBulletCollisionObject(const_cast<btCollisionObject*>(collision->GetCollisionPtr()));
		collision = nullptr;
	}

	void BulletWorld::RemoveCollisionShape(CollisionShape * shape)
	{
		shapeArray.remove(shape);
		delete shape;
		shape = nullptr;
	}

	void BulletWorld::RemoveBulletCollisionObject(btCollisionObject* obj)
	{
		if (!obj) { return; }
		btRigidBody* rigid = btRigidBody::upcast(obj);
		if (rigid != nullptr)
		{
			if (rigid->getMotionState())
			{
				delete rigid->getMotionState();
				rigid->setMotionState(nullptr);
			}
		}
		if (obj->getUserPointer())
		{
			delete static_cast<CollisionObject*>(obj->getUserPointer());
			obj->setUserPointer(nullptr);
		}
		bulletWorld->removeCollisionObject(obj);
		delete obj;
		obj = nullptr;
	}
}