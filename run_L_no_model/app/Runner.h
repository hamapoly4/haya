/******************************************************************************
 *  ファイル名：Runner.cpp
 *　　　　内容：Runnerクラスの定義
 *  　　作成日：2024/8/3
 *  　　作成者：近藤　悠太
 *****************************************************************************/

#ifndef EV3_APP_RUNNER_H_
#define EV3_APP_RUNNER_H_

/* ヘッダファイルのインクルード */
#include "SonarSensor.h"
#include "GyroSensor.h"
#include "CalcPID.h"
#include "LineTracer.h"

/*----------------------------------------------------
*                  Runnerクラスの定義
*-----------------------------------------------------*/
class Runner {
private:
    static const unsigned char TARGET;
    const ev3api::SonarSensor& mSonarSensor;    /* 超音波センサのconst参照オブジェクト */
    ev3api::GyroSensor& mGyroSensor;
    CalcPID& mCalcPID;
    LineTracer& mLineTracer;

    /* メンバ変数宣言 */
    unsigned char mrunline_flg = false;     // ライントレース走行開始フラグは降りた状態で定義
    unsigned char mrunstra_flg = false;     // 直進走行開始フラグは降りた状態で定義

public:
    /* コンストラクタ宣言 */
    Runner(const ev3api::SonarSensor& sonarsensor, ev3api::GyroSensor& gyrosensor,
                CalcPID& calcpid, LineTracer& linetracer);

    
    /* L字走行をするメンバ関数宣言 */
    void runL();

    /* ライントレース走行開始の判断をするメンバ関数宣言 */
    void runLineStart();

    /* 直進走行開始の判断をするメンバ関数宣言 */
    void runStraStart();
};

#endif  // EV3_APP_RUNNER_H_
