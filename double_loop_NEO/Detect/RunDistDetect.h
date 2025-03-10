#ifndef ___CLASS_RUNDISTDETECT
#define ___CLASS_RUNDISTDETECT

#include "Motor.h"

class RunDistDetect {
private:
    static constexpr float mANGLE1DIST = 0.87266;

    static ev3api::Motor LeftMotorEncoder;
    static ev3api::Motor RightMotorEncoder;

    enum eTire { RIGHT, LEFT, BOTH, };

    int mleft_cnt;
    int mright_cnt;
    int mold_left_cnt;
    int mold_right_cnt;
    float mleft_sum;
    float mright_sum;
    float mrun_dist;
    unsigned char mtire;
    bool count_reset;

public:
    RunDistDetect(unsigned char tire);
    ~RunDistDetect();
    float getRunDist();
    void measureRunDist();
};

#endif // ___CLASS_RUNDISTDETECT
