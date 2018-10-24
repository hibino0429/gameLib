#pragma once

#if defined(_DEBUG)
#pragma comment(lib,"BulletCollision_vs2010_debug.lib")
#pragma comment(lib,"BulletDynamics_vs2010_debug.lib")
#pragma comment(lib,"BulletSoftBody_vs2010_debug.lib")
#pragma comment(lib,"LinearMath_vs2010_debug.lib")
#else
#pragma comment(lib,"BulletCollision_vs2010.lib")
#pragma comment(lib,"BulletDynamics_vs2010.lib")
#pragma comment(lib,"BulletSoftBody_vs2010.lib")
#pragma comment(lib,"LinearMath_vs2010.lib")
#endif

#include "../../src/DXEngine/Math/Math.h"
#include <../Bullet/btBulletCollisionCommon.h>
#include <../Bullet/btBulletDynamicsCommon.h>
#include <../Bullet/BulletCollision/CollisionDispatch/btInternalEdgeUtility.h>
#include <../Bullet/BulletCollision/CollisionDispatch/btGhostObject.h>
#include <string>


//����
namespace Physics
{
	//�R���W�����̃^�O�̃f�[�^
	struct CollisionTag
	{
		std::string		tagName;
		int				tagIndex;
		void*			userData;
	};

	//�R���W�����ɕK�v�ȃf�[�^
	struct CollisionData
	{
		btCollisionShape*	shape;
		CollisionTag		tagData;
		bool				active;
		int					myselfMask;
		int					giveMask;
	};

	//���̂ɕK�v�ȃf�[�^
	struct RigidBodyData
	{
		CollisionData	collisionData;
		btScalar		mass;		//����
		btVector3		inertia;	//�������[�����g
		btRigidBody*	rigid;		//����
		bool			isDynamic;	//�ړ�����I�u�W�F�N�g��
	};


	//!@class	�R���W�����̌`��
	typedef btCollisionShape CollisionShape;


	//�R���W�������I�u�W�F�N�g�Ƃ��Ĉ���
	class CollisionObject
	{
	public:
		//!@brief	�R���W�����̌`��ƂƂ��ɐ���
		CollisionObject(CollisionShape * shape, bool ghost, const int myselfMask, const int giveMask, const Math::Vector3 & pos = Math::Vector3(0, 0, 0), const Math::Vector3 & rotate = Math::Vector3(0, 0, 0));
		//!@brief	�`����폜
		~CollisionObject();
	public:
		//�ݒ菈��
		//!@brief	�R���W�����̈ʒu�̐ݒ�
		//!@param[in]	position	�ʒu
		void	SetCollisionPosition(const Math::Vector3& position);
		//!@brief	�R���W�����̉�]�̐ݒ�
		//!@param[in]	rotation	��]
		void	SetCollisionRotation(const Math::Vector3& rotation);
		//!@brief	�����Ă��邩�̃t���O�̐ݒ�
		//!@param[in]	activeFlag	�����Ă��邩�̃t���O
		void	SetActiveFlag(bool activeFlag);
		//!@brief	�R���W�����^�O�̐ݒ�
		//!@param[in]	tag	�^�O
		void	SetCollisionTag(const CollisionTag& tag);
		//!@brief	���g�̃}�X�N�̐ݒ�
		//!@param[in]	mask	�}�X�N�̐ݒ�
		void	SetMyselfMask(const int mask);
		//!@brief	����̃}�X�N�̐ݒ�
		//!@param[in]	mask	�}�X�N�̐ݒ�
		void	SetGiveMask(const int mask);

		//�擾����
		//!@brief	�R���W�����̈ʒu�̎擾
		const Math::Vector3&	GetCollisionPosition() const;
		//!@brief	�R���W�����̉�]�̎擾
		const Math::Vector3&	GetCollisionRotation() const;
		//!@brief	�R���W�����̎擾
		const btCollisionObject&	GetCollision() const;
		//!@brief	�R���W�����̃|�C���^�̎擾
		const btCollisionObject*	GetCollisionPtr() const;
		//!@brief	���g�̃}�X�N�̎擾
		const int	GetMyselfMask() const;
		//!@brief	����̃}�X�N�̎擾
		const int	GetGiveMask() const;
		//!@brief	�R���W�����^�O�̎擾
		const CollisionTag&	GetCollisionTag() const;
		//!@brief	�����Ă��邩����
		bool	IsActive() const;
	private:
		CollisionData		data;
		btCollisionObject*	collisionObj;
	};



	//����
	class RigidBody
	{
	public:
		RigidBody(CollisionShape* shape, const float mass, bool ghost, const int myselfMask, const int giveMask, const Math::Vector3 & pos = Math::Vector3(0, 0, 0), const Math::Vector3 & rotate = Math::Vector3(0, 0, 0));
		~RigidBody();
		void*	operator new(size_t size)
		{
			return _mm_malloc(size, 16);
		}
		void	operator delete(void* p)
		{
			_mm_free(p);
		}
	public:
		//!@brief	�R���W�����̎擾
		const btCollisionObject&	GetCollision() const;
		//!@brief	�R���W�����̃|�C���^�̎擾
		const btCollisionObject*	GetCollisionPtr() const;
		//!@brief	RigidBody�̎擾
		const btRigidBody*	GetRigidBody() const;
	private:
		CollisionObject*	collision;
		RigidBodyData		data;		//�R���W�����f�[�^
	};
}