#pragma once

#include <ode/ode.h>
#include <memory>
#include <vector>


#if defined(_DEBUG)
#pragma comment(lib,"oded.lib")
#else
#pragma comment(lib,"ode.lib")
#endif


//--------------------------------------------------------------------
//!@class		PhysicsData
//!@brief	物理に関するデータを扱うクラス
//!@brief	物理挙動のパラメータを保持する
//--------------------------------------------------------------------
class PhysicsData
{
public:
	//!@brief	コンストラクタ
	PhysicsData();
	//!@brief	デストラクタ
	~PhysicsData();
public:
	////////////////////////////////////////////////////////////////////
	//設定処理
	////////////////////////////////////////////////////////////////////
	//!@brief	水平重力(x)の設定
	void	SetHorizonGravity(const double& horizonGravity);
	//!@brief	垂直重力(y)の設定
	void	SetVerticalGravity(const double& verticalGravity);
	//!@brief	奥行重力(z)の設定
	void	SetDeepGravity(const double& deepGravity);
	//!@brief	空気抵抗(平行移動速度)の設定
	void	SetAirResistanceSpeed(const double& airResistanceSpeed);
	//!@brief	空気抵抗(角速度)の設定
	void	SetAirResistanceAngleVelocity(const double& airResistanceAngleVelocity);
	//!@brief	最大角速度の設定
	void	SetMaxAirAngleVelocity(const double& maxAirAngleVelocity);
	//!@brief	接触層の厚さ
	void	SetContactSurfaceLayerThickness(const double& constactSurfaceLayerThickness);
	//!@brief	ステップ時間の設定
	void	SetStepTime(const double& stepTime);

	////////////////////////////////////////////////////////////////////
	//取得処理
	////////////////////////////////////////////////////////////////////
	//!@brief	水平重力(x)の取得
	const double&	GetHorizonGravity() const;
	//!@brief	垂直重力(y)の取得
	const double&	GetVerticalGravity() const;
	//!@brief	奥行重力(z)の取得
	const double&	GetDeepGravity() const;
	//!@brief	空気抵抗(平行移動速度)の取得
	const double&	GetAirResistanceSpeed() const;
	//!@brief	空気抵抗(角速度)の取得
	const double&	GetAirResistanceAngleVelocity() const;
	//!@brief	最大角速度の取得
	const double&	GetMaxAirAngleVelocity() const;
	//!@brief	接触層の厚さの取得
	const double&	GetContactSurfaceLayerThickness() const;
	//!@brief	ステップ時間の取得
	const double&	GetStepTime() const;

private:
	//物理データ
	double			horizonGravity;				//水平重力(x)
	double			verticalGravity;			//垂直重力(y)
	double			deepGravity;				//奥行重力(z)
	double			airResistanceSpeed;			//空気抵抗(平行移動速度)
	double			airResistanceAngleVelocity;	//空気抵抗(角速度)
	double			maxAirAngleVelocity;		//最大角速度
	//衝突挙動データ
	double			contactSurfaceLayerThickness;	//接触層の厚さ
	//ステップ時間データ
	double			stepTime;					//ステップ時間

};