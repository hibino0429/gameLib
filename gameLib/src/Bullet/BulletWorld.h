#pragma once
#include <vector>
#include <memory>
#include "../../src/Bullet/CollisionObject.h"
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/Bullet/BulletDebugDraw.h"


namespace Physics
{
	//物理世界
	class BulletWorld
	{
	public:
		BulletWorld();
		~BulletWorld();
	public:
		bool	Initialize();
		void	Finalize();
		void	Run();
	public:
		//!@brief	デバッグ描画のセット
		//!@param[in]	debugDraw	デバッグ描画オブジェクト
		void	SetDebugDraw(BulletDebugDraw& debugDraw);
		void	DebugDraw();
		//!@brief	デバッグ時のビュー行列の設定
		//!@param[in]	viewMatrix	ビュー行列
		void	SetViewMatrix(const DirectX::XMMATRIX& viewMatrix);
		//!@brief	デバッグ時のプロジェクション行列の設定
		//!@param[in]	projMatrix	プロジェクション行列
		void	SetProjMatrix(const DirectX::XMMATRIX& projMatrix);
		//!@brief	カメラ行列のセット
		//void	SetCameraMatrix(Camera& camera);
	public:
		//!@brief	三角形の形状の生成
		//!@param[in]	point1	頂点1つ目の座標
		//!@param[in]	point2	頂点2つ目の座標
		//!@param[in]	point3	頂点3つ目の座標
		CollisionShape*	CreateTriangleShape(const Math::Vector3& point1, const Math::Vector3& point2, const Math::Vector3& point3);
		//!@brief	凸面体三角形の形状の生成
		//!@param[in]	triangleMesh	凸面体のポインタ
		CollisionShape*	CreateTriangleMeshShape(btTriangleMesh* triangleMesh);
		//!@brief	球の形状の生成
		//!@param[in]	radius	半径
		CollisionShape*	CreateShpereShape(const float radius);
		//!@brief	カプセルの形状の生成
		//!@param[in]	radius	半径
		//!@param[in]	height	高さ
		CollisionShape*	CreateCapsuleShape(const float radius, const float height);
		//!@brief	凸面体三角形の生成
		//!@param[in]	vertics	ポリゴンの座標データ
		//!@param[in]	triangleNum	ポリゴンの数
		btTriangleMesh*	CreateTriangleMeshShape(Math::Vector3* vertics, const int triangleNum);
		//!@brief	直方体の形状の生成
		//!@param[in]	halfWidth	中心からの幅
		//!@param[in]	halfHeight	中心からの高さ
		//!@param[in]	halfDepth	中心からの奥行
		CollisionShape*	CreateBoxShape(const float halfWidth, const float halfHeight, const float halfDepth);
	public:
		//!@brief	剛体オブジェクトの生成
		//!@param[in]	shape	形状
		//!@param[in]	mass	質量
		//!@param[in]	ghost	コリジョンと剛体が衝突フル化のフラグ(true:衝突しない)
		//!@param[in]	myselfMask	自身側の衝突マスク
		//!@param[in]	giveMask	相手側の衝突マスク
		//!@param[in]	pos			初期位置
		//!@param[in]	rotate		回転
		RigidBody*	CreateRigidBody(CollisionShape* shape, const float mass, bool ghost, const int myselfMask, const int giveMask, const Math::Vector3& pos = Math::Vector3(0, 0, 0), const Math::Vector3& rotate = Math::Vector3(0, 0, 0));
		//!@brief	コリジョンオブジェクトの生成
		//!@param[in]	ghost	コリジョンと剛体が衝突フル化のフラグ(true:衝突しない)
		//!@param[in]	myselfMask	自身側の衝突マスク
		//!@param[in]	giveMask	相手側の衝突マスク
		//!@param[in]	pos			初期位置
		//!@param[in]	rotate		回転
		CollisionObject*	CreateCollisionObject(CollisionShape* shape, bool ghost, const int myselfMask, const int giveMask, const Math::Vector3& pos = Math::Vector3(0, 0, 0), const Math::Vector3& rotate = Math::Vector3(0, 0, 0));

		//!@brief	物理世界に登録している剛体を削除
		void		RemoveRigidBody(RigidBody* rigidBody);
		//!@brief	物理世界に登録しているコリジョンを削除
		void		RemoveCollision(CollisionObject* collision);
		//!@brief	形状を削除
		void		RemoveCollisionShape(CollisionShape* shape);

	private:
		//!@brief	Bulletのコリジョンオブジェクトの削除
		//!@param[in]	obj	Bulletのコリジョンオブジェクト
		void		RemoveBulletCollisionObject(btCollisionObject* obj);
	public:
		void*	operator new(size_t size)
		{
			return _mm_malloc(size, 16);
		}
		void	operator delete(void* p)
		{
			_mm_free(p);
		}
	private:
		std::vector<CollisionTag*>	confrictResult;

