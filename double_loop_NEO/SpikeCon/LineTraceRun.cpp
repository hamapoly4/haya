#include "LineTraceRun.h"
#include <stdio.h>

LineTraceRun::LineTraceRun(unsigned char edge, int pwm)
	: medge(edge), Run(pwm)
{
	mPDcon = new PDcon(mLINETRACE, 69, 0.50, 2);
}

LineTraceRun::~LineTraceRun()
{
	delete mPDcon;
}

void LineTraceRun::run()
{
	mturn = mPDcon->getTurn();
	if (medge == RIGHT)
	{
		LeftMotor.setPWM(mfix_pwm - mturn);
		RightMotor.setPWM(mfix_pwm + mturn);
	}
	else if (medge == LEFT)
	{
		LeftMotor.setPWM(mfix_pwm + mturn);
		RightMotor.setPWM(mfix_pwm - mturn);
	}
	//printf("LineTrace Run!!\n");
	//printf("pwm is %d\n", mfix_pwm);

}
