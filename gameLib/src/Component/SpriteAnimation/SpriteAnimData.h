#pragma once
#include "../../src/Utility/Counter.hpp"
#include "../../src/DXEngine/Math/Math.h"


struct SpriteAnimData
{
	int		animationSpeed;
	int		sheetWidthNum;
	int		sheetHeightNum;
	int		nowSheetWidthNum;
	int		nowSheetHeightNum;
	bool	isCenter;
	bool	continueFlag;
	bool	drawFlag;
	bool	endChipFlag;
	Math::Vector2	srcOffset;
	Counter_f	animationCounter;
	Math::Box2D	chip;
	Math::Color	color;
};
