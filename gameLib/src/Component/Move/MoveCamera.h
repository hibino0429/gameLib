#pragma once
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/GameSystem/DirectInput/DirectKey/DirectKey.h"
#include "../../src/GameSystem/DirectInput/DirectMouse/DirectMouse.h"
#include "../../src/DXEngine/Math/Math.h"



class MoveInput : public Component
{
public:
	//!@brief	�R���X�g���N�^
	MoveInput();
	//!@brief	�f�X�g���N�^
	~MoveInput();
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
private:
	//!@brief	�O���ƌ���̈ړ�
	void	MoveForwardAndBack();
	//!@brief	���E�̈ړ�
	void	MoveLeftAndRight();
	//!@brief	�O���ƌ���̕����̌���
	void	DecideForwardAndBackDir();
	//!@brief	���E�̕����̌���
	void	DecideLeftAndRightDir();
	//!@brief	��]�̓���
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