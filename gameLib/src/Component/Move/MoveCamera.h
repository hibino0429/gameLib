#pragma once
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/GameSystem/DirectInput/DirectKey/DirectKey.h"
#include "../../src/GameSystem/DirectInput/DirectMouse/DirectMouse.h"
#include "../../src/DXEngine/Math/Math.h"



class MoveInput : public Component
{
public:
	//!@brief	コンストラクタ
	MoveInput();
	//!@brief	デストラクタ
	~MoveInput();
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
private:
	//!@brief	前方と後方の移動
	void	MoveForwardAndBack();
	//!@brief	左右の移動
	void	MoveLeftAndRight();
	//!@brief	前方と後方の方向の決定
	void	DecideForwardAndBackDir();
	//!@brief	左右の方向の決定
	void	DecideLeftAndRightDir();
	//!@brief	回転の動作
	void	MoveRotation();
private:
	DirectKey*		key;
	DirectMouse*	mouse;
	Math::Vector3	dir;
	Math::Vector3	velocity;
	Math::Vector3	pos;
	Math::Vector3	prePos;
	float			speed;
	const float		DirOffset;
};