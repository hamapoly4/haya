/******************************************************************************
 *  ファイル名：app.cpp
 *　　　　内容：タスクであるmain_taskの実施
 *  　　作成日：2024/8/3
 *  　　作成者：近藤　悠太
 *****************************************************************************/

#include "app.h"
#include "Runner.h"

#include "ColorSensor.h"
#include "SonarSensor.h"
#include "GyroSensor.h"
#include "Motor.h"

/* 名前空間ev3apiを使用する */
using namespace ev3api;

/*----------------------------
* オブジェクトを静的に確保する
*-----------------------------*/
ColorSensor gColorSensor(PORT_2);
SonarSensor gSonarSensor(PORT_3);
GyroSensor  gGyroSensor(PORT_4);
Motor       gLeftWheel(PORT_C);
Motor       gRightWheel(PORT_B);

CalcPID gCalcPID(gColorSensor);
LineTracer gLineTracer(gLeftWheel, gRightWheel);
Runner gRunner(gSonarSensor, gGyroSensor, gCalcPID, gLineTracer);


int Botlle_flg = 0;
int distance  = gSonarSensor.getDistance();

/*----------------------------------------------------
*                      内部結合
*-----------------------------------------------------*/
namespace {
    /* システムの破棄 */
    void user_system_destroy()
    {
        /* 左右のモータをリセット */
        gLeftWheel.reset();
        gRightWheel.reset();
    }
}

/*----------------------------------------------------
*                    メインタスク
*-----------------------------------------------------*/
void main_task(intptr_t unused)
{
    /* 周期ハンドラ開始 */
    sta_cyc(CYC_RUNNER);

    slp_tsk();  /* メインタスクの起床待ち */

    /* 周期ハンドラ停止 */
    stp_cyc(CYC_RUNNER);

    user_system_destroy();  /* 終了処理 */

    ext_tsk();  /* タスクの終了 */
}

/*----------------------------------------------------
*                    ランナータスク
*-----------------------------------------------------*/
void runner_task(intptr_t exinf)
{
    
    int Brightness;
    
    
    /*ラージハブの右ボタンが押下されたら判定 */
    if (ev3_button_is_pressed(RIGHT_BUTTON))
    {
        wup_tsk(MAIN_TASK);     // メインタスクの起床
    }
    else if (Brightness >= 27 && Brightness <= 30)
    {
            printf("Brightness = %d\n",gColorSensor.getBrightness());
            
            Brightness = gColorSensor.getBrightness();
            
            if(27 <= Brightness && Brightness <= 30)
            {
                
                
                if(distance <= 27)
                {
                    Botlle_flg = true;
                }
            }
    }
    else
        gRunner.runL();

    ext_tsk();
}


void Botlle_tsk()
{
    if(Botlle_flg == false)
    {
        gLeftWheel.setPWM(30);
        gRightWheel.setPWM(10);
        if(distance <= 27)
        {
            Botlle_flg = true;
        }
        
    }
    else if(Botlle_flg == true)
    {
        gLeftWheel.setPWM(15);
        gRightWheel.setPWM(15);
        if(distance <= 2)
        {
                gLeftWheel.setPWM(25);
                gRightWheel.setPWM(15);    
        }
    }
}
