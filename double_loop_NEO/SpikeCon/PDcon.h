#ifndef ___CLASS_PDCON
#define ___CLASS_PDCON	// インクルードカード

#include "GyroSensor.h"
#include "ColorSensor.h"

class PDcon {
private:
    static ev3api::GyroSensor PDgyro;
    static ev3api::ColorSensor PDcolor;

    enum eRun { STRAIGHT, LINETRACE, };

    int mthreathold;
    int mdiff;
    int mold_diff;
    float mPgain;
    float mDgain;
    int mP_value;
    int mD_value;
    int mturn;
    unsigned char mRunmethod;
    bool angle_reset;

public:
    PDcon(unsigned char runmethod, int threathold, float Pgain, float Dgain);
    ~PDcon();
    int getTurn();
    void calcTurn();
    void calcP();
    void calcD();
};

#endif // ___CLASS_PDCON
