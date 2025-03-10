#include "RunDistJudgeMent.h"
#include <stdio.h>

RunDistJudgeMent::RunDistJudgeMent(unsigned char tire, float target_dist)
	: mtire(tire), mtarget_dist(target_dist)
{
	mRunDistDetect = new RunDistDetect(mtire);
}

RunDistJudgeMent::~RunDistJudgeMent()
{
	delete mRunDistDetect;
}

bool RunDistJudgeMent::judge()
{
	mcurrent_dist = mRunDistDetect->getRunDist();

	if (mcurrent_dist >= mtarget_dist)
	{
		printf("%fmm走った！！\n", mcurrent_dist);
		return true;
	}

	return false;
}
