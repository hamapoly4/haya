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
#include "ColorDetect.h"
#include "RunDistDetect.h"

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
RunDistDetect gRunDistDetectRight(0);
RunDistDetect gRunDistDetectLeft(1);
RunDistDetect gRunDistDetect(2);
ColorDetect gColorDetect;
void        carry_tsk();
void        carry_botlle();
void        morter_stop();
void        line_tsk();
void        end_tsk();

CalcPID gCalcPID(gColorSensor);
LineTracer gLineTracer(gLeftWheel, gRightWheel);
Runner gRunner(gSonarSensor, gGyroSensor, gCalcPID, gLineTracer);
int gColor = 5;


int Botlle_flg = 0;
int distance  = 0;

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
    
    
    gColor = gColorDetect.getColor();
    distance = gSonarSensor.getDistance();
   
            
    /*ラージハブの右ボタンが押下されたら判定 */
    if (ev3_button_is_pressed(RIGHT_BUTTON))
    {
        wup_tsk(MAIN_TASK);     // メインタスクの起床
    }
    else if(gColor == 1 && Botlle_flg == 0)
    {
        carry_tsk();
    }
    else
    {
        gRunner.runL();
    }
    ext_tsk();
}

void carry_tsk()
{
    while(1)
    {
            printf("Blue now \n");
            gRightWheel.setPWM(38);
            gLeftWheel.setPWM(35);
            Botlle_flg = 1;
            if(gRunDistDetectRight.getRunDist() >= 147)
            {
                gRunDistDetectRight.count_reset = true;
                carry_botlle();
            }
    }      
}

void carry_botlle()
{
    int carry_flg = true;
    int run_flg = true;
  
     while(1)   
     {
        printf("Red \n");
        gColor = gColorDetect.getColor();   
        while(gColor == 2 && carry_flg == true)
        {
            gRightWheel.setPWM(-35);
            gLeftWheel.setPWM(48);
            //printf("kondo\n");

            if(gRunDistDetectLeft.getRunDist() >= 150)
            {
                gRunDistDetectLeft.count_reset = true;

               while(run_flg == true)
               { 
                    //printf("White \n");
                    gLeftWheel.setPWM(50);
                    gRightWheel.setPWM(50);
                    if(gRunDistDetect.getRunDist() >= 950)
                    {
                        gRunDistDetect.count_reset = true;
                        carry_flg = false;  
                        printf("yuuta\n");
                        morter_stop();
                    }
                }
                break;
            }
        }  
}

}

void morter_stop()
{

    
        printf("asuka\n");
     
    while(1)
    {
        gLeftWheel.setPWM(-50);
        gRightWheel.setPWM(-50);
        if(gRunDistDetectLeft.getRunDist() <= -300)
        {
            gRunDistDetectLeft.count_reset = true;
            line_tsk();
        }
    }
   

}

void line_tsk()
{
    while(1)
    {
       // printf("tenten\n"); 
        gLeftWheel.setPWM(-35);
        gRightWheel.setPWM(48); 
        if(gRunDistDetectRight.getRunDist() >= 80)
        {
            gRunDistDetectRight.count_reset = true;
                      
            while(1)
            {
                 //   printf("saitou\n"); 
                    gLeftWheel.setPWM(40);
                    gRightWheel.setPWM(40);
                    gColor = gColorDetect.getColor();
                    if(gColor == 0)
                    {
                        gRunDistDetectRight.count_reset = true;
                        end_tsk();
                    }
                    
            }
        }
    }
    
}

void end_tsk()
{
    printf("konkon\n"); 
    while(1)
    {
           
        gRightWheel.setPWM(45);
        gLeftWheel.setPWM(-35);
        if(gRunDistDetectRight.getRunDist() >= 125)
        {
            gRightWheel.setPWM(35);
            gLeftWheel.setPWM(35);
            gRunDistDetectRight.count_reset = true;
            while(1)
            {
                gColor = gColorDetect.getColor();


                if(gRunDistDetectRight.getRunDist() >= 450)
                { 
                          

                   while(1)
                   {
                        gRightWheel.stop();
                        gLeftWheel.stop();       
                    }    
                
                } 
                else if(gColor == 0)
                {
                    printf("BLACK\n");
                    gRightWheel.setPWM(35);
                    gLeftWheel.setPWM(43); 
                    
                }
             }
            }
        }
}
    


