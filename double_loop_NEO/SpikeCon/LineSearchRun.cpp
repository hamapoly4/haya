#include "LineSearchRun.h"
#include <stdio.h>

LineSearchRun::LineSearchRun(int pwm)
	: Run(pwm)
{
	;
}

LineSearchRun::~LineSearchRun()
{
	;
}

void LineSearchRun::run()
{
	LeftMotor.setPWM(mfix_pwm);
	RightMotor.setPWM(mfix_pwm);
}
