#pragma once
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/GameSystem/ECS/Entity/Entity.h"
#include "../../src/GameSystem/DirectInput/DirectKey/DirectKey.h"



//----------------------------------------------
//!@class		MovePlayer
//!@brief	ƒvƒŒƒCƒ„[‚ğ‘€ì‚·‚é
//----------------------------------------------
class MovePlayer : public Component
{
public:
	MovePlayer();
	~MovePlayer();
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
private:
	float			moveSpeed;
	DirectKey*		key;
};