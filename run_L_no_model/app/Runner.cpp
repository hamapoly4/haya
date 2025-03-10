/******************************************************************************
 *  ファイル名：Runner.cpp
 *　　　　内容：Runnerクラスの実施
 *  　　作成日：2024/8/3
 *  　　作成者：近藤　悠太
 *****************************************************************************/

#include "Runner.h"
#include <stdio.h>

using namespace ev3api;

const unsigned char Runner::TARGET = 90;

/*--------------------------------------------------------------------------------------------
*                                   コンストラクタ定義
----------------------------------------------------------------------------------------------*/
Runner::Runner(const SonarSensor& sonarsensor, GyroSensor& gyrosensor,
                        CalcPID& calcpid, LineTracer& linetracer/*, Walker& walker*/)
  : mSonarSensor(sonarsensor), mGyroSensor(gyrosensor),
    mCalcPID(calcpid), mLineTracer(linetracer)/*, mWalker(walker)*/
{
  ;
}

/*-------------------------------------------------------
*                   メンバ関数定義
---------------------------------------------------------*/
/* L字走行をするメンバ関数定義 */
void Runner::runL()
{
  runLineStart();
  /* ライントレース走行を開始するか判定 */
  if (mrunline_flg == false && mrunstra_flg == false)
  {
    return;  // ライントレース走行を開始しない！！
  }
  else if (mrunline_flg == true && mrunstra_flg == false)
  {
    mLineTracer.Run(mCalcPID.calcPID()); // ライントレース走行        /* もっと省略できる！！ */
  }


  runStraStart();
  if (mrunstra_flg == false)
  {
    return; // 直進走行を開始しない！！
  }
  printf("mrunstra_flg is true!!\n");
  wup_tsk(MAIN_TASK);   // メインタスクの起床

}

/* ライントレース走行開始の判断をするメンバ関数定義 */
void Runner::runLineStart()
{
  int16_t sdist; // 超音波センサの距離に関する変数

  sdist = mSonarSensor.getDistance();  // 障害物との距離を取得
  /* 障害物との距離が-1cmより大きく、5cm未満か判定 */
  if (-1 < sdist && sdist < 5)
  {
    mrunline_flg = true;   // ライントレース走行開始フラグを立てる
  }
}

/* 直進走行開始の判断をするメンバ関数定義 */
void Runner::runStraStart()
{
  static unsigned char achi_cnt = 0;  // 目標値に達成した回数
  int16_t yaw_angle;  // ヨー方向の角位置

  if (achi_cnt < 2)
  {
    yaw_angle = mGyroSensor.getAngle();
    if ((TARGET - 5) <= yaw_angle && yaw_angle <= (TARGET + 5))
    {
      mGyroSensor.reset();
      printf("GyroSensor can reset!!\n");
      achi_cnt++;
    }
  }
  else
  {
    mrunline_flg = false;
    mrunstra_flg = true;
  }
}
