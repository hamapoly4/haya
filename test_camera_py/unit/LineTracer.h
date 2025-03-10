/******************************************************************************
 *  ファイル名：LineTracer.h
 *　　　　内容：LineTracerクラスの定義
 *  　　作成日：2024/8/4
 *  　　作成者：近藤　悠太
 *****************************************************************************/

#ifndef EV3_APP_LINETRACER_H
#define EV3_APP_LINETRACER_H

#include "Motor.h"

class LineTracer {
private:
    static const int PWM;       // 静的const付きメンバ定数宣言
    ev3api::Motor& mLeftWheel;
    ev3api::Motor& mRightWheel;

public:
    LineTracer(ev3api::Motor& leftwheel, ev3api::Motor& rightwheel);

    void Run(int turn);
};

#endif  // EV3_APP_LINETRACER_H_