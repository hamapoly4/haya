#include "RunDistDetect.h"
#include <stdio.h>

using namespace ev3api;

Motor RunDistDetect::LeftMotorEncoder(PORT_C);
Motor RunDistDetect::RightMotorEncoder(PORT_B);

RunDistDetect::RunDistDetect(unsigned char tire)
    : mtire(tire), mold_left_cnt(0), mold_right_cnt(0),
      mleft_sum(0), mright_sum(0), count_reset(true)
{
    ;
    //printf("RunDistDetectクラスのコンストラクタ\n");
    //printf("mold_left_cnt : %d\n", mold_left_cnt);
    //printf("mold_right_cnt : %d\n", mold_right_cnt);
}

RunDistDetect::~RunDistDetect()
{
    ;
}

float RunDistDetect::getRunDist()
{
    if (count_reset == true)
    {
        LeftMotorEncoder.setCount(0);
        RightMotorEncoder.setCount(0);
        count_reset = false;
        return 0;
    }
    
    measureRunDist();
    //printf("RunDistDetect::getRunDist関数におけるmrun_distの値：%f\n", mrun_dist);
    return mrun_dist;
}

void RunDistDetect::measureRunDist()
{
    if (mtire == RIGHT)
    {
        mright_cnt = RightMotorEncoder.getCount();
        mright_sum += mright_cnt - mold_right_cnt;
        mrun_dist = mright_sum * mANGLE1DIST;
        
        mold_right_cnt = mright_cnt;
    }
    else if (mtire == LEFT)
    {
        mleft_cnt = LeftMotorEncoder.getCount();
        mleft_sum += mleft_cnt - mold_left_cnt;
        mrun_dist = mleft_sum * mANGLE1DIST;

        mold_left_cnt = mleft_cnt;
    }
    else if (mtire == BOTH)
    {
        //printf("mtire is BOTH\n");
        mright_cnt = RightMotorEncoder.getCount();
        mleft_cnt = LeftMotorEncoder.getCount();
        //printf("mright_cnt : %d\n", mright_cnt);
        //printf("mleft_cnt  : %d\n", mleft_cnt);

        mright_sum += mright_cnt - mold_right_cnt;
        mleft_sum += mleft_cnt - mold_left_cnt;
        //printf("mright_sum : %f\n", mright_sum);
        //printf("mleft_sum  : %f\n", mleft_sum);

        mrun_dist = (mright_sum + mleft_sum) * mANGLE1DIST / 2.0;
        //printf("mrun_dist : %f\n", mrun_dist);

        mold_right_cnt = mright_cnt;
        mold_left_cnt = mleft_cnt;
        //printf("mold_right_cnt : %d\n", mold_right_cnt);
        //printf("mold_left_cnt : %d\n", mold_left_cnt);
    }
}
