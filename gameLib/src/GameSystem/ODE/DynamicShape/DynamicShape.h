#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define warning (disable : 4819)	

#include <ode/ode.h>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ODE/Physics/Physics.h"

//------------------------------------------------------------------------------
//!@class		DynamicShape
//!@brief	形状を持つ剛体クラス
//!@brief	形状を表す剛体を示す抽象的なもの
//------------------------------------------------------------------------------
class DynamicShape
{
public:
	//!@brief	コンストラクタ
	DynamicShape();
	//!@brief	デストラクタ
	virtual ~DynamicShape();
public:
	//!@brief	剛体の作成
	void		Create();
	//!@brief	座標(x,y,z)の取得
	virtual const Math::Vector3&	GetPosition() const;
	//!@brief	剛体の速度の取得
	virtual	const Math::Vector3&	GetVelocity() const;
	//!brief	剛体の姿勢の回転行列の取得
	virtual const dMatrix4&	GetRotationMatrix() const;

	//!@brief	座標の設定
	virtual	void	SetPosition(const Math::Vector3& position);
	//!@brief	任意軸1つに対しての姿勢の設定
	virtual void	SetAxisAngle();

	//!@brief	ボディの重心に作用する力の設定
	//!@brief	剛体ごとに重力をかける
	//!@param[in]	force	向きに対しての与える力
	virtual	void	AddForce(const Math::Vector3& force);
	//!@brief	剛体に速度を与える
	//!@param[in]	向きに対しての与える速度
	virtual	void	AddVelocity(const Math::Vector3& velocity);
	//!@brief	剛体の物理演算のフラグを設定する
	//!@param[in]	physicsOperationFlag	物理演算の有効(true)/無効(false)フラグ
	virtual	void	SetPhysicsOperation(bool physicsOperationFlag);
	//!@brief	形状の表示
	virtual void	Draw() = 0;

	////////////////////////////////////////////////////////////////////
	//取得処理
	////////////////////////////////////////////////////////////////////
	//!@brief	剛体の取得
	const dBodyID&	GetRigidBody() const;
	//!@brief	衝突検知(ジオメトリ)の取得
	const dGeomID&	GetGeometory() const;
	//!@brief	質量の取得
	const dMass&	GetMass() const;
	//!@brief	質量の取得(質量の変更可)
	dMass*		ChangeMass();
	////////////////////////////////////////////////////////////////////
	//設定処理
	////////////////////////////////////////////////////////////////////
	//!@brief	剛体の設定
	void		SetRigidBody(const dBodyID& rigidBody);
	//!@brief	衝突検知(ジオメトリ)の設定
	void		SetGeometory(const dGeomID& geometory);
	//!@brief	質量の設定
	void		SetMass(const dMass& mass);
private:
	dBodyID			rigidBody;		//剛体
	dGeomID			geometory;		//衝突検知
	dMass			mass;			//質量
};

