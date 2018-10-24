#pragma once
#include "../../src/Component/SpriteRender/SpriteRender.h"
#include "../../src/GameSystem/ECS/Entity/Entity.h"
#include "../../src/Component/SpriteAnimation/SpriteAnimData.h"
#include "../../src/DXEngine/Math/Math.h"


//---------------------------------------------------------------------
//!@class		SpriteAnimation
//!@brief	2Dスプライトをアニメーションさせる
//---------------------------------------------------------------------
class SpriteAnimation : public Component
{
public:
	SpriteAnimation(const std::string& path);
public:
	void Initialize() override;
	void UpDate() override;
	void Render2D() override;
private:
	void Render3D() override;
public:
	void	LoadAnimation(const Math::Vector2& chipNum,const Math::Box2D& chip,const int animSpeed);
	void	ChangeAnimation(const Math::Vector2& chipNum, const Math::Box2D& chip, const int animSpeed);
	void	SetChipNumber(const Math::Vector2& chipNum);
	void	SetIsCenterFlag(const bool isCenterFlag);
	void	SetColor(const Math::Color& color);
	void	SetDraw(const Math::Vector2& pos,const Math::Vector2& drawSize);
public:
	void	Play();
	void	Stop();
	void	Reset();
	void	DrawOn();
	void	DrawOff();
public:
	bool	IsEndChipNum();
private:
	void	Animation();
private:
	Sprite2D		sprite;
	SpriteAnimData	animData;
	Math::Vector2	drawSize;
};