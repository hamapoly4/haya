/******************************************************************************
 *  ファイル名：LineTracer.cpp
 *　　　　内容：LineTracerクラスの実施
 *  　　作成日：2024/8/4
 *  　　作成者：近藤　悠太
 *****************************************************************************/

#include "LineTracer.h"

using namespace ev3api;

const int LineTracer::PWM = 45; // 静的const付きメンバ定数の定義

LineTracer::LineTracer(Motor& leftwheel, Motor& rightwheel)
    : mLeftWheel(leftwheel), mRightWheel(rightwheel)
{
    ;
}

void LineTracer::Run(int turn)
{
    mLeftWheel.setPWM(PWM + turn);
    mRightWheel.setPWM(PWM - turn);
}