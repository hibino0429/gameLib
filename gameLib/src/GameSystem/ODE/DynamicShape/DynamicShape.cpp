#include "DynamicShape.h"



//コンストラクタ
DynamicShape::DynamicShape()
{
	rigidBody = dBodyCreate(0);		//引数にworldIDを入れる
	dMassSetZero(&mass);

	Create();
}

//デストラクタ
DynamicShape::~DynamicShape()
{
	if (geometory != nullptr)
	{
		dGeomDestroy(geometory);
		geometory = nullptr;
	}
	if (rigidBody != nullptr)
	{
		dBodyDestroy(rigidBody);
		rigidBody = nullptr;
	}
}

//!@brief	剛体の作成
void		DynamicShape::Create()
{
	SetRigidBody(dBodyCreate(Physics::GetWorld()));
	dMassSetZero(ChangeMass());
}

//!@brief	座標(x,y,z)の取得
const Math::Vector3&	DynamicShape::GetPosition() const
{
	const dReal*	pos = dBodyGetPosition(rigidBody);
	return Math::Vector3(static_cast<float>(pos[0]), static_cast<float>(pos[1]), static_cast<float>(pos[2]));
}
//!@brief	剛体の速度の取得
const Math::Vector3&	DynamicShape::GetVelocity() const
{
	const dReal*	vel = dBodyGetLinearVel(rigidBody);
	return Math::Vector3(static_cast<float>(vel[0]), static_cast<float>(vel[1]), static_cast<float>(vel[2]));
}
//!brief	剛体の姿勢の回転行列の取得
const dMatrix4&		DynamicShape::GetRotationMatrix() const
{
	dMatrix4	rotateMatrix;
	return rotateMatrix;
}

//!@brief	座標の設定
void	DynamicShape::SetPosition(const Math::Vector3& position)
{
	dBodySetPosition(rigidBody, position.x, position.y, position.z);
}
//!@brief	任意軸1つに対しての姿勢の設定
void	DynamicShape::SetAxisAngle()
{
	//未実装
}

//!@brief	ボディの重心に作用する力の設定
//!@brief	剛体ごとに重力をかける
//!@param[in]	force	向きに対しての与える力
void	DynamicShape::AddForce(const Math::Vector3& force)
{
	dBodyAddForce(rigidBody, force.x, force.y, force.z);
}
//!@brief	剛体に速度を与える
//!@param[in]	向きに対しての与える速度
void	DynamicShape::AddVelocity(const Math::Vector3& velocity)
{
	dBodySetLinearVel(rigidBody, velocity.x, velocity.y, velocity.z);
}
//!@brief	剛体の物理演算のフラグを設定する
//!@param[in]	physicsOperationFlag	物理演算の有効(true)/無効(false)フラグ
void	DynamicShape::SetPhysicsOperation(bool physicsOperationFlag)
{
	if (physicsOperationFlag)
	{
		dBodyEnable(rigidBody);
	}
	else
	{
		dBodyDisable(rigidBody);
	}
}


////////////////////////////////////////////////////////////////////
//取得処理
////////////////////////////////////////////////////////////////////
//!@brief	剛体の取得
const dBodyID&	DynamicShape::GetRigidBody() const
{
	return rigidBody;
}
//!@brief	衝突検知(ジオメトリ)の取得
const dGeomID&	DynamicShape::GetGeometory() const
{
	return geometory;
}
//!@brief	質量の取得
const dMass&	DynamicShape::GetMass() const
{
	return mass;
}
//!@brief	質量の取得(質量の変更可)
dMass*		DynamicShape::ChangeMass()
{
	return &mass;
}

////////////////////////////////////////////////////////////////////
//設定処理
////////////////////////////////////////////////////////////////////
//!@brief	剛体の設定
void		DynamicShape::SetRigidBody(const dBodyID& rigidBody)
{
	this->rigidBody = rigidBody;
}
//!@brief	衝突検知(ジオメトリ)の設定
void		DynamicShape::SetGeometory(const dGeomID& geometory)
{
	this->geometory = geometory;
}
//!@brief	質量の設定
void		DynamicShape::SetMass(const dMass& mass)
{
	this->mass = mass;
}