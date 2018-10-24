#pragma once
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/GameSystem/ECS/Entity/Entity.h"
#include "../../src/Utility/Counter.hpp"



//----------------------------------------------
//!@class		Map
//!@brief	ƒ}ƒbƒv‚ðˆµ‚¤
//----------------------------------------------
class Map : public Component
{
public:
	Map();
	~Map();
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
private:
	float			moveSpeed;
	Counter_f		counter;
	Counter_f		rotateCnt;
};