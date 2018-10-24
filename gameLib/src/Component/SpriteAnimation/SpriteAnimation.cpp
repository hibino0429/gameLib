#include "SpriteAnimation.h"
#include "../../src/Component/Transform/Transform.h"



SpriteAnimation::SpriteAnimation(const std::string& path)
	: sprite(path)
{
	
}

void SpriteAnimation::Initialize()
{
	animData.nowSheetWidthNum = 0;
	animData.nowSheetHeightNum = 0;
	animData.isCenter = false;
	animData.endChipFlag = false;
	animData.continueFlag = true;
	animData.drawFlag = true;
	animData.color = Math::Color(1.0f, 1.0f, 1.0f, 1.0f);
}

void SpriteAnimation::UpDate()
{
	Animation();
}

void SpriteAnimation::Render2D()
{
	if (!animData.drawFlag) { return; }
	if (GetEntity()->HasComponent<Transform>())
	{
		Math::Vector3	position = GetEntity()->GetComponent<Transform>().GetPosition();
		sprite.Draw(Math::Box2D(position.x, position.y, drawSize.x, drawSize.y), animData.chip, animData.isCenter, animData.color);
	}
}

void SpriteAnimation::Render3D()
{
}


void SpriteAnimation::LoadAnimation(const Math::Vector2 & chipNum, const Math::Box2D & chip, const int animSpeed)
{
	ChangeAnimation(chipNum, chip, animSpeed);
}

void SpriteAnimation::ChangeAnimation(const Math::Vector2 & chipNum, const Math::Box2D & chip, const int animSpeed)
{
	animData.sheetWidthNum = static_cast<int>(chipNum.x);
	animData.sheetHeightNum = static_cast<int>(chipNum.y);
	animData.chip = chip;
	animData.srcOffset = Math::Vector2(chip.x, chip.y);
	animData.animationSpeed = animSpeed;
}

void SpriteAnimation::SetChipNumber(const Math::Vector2& chipNum)
{
	animData.nowSheetWidthNum = static_cast<int>(chipNum.x);
	animData.nowSheetHeightNum = static_cast<int>(chipNum.y);
	Stop();
}

void SpriteAnimation::SetIsCenterFlag(const bool isCenterFlag)
{
	animData.isCenter = isCenterFlag;
}

void	SpriteAnimation::SetColor(const Math::Color& color)
{
	animData.color = color;
}

void SpriteAnimation::SetDraw(const Math::Vector2& pos,const Math::Vector2& drawSize)
{
	this->drawSize = drawSize;
	if (GetEntity()->HasComponent<Transform>())
	{
		GetEntity()->GetComponent<Transform>().position = pos;
	}
}

void SpriteAnimation::Play()
{
	animData.continueFlag = true;
}

void SpriteAnimation::Stop()
{
	animData.continueFlag = false;
}

void SpriteAnimation::Reset()
{
	animData.animationCounter.Reset();
}

void SpriteAnimation::DrawOn()
{
	animData.drawFlag = true;
}

void SpriteAnimation::DrawOff()
{
	animData.drawFlag = false;
}

bool SpriteAnimation::IsEndChipNum()
{
	return animData.endChipFlag;
}


void SpriteAnimation::Animation()
{
	animData.endChipFlag = false;
	if (animData.continueFlag)
	{
		animData.animationCounter.Add();
		animData.nowSheetWidthNum = static_cast<int>(animData.animationCounter.GetCurrentCount()) / static_cast<int>(animData.animationSpeed);
	}
	if (animData.nowSheetWidthNum >= animData.sheetWidthNum)
	{
		animData.nowSheetWidthNum = 0;
		++animData.nowSheetHeightNum;
		animData.animationCounter.Reset();
	}
	if (animData.nowSheetHeightNum >= animData.sheetHeightNum)
	{
		animData.nowSheetWidthNum = 0;
		animData.nowSheetHeightNum = 0;
		animData.animationCounter.Reset();
		animData.endChipFlag = true;
	}
	animData.chip = Math::Box2D(
		animData.srcOffset.x + animData.chip.width * animData.nowSheetWidthNum,
		animData.srcOffset.y + animData.chip.height * animData.nowSheetHeightNum,
		animData.chip.width,
		animData.chip.height
	);
}


