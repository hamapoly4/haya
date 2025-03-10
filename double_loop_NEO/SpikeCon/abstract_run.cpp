#include "abstract_run.h"
#include <stdio.h>

using namespace ev3api;

Motor Run::LeftMotor(PORT_C);
Motor Run::RightMotor(PORT_B);

Run::Run(int pwm)
	: mfix_pwm(pwm)
{
	;
}

Run::~Run()
{
	LeftMotor.stop();
	RightMotor.stop();
	printf("左右のモータを停止した！！\n");
}
