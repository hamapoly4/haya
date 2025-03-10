#include "ColorJudgeMent.h"
#include <stdio.h>

ColorJudgeMent::ColorJudgeMent(unsigned char target_color)
	: mtarget_color(target_color)
{
	mColorDetect = new ColorDetect;
}

ColorJudgeMent::~ColorJudgeMent()
{
	delete mColorDetect;
}

bool ColorJudgeMent::judge()
{
	mcurrent_color = mColorDetect->getColor();

	if (mcurrent_color == mtarget_color)
	{
		return true;
	}

	return false;
}
