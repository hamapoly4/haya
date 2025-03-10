#include "RotateRun.h"
#include <stdio.h>

RotateRun::RotateRun(unsigned char rota, int pwm)
	: mrota(rota), Run(pwm)
{
	;
}

RotateRun::~RotateRun()
{
	;
}

void RotateRun::run()
{
	if (mrota == RIGHT)
	{
		LeftMotor.setPWM(+mfix_pwm);
		RightMotor.setPWM(-mfix_pwm);
	}
	else if (mrota == LEFT)
	{
		LeftMotor.setPWM(-mfix_pwm);
		RightMotor.setPWM(+mfix_pwm);
	}
	//printf("Rotation Run!!\n");
	//printf("pwm is %d\n", mfix_pwm);
}