		btDiscreteDynamicsWorld*			bulletWorld;
		btDefaultCollisionConfiguration*	config;
		btCollisionDispatcher*				dispatcher;
		btConstraintSolver*					solver;
		btBroadphaseInterface*				broadphase;
		btAlignedObjectArray<CollisionShape*>	shapeArray;
		btVector3							skyVector;
		BulletDebugDraw*					debugDraw;
	};



	//衝突判定
	//すべての交点を収集するRayとの当たり判定
	class HitsRayCallback : public btCollisionWorld::AllHitsRayResultCallback
	{
	public:
		btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace) override
		{
			//ここに独自の衝突処理
			return addSingleResult(rayResult, normalInWorldSpace);
		}
	};



	class BulletDemo
	{
	public:
		//!@brief	初期化
		void	Initialize()
		{
			collisionConfig = new btDefaultCollisionConfiguration();
			dispacher = new btCollisionDispatcher(collisionConfig);
			broadphase = new btDbvtBroadphase();
			solver = new btSequentialImpulseConstraintSolver();
			dynamicWorld = new btDiscreteDynamicsWorld(dispacher, broadphase, solver, collisionConfig);

			dynamicWorld->setGravity(btVector3(0, -10, 0));

			groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));
			collsionShapes.push_back(groundShape);

			btTransform groundTrans;
			groundTrans.setIdentity();
			groundTrans.setOrigin(btVector3(0, -56, 0));

			{
				btScalar mass(0.);
				bool isDynamic = (mass != 0.f);

				btVector3	localInertia(0, 0, 0);
				if (isDynamic)
				{
					groundShape->calculateLocalInertia(mass, localInertia);
				}

				btDefaultMotionState*	motionState = new btDefaultMotionState(groundTrans);
				btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, groundShape, localInertia);
				btRigidBody*	body = new btRigidBody(rbInfo);
				dynamicWorld->addRigidBody(body);
			}
			//dynamic Rigidbody Create
			{
				btCollisionShape*	colShape = new btSphereShape(btScalar(1.));
				collsionShapes.push_back(colShape);

				btTransform startTrans;
				startTrans.setIdentity();

				btScalar mass(1.f);

				bool isDynamic = (mass != 0.f);
				btVector3	localInertia(0, 0, 0);
				if (isDynamic)
				{
					colShape->calculateLocalInertia(mass, localInertia);
				}
				startTrans.setOrigin(btVector3(2, 10, -80));

				btDefaultMotionState*	motionState = new btDefaultMotionState(startTrans);

				btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, colShape, localInertia);
				btRigidBody*	body = new btRigidBody(rbInfo);

				dynamicWorld->addRigidBody(body);
			}
		}
		//!@brief	終了
		void	Finalize()
		{
			for (int i = dynamicWorld->getNumCollisionObjects() - 1; i >= 0; i--)
			{
				btCollisionObject* obj = dynamicWorld->getCollisionObjectArray()[i];
				btRigidBody* body = btRigidBody::upcast(obj);
				if (body && body->getMotionState())
				{
					delete body->getMotionState();
				}
				dynamicWorld->removeCollisionObject(obj);
				delete obj;
			}
			for (int j = 0; j < collsionShapes.size(); j++)
			{
				btCollisionShape* shape = collsionShapes[j];
				collsionShapes[j] = 0;
				delete shape;
			}
			//delete dynamics world
			delete dynamicWorld;

			//delete solver
			delete solver;

			//delete broadphase
			delete broadphase;

			//delete dispatcher
			delete dispacher;

			delete collisionConfig;

			//next line is optional: it will be cleared by the destructor when the array goes out of scope
			collsionShapes.clear();

		}
		
		//更新
	void	UpDate()
	{
		for (int i = 0; i < 200; ++i)
		{
			dynamicWorld->stepSimulation(1.0f / 60.0f, 10);
			for (int j = dynamicWorld->getNumCollisionObjects() - 1; j >= 0; j--)
			{
				if (j == 1)
				{
					btCollisionObject* obj = dynamicWorld->getCollisionObjectArray()[j];
					btRigidBody* body = btRigidBody::upcast(obj);
					if (body && body->getMotionState())
					{
						btTransform trans;
						body->getMotionState()->getWorldTransform(trans);
						printf("world pos : ,%f,%f,%f\n", float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
					}
				}
			}
		}
	}
	private:
		btDefaultCollisionConfiguration*	collisionConfig;
		btCollisionDispatcher*				dispacher;
		btBroadphaseInterface*				broadphase;
		btSequentialImpulseConstraintSolver*	solver;
		btDiscreteDynamicsWorld*			dynamicWorld;

		btCollisionShape*					groundShape;
		btAlignedObjectArray<btCollisionShape*>	collsionShapes;

	};
}