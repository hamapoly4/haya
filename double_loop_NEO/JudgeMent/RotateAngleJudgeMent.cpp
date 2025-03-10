#include "RotateAngleJudgeMent.h"
#include <stdio.h>

using namespace ev3api;

GyroSensor RotateAngleJudgeMent::mGyroSensor(PORT_4);

RotateAngleJudgeMent::RotateAngleJudgeMent(unsigned char rota, int target_angle)
	: mrota(rota), mtarget_angle(target_angle), angle_reset(true)
{
	;
}

RotateAngleJudgeMent::~RotateAngleJudgeMent()
{
	;
}

bool RotateAngleJudgeMent::judge()
{
	mcurrent_angle = mGyroSensor.getAngle();
	if (angle_reset == true)
	{
		mGyroSensor.reset();
		printf("mcurrent_angle : %d\n", mcurrent_angle);
		printf("mtarget_angle : %d\n", mtarget_angle);
		angle_reset = false;
		return false;
	}
	
	if (mcurrent_angle >= (mtarget_angle + 10))
	{
		printf("mcurrent_angle is over mtarget_angle!!\n");
		printf("So return!!\n");
		return false;
	}

	if (mrota == RIGHT)
	{
		printf("右旋回角度：%d度\n", mcurrent_angle);
		if (mcurrent_angle >= mtarget_angle)
		{
			return true;
		}
	}
	else if (mrota == LEFT)
	{
		printf("左旋回角度：%d度\n", mcurrent_angle);
		if (mcurrent_angle <= mtarget_angle)
		{
			return true;
		}
	}

	return false;
}
