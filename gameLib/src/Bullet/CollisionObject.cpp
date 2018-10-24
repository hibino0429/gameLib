#include "CollisionObject.h"


namespace Physics
{
	CollisionObject::CollisionObject(CollisionShape * shape, bool ghost, const int myselfMask, const int giveMask, const Math::Vector3 & pos, const Math::Vector3 & rotate)
	{
		data.shape = shape;

		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(btVector3(pos.x, pos.y, pos.z));
		btQuaternion q = btQuaternion(btVector3(0, 0, 1), rotate.z) * btQuaternion(btVector3(1, 0, 0), rotate.x) * btQuaternion(btVector3(0, 1, 0), rotate.y);
		transform.setRotation(q);

		collisionObj = new btCollisionObject();
		collisionObj->setCollisionShape(shape);

		if (ghost)
		{
			collisionObj->setCollisionFlags(collisionObj->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		}
		else
		{
			collisionObj->setCollisionFlags(collisionObj->getCollisionFlags() & !btCollisionObject::CF_NO_CONTACT_RESPONSE);
		}
		collisionObj->setWorldTransform(transform);

		data.tagData = { "",0,nullptr };
		collisionObj->setUserPointer(this);
	}
	CollisionObject::~CollisionObject()
	{
		delete data.shape;
		data.shape = nullptr;
	}

	void CollisionObject::SetCollisionPosition(const Math::Vector3 & position)
	{
		 //= position;
	}

	void CollisionObject::SetCollisionRotation(const Math::Vector3 & rotation)
	{
		//data.rotation = rotation;
	}

	void CollisionObject::SetActiveFlag(bool activeFlag)
	{
		//data.active = activeFlag;
	}

	void CollisionObject::SetCollisionTag(const CollisionTag & tag)
	{
	}

	void CollisionObject::SetMyselfMask(const int mask)
	{
	}

	void CollisionObject::SetGiveMask(const int mask)
	{
	}

	const Math::Vector3 & CollisionObject::GetCollisionPosition() const
	{
		return Math::Vector3(0, 0, 0);
	}

	const Math::Vector3 & CollisionObject::GetCollisionRotation() const
	{
		return Math::Vector3(0, 0, 0);
	}

	const btCollisionObject& CollisionObject::GetCollision() const
	{
		return *collisionObj;
	}

	const btCollisionObject* CollisionObject::GetCollisionPtr() const
	{
		return collisionObj;
	}

	const int CollisionObject::GetMyselfMask() const
	{
		return 0;
	}

	const int CollisionObject::GetGiveMask() const
	{
		return 0;
	}

	const CollisionTag & CollisionObject::GetCollisionTag() const
	{
		return data.tagData;
	}

	bool CollisionObject::IsActive() const
	{
		return false;
	}


	//RigidBody
	RigidBody::RigidBody(CollisionShape* shape, const float mass, bool ghost, const int myselfMask, const int giveMask, const Math::Vector3 & pos, const Math::Vector3 & rotate)
	{
		//形状の取得
		data.collisionData.shape = shape;

		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(btVector3(pos.x, pos.y, pos.z));

		//慣性モーメントの計算
		btVector3 inertia(0, 0, 0);

		//質量が0なら固定の剛体
		btScalar objMass(mass);
		bool isDynamic = (mass != 0.0f);
		if (isDynamic)
		{
			data.collisionData.shape->calculateLocalInertia(mass, inertia);
		}

		//DefaultMotionStateの作成(外部から剛体を制御)
		btDefaultMotionState* motionState(new btDefaultMotionState(transform));

		//剛体の作成
		btRigidBody::btRigidBodyConstructionInfo rigidInfo(objMass, motionState, data.collisionData.shape, inertia);
		data.rigid = new btRigidBody(rigidInfo);
	}
	RigidBody::~RigidBody()
	{
		delete data.collisionData.shape;
		data.collisionData.shape = nullptr;
	}

	const btCollisionObject& RigidBody::GetCollision() const
	{
		return collision->GetCollision();
	}

	const btCollisionObject* RigidBody::GetCollisionPtr() const
	{
		return collision->GetCollisionPtr();
	}

	const btRigidBody * RigidBody::GetRigidBody() const
	{
		return data.rigid;
	}


}