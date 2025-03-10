/******************************************************************************
 *  ファイル名：app.cpp
 *　　　　内容：タスクであるmain_taskの実施
 *  　　作成日：2024/8/3
 *  　　作成者：近藤　悠太
 *****************************************************************************/
#include <stdio.h>
#include <opencv2/opencv.hpp>



//#ifdef _DEBUG
//#pragma comment(lib, "opencv_world400d.lib")
//#else
//#pragma comment(lib, "opencv_world400.lib")
//#endif

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
using namespace cv;
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

bool flag = true;


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
    
    destroyAllWindows();

    ext_tsk();  /* タスクの終了 */
}

/*----------------------------------------------------
*                    ランナータスク
*-----------------------------------------------------*/
void runner_task(intptr_t exinf)
{
    // カメラを起動（カメラ番号0を指定）
    VideoCapture capture("/dev/video0");
   
            
    /*ラージハブの右ボタンが押下されたら判定 */
    if (ev3_button_is_pressed(RIGHT_BUTTON))
    {
        wup_tsk(MAIN_TASK);     // メインタスクの起床
    }
    else
    {
        carry_tsk();
    }

    capture.release();
    ext_tsk();
}

void carry_tsk()
{   
    ;
}


