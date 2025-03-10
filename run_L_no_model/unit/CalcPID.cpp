/******************************************************************************
 *  ファイル名：CalcPID.cpp
 *　　　　内容：CalcPIDクラスの実施
 *  　　作成日：2024/8/3
 *  　　作成者：近藤　悠太
 *****************************************************************************/

#include "CalcPID.h"

using namespace ev3api;

/* 静的const付きメンバ定数の定義 */
const float CalcPID::KP = 0.50;  // Pゲイン
const float CalcPID::KI = 0.025;  // Iゲイン
const float CalcPID::KD = 2;     // Dゲイン
const int CalcPID::TARGET = 69;  // 目標値

/*-------------------------------------------------------
*                  コンストラクタ定義
---------------------------------------------------------*/
CalcPID::CalcPID(const ColorSensor& colorsensor)
    : mColorSensor(colorsensor)
{
    ;
}

/*-------------------------------------------------------
*                   メンバ関数定義
---------------------------------------------------------*/
int CalcPID::calcP()    // P演算
{
    diff = mColorSensor.getBrightness() - TARGET;
    p_value = KP * diff;
    return p_value;
}

int CalcPID::calcI()    // I演算
{
    static int sum = 0;
    static unsigned char i = 0;

    sum += diff;
    i_value = sum * KI;

    i++;
    if (i >= 10)
    {
        sum = 0;
        i = 0;
    }

    return i_value;
}

int CalcPID::calcD()    // D演算
{
    static int old_diff = 0;

    d_value = (diff - old_diff) * KD;
    old_diff = diff;

    return d_value;
}

int CalcPID::calcPID()   // PID制御から制御値を求める
{
    turn = calcP() + calcI() + calcD();
    return turn;
}
