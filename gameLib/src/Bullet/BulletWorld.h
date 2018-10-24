#pragma once
#include <vector>
#include <memory>
#include "../../src/Bullet/CollisionObject.h"
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/Bullet/BulletDebugDraw.h"


namespace Physics
{
	//�������E
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
		//!@brief	�f�o�b�O�`��̃Z�b�g
		//!@param[in]	debugDraw	�f�o�b�O�`��I�u�W�F�N�g
		void	SetDebugDraw(BulletDebugDraw& debugDraw);
		void	DebugDraw();
		//!@brief	�f�o�b�O���̃r���[�s��̐ݒ�
		//!@param[in]	viewMatrix	�r���[�s��
		void	SetViewMatrix(const DirectX::XMMATRIX& viewMatrix);
		//!@brief	�f�o�b�O���̃v���W�F�N�V�����s��̐ݒ�
		//!@param[in]	projMatrix	�v���W�F�N�V�����s��
		void	SetProjMatrix(const DirectX::XMMATRIX& projMatrix);
		//!@brief	�J�����s��̃Z�b�g
		//void	SetCameraMatrix(Camera& camera);
	public:
		//!@brief	�O�p�`�̌`��̐���
		//!@param[in]	point1	���_1�ڂ̍��W
		//!@param[in]	point2	���_2�ڂ̍��W
		//!@param[in]	point3	���_3�ڂ̍��W
		CollisionShape*	CreateTriangleShape(const Math::Vector3& point1, const Math::Vector3& point2, const Math::Vector3& point3);
		//!@brief	�ʖʑ̎O�p�`�̌`��̐���
		//!@param[in]	triangleMesh	�ʖʑ̂̃|�C���^
		CollisionShape*	CreateTriangleMeshShape(btTriangleMesh* triangleMesh);
		//!@brief	���̌`��̐���
		//!@param[in]	radius	���a
		CollisionShape*	CreateShpereShape(const float radius);
		//!@brief	�J�v�Z���̌`��̐���
		//!@param[in]	radius	���a
		//!@param[in]	height	����
		CollisionShape*	CreateCapsuleShape(const float radius, const float height);
		//!@brief	�ʖʑ̎O�p�`�̐���
		//!@param[in]	vertics	�|���S���̍��W�f�[�^
		//!@param[in]	triangleNum	�|���S���̐�
		btTriangleMesh*	CreateTriangleMeshShape(Math::Vector3* vertics, const int triangleNum);
		//!@brief	�����̂̌`��̐���
		//!@param[in]	halfWidth	���S����̕�
		//!@param[in]	halfHeight	���S����̍���
		//!@param[in]	halfDepth	���S����̉��s
		CollisionShape*	CreateBoxShape(const float halfWidth, const float halfHeight, const float halfDepth);
	public:
		//!@brief	���̃I�u�W�F�N�g�̐���
		//!@param[in]	shape	�`��
		//!@param[in]	mass	����
		//!@param[in]	ghost	�R���W�����ƍ��̂��Փ˃t�����̃t���O(true:�Փ˂��Ȃ�)
		//!@param[in]	myselfMask	���g���̏Փ˃}�X�N
		//!@param[in]	giveMask	���葤�̏Փ˃}�X�N
		//!@param[in]	pos			�����ʒu
		//!@param[in]	rotate		��]
		RigidBody*	CreateRigidBody(CollisionShape* shape, const float mass, bool ghost, const int myselfMask, const int giveMask, const Math::Vector3& pos = Math::Vector3(0, 0, 0), const Math::Vector3& rotate = Math::Vector3(0, 0, 0));
		//!@brief	�R���W�����I�u�W�F�N�g�̐���
		//!@param[in]	ghost	�R���W�����ƍ��̂��Փ˃t�����̃t���O(true:�Փ˂��Ȃ�)
		//!@param[in]	myselfMask	���g���̏Փ˃}�X�N
		//!@param[in]	giveMask	���葤�̏Փ˃}�X�N
		//!@param[in]	pos			�����ʒu
		//!@param[in]	rotate		��]
		CollisionObject*	CreateCollisionObject(CollisionShape* shape, bool ghost, const int myselfMask, const int giveMask, const Math::Vector3& pos = Math::Vector3(0, 0, 0), const Math::Vector3& rotate = Math::Vector3(0, 0, 0));

		//!@brief	�������E�ɓo�^���Ă��鍄�̂��폜
		void		RemoveRigidBody(RigidBody* rigidBody);
		//!@brief	�������E�ɓo�^���Ă���R���W�������폜
		void		RemoveCollision(CollisionObject* collision);
		//!@brief	�`����폜
		void		RemoveCollisionShape(CollisionShape* shape);

	private:
		//!@brief	Bullet�̃R���W�����I�u�W�F�N�g�̍폜
		//!@param[in]	obj	Bullet�̃R���W�����I�u�W�F�N�g
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



	//�Փ˔���
	//���ׂĂ̌�_�����W����Ray�Ƃ̓����蔻��
	class HitsRayCallback : public btCollisionWorld::AllHitsRayResultCallback
	{
	public:
		btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace) override
		{
			//�����ɓƎ��̏Փˏ���
			return addSingleResult(rayResult, normalInWorldSpace);
		}
	};



	class BulletDemo
	{
	public:
		//!@brief	������
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
		//!@brief	�I��
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
		
		//�X�V
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