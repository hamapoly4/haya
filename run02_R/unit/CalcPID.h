/******************************************************************************
 *  ファイル名：CalcPID.h
 *　　　　内容：CalcPIDクラスの定義
 *  　　作成日：2024/8/3
 *  　　作成者：近藤　悠太
 *****************************************************************************/

#ifndef EV3_APP_CALCPID_H_
#define EV3_APP_CALCPID_H_

/* ヘッダファイルのインクルード */
#include "ColorSensor.h"

class CalcPID {
private:
    /* constメンバオブジェクトの定義 */
    const ev3api::ColorSensor& mColorSensor;

    /* 静的const付きメンバ定数の宣言 */
    static const float KP;      // Pゲイン
    static const float KI;      // Iゲイン
    static const float KD;      // Dゲイン
    static const int TARGET;    // 目標値

    /* メンバ変数宣言 */
    int p_value;    // P制御から求めた値
    int i_value;    // I制御から求めた値
    int d_value;    // D制御から求めた値
    int turn;       // 制御値
    int diff;       // 偏差

public:
    /* コンストラクタ宣言 */
    CalcPID(const ev3api::ColorSensor& colorsensor);

    /* メンバ関数宣言 */
    int calcP();    // P演算
    int calcI();    // I演算
    int calcD();    // D演算
    int calcPID();   // PID制御から制御値を求める

};

#endif  // EV3_APP_CALCPID_H_
