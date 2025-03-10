#include "PDcon.h"

using namespace ev3api;

GyroSensor PDcon::PDgyro(PORT_4);
ColorSensor PDcon::PDcolor(PORT_2);

PDcon::PDcon(unsigned char runmethod, int threathold, float Pgain, float Dgain)
    : mRunmethod(runmethod), mthreathold(threathold),
      mPgain(Pgain), mDgain(Dgain), mold_diff(0), angle_reset(true)
{
    ;
}

PDcon::~PDcon()
{
    ;
}

int PDcon::getTurn()
{
    if (angle_reset == true)
    {
        PDgyro.reset();
        angle_reset = false;
        return 0;
    }
    
    calcTurn();
    return mturn;
}

void PDcon::calcTurn()
{
    calcP();
    calcD();
    mturn = mP_value + mD_value;
}

void PDcon::calcP()
{
    if (mRunmethod == STRAIGHT)
    {
        mdiff = PDgyro.getAngle() - mthreathold;
    }
    else if (mRunmethod == LINETRACE)
    {
        mdiff = PDcolor.getBrightness() - mthreathold;
    }

    mP_value = mdiff * mPgain;
}

void PDcon::calcD()
{
    mD_value = (mdiff - mold_diff) * mDgain;
    mold_diff = mdiff;
}
