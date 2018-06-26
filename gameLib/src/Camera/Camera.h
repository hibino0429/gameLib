#pragma once
#include "../../src/Math/Math.h"
#include "../../src/Device/DXDevice/DXDevice.h"

//----------------------------------------------------------------------------
//!@brief		カメラ
//----------------------------------------------------------------------------
class Camera
{
public:
	//!@brief	コンストラクタ
	//!@param[in]	position_	位置
	//!@param[in]	angle_		向き
	Camera(const Math::Vector3& eyePos, const Math::Vector3& targetPos,const Math::Vector3& upVec);
	//!@brief	デストラクタ
	~Camera();

	//!@brief	カメラの生成
	bool	Create();
	//!@brief	View変換を行う
	void	LookAtLH();
	//!@brief	Perspective変換を行う
	void	PerspectiveFovLH();
	//!@brief	Ortho変換を行う
	void	OrthoFovLH();

	//!@brief	視点の設定
	//!@param[in]	eyePos_ 視点
	void	SetEyePos(const Math::Vector3& eyePos_);
	//!@brief	注視点の設定
	//!@param[in]	 targetPos_ 注視点
	void	SetTargetPos(const Math::Vector3& targetPos_);
	//!@brief	 上方向ベクトルの設定
	//!@param[in]	upVec_ 上方向ベクトル
	void	SetUpVec(const Math::Vector3& upVec_);

	//!@brief	視	野角(度数)の設定
	//!@param[in] fovAngle_ 視野角
	void	SetFovAngle(const float& fovAngle_);
	//!@brief	アスペクトの設定
	//!@param[in]	 aspect_ アスペクト比
	void	SetAspect(const float& aspect_);
	//!@brief	前方投影面までの距離の設定
	//!@param[in]	nearZ_ 前方投影面までの距離
	void	SetNearZ(const float& nearZ_);
	//!@brief	後方投影面までの距離の設定
	//!@param[in]	farZ_ 後方投影面までの距離
	void	SetFarZ(const float& farZ_);
	//!@brief	カメラの位置を動かす
	//!@param[in]	moveVec	移動量
	void	AddVec(const Math::Vector3& moveVec);

private:
	//!@brief	定数バッファの定義
	struct ConstantBuffer
	{
		DirectX::XMFLOAT4X4	world;
		DirectX::XMFLOAT4X4	view;
		DirectX::XMFLOAT4X4	projection;
	};

public:
	//!@brief	ビュー行列の取得
	DirectX::XMFLOAT4X4&	GetViewMatrix();
	//!@brief	プロジェクション行列の取得
	DirectX::XMFLOAT4X4&	GetProjectionMatrix();


private:
	ID3D11Buffer*	constantBuf;//定数バッファ
	ConstantBuffer	constant;	//定義したバッファの内容

private:
	float			fovAngle;	//視野角(度数)
	float			aspect;		//アスペクト比
	float			nearZ;		//前方投影面までの距離
	float			farZ;		//広報投影面までの距離
	
	Math::Vector3			eyePos;
	Math::Vector3			targetPos;
	Math::Vector3			upVec;

	Math::Vector3			position;
	Math::Vector3			angle;
	Math::Vector3			color;

};