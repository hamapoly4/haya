#include "StraRun.h"
#include <stdio.h>

StraRun::StraRun(int pwm)
	: Run(pwm)
{
	mPDcon = new PDcon(mSTRAIGHT, 0, 1.5, 3);
}

StraRun::~StraRun()
{
	delete mPDcon;
}

void StraRun::run()
{
	mturn = mPDcon->getTurn();
	LeftMotor.setPWM(mfix_pwm - mturn);
	RightMotor.setPWM(mfix_pwm + mturn);
	
	//printf("Straight Run!!\n");
	//printf("pwm is %d\n", mfix_pwm);
}
