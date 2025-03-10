#include "app_Line.h"

/* マクロ定義 */
#define MOTOR_POWER     45 // モーターの出力値(-100 ~ +100)
#define PID_TARGET_VAL  40  // PID制御におけるセンサrgb.rの目標値 *参考 : https://qiita.com/pulmaster2/items/fba5899a24912517d0c5

/* グローバル変数 */
static const sensor_port_t
    color_sensor    = EV3_PORT_2;

/* 構造体 */
typedef enum {
    START,
    MOVE,
    Straight,
    Straight2,
    Ellipse,
    smallcircle,
    EIGHT,
    EIGHT2,
    Ellipse2,
    END
    } RUN_STATE;

static RUN_STATE r_state = START;

/*************************************************************************************************************************************************/

//以下測定色を返却コピペ用
//colorid_t ev3_color_sensor_get_color 	( 	color_sensor	);

/*************************************************************************************************************************************************/

/* メイン関数 */
void Line_task()
{
    /* ローカル変数 ******************************************************************************************/
    rgb_raw_t rgb;

    int temp = 0.0;   // 距離、方位の一時保存用
    int8_t flag = 0;
    int8_t power = MOTOR_POWER;

    int16_t turn = 0;

    /* 初期化処理 ********************************************************************************************/
    // 別ソースコード内の計測用static変数を初期化する(初期化を行わないことで、以前の区間から値を引き継ぐことができる)
    Distance_init();    // 距離を初期化
    Direction_init();   // 方位を初期化

    Run_init();         // 走行時間を初期化
    Run_PID_init();     // PIDの値を初期化

    /**
    * Main loop ****************************************************************************************************************************************
    */
    while(1)
    {
        /* 値の更新 **********************************************************************************************/
        // 周期ハンドラによる取得値も利用できるが、精度を求める場合は使用直前に値を更新した方が良いと思われる
        ev3_color_sensor_get_rgb_raw(color_sensor, &rgb);   // RGB値を更新
        /********************************************************************************************************/

        if(flag == 1)   // 終了フラグを確認
            return;     // 関数終了

        switch(r_state)
        {
            case START: // スタート後の走行処理 *****************************************************
                r_state = MOVE;

                break;

            case MOVE: // 通常走行 *****************************************************************
                turn = -Run_getTurn_sensorPID(rgb.r, PID_TARGET_VAL);    // PID制御で旋回量を算出

                motor_ctrl(power,turn);

               /* if(-50 < turn && turn < 50)             // 旋回量が少ない場合
                    motor_ctrl_alt(power, turn, 0.5);       // 加速して走行
                else                                    // 旋回量が多い場合
                    motor_ctrl_alt(70, turn, 0.5);          // 減速して走行
*/

                //Run_setDirection(100,100,90);

                if( Distance_getDistance() > 5100 && rgb.r > 30  && rgb.g > 40 && rgb.b > 55)    // 1つ目の青ラインを検知
                {
                    temp = Distance_getDistance();  // 検知時点でのdistanceを仮置き
                    log_stamp("\n\n\tColor detected\n\n\n");
                    motor_ctrl(-40,37);
                    tslp_tsk(450 * 1000U);
                    power = 40;
                    r_state = Straight;
                }

                break;

           case Straight:
                turn = -Run_getTurn_sensorPID(rgb.r, PID_TARGET_VAL);
                motor_ctrl(power, turn);

                if( Distance_getDistance() >= temp + 1300 && rgb.r > 50  && rgb.g > 70 && rgb.b > 60)     // 2つ目の青ライン付近で曲げる
                //if( Distance_getDistance() >= temp + 1720)     // 2つ目の青ライン付近で曲げる
                {
                    log_stamp("\n\n\tColor detected2\n\n\n");

                    //motor_ctrl(33,-37);
                    //tslp_tsk(650 * 1000U);

                    power = 30;
                    temp = Distance_getDistance();
                    r_state = Straight2;
                    //r_state = Ellipse;
                }

                break;

            case Straight2:
                turn = -Run_getTurn_sensorPID(rgb.r, PID_TARGET_VAL);
                motor_ctrl(power, turn);

                if( Distance_getDistance() >= temp + 123 && rgb.r > 30  && rgb.g > 20 && rgb.b > 20)     // 2つ目の青ライン付近で曲げる
                {
                    log_stamp("\n\n\tColor detected3\n\n\n");

                    //motor_ctrl(33,-37);
                    //tslp_tsk(650 * 1000U);

                    power = 30;
                    temp = Distance_getDistance();
                    r_state = smallcircle;
                }

                break;    

            case smallcircle:
                turn = -Run_getTurn_sensorPID(rgb.r, PID_TARGET_VAL);
                motor_ctrl(power, turn);

                if( Distance_getDistance() >= temp + 125)     // 2つ目の青ライン付近で曲げる
                {
                    log_stamp("\n\n\tColor detected4\n\n\n");

                    motor_ctrl(-33,-38);
                    tslp_tsk(670 * 1000U);

                    power = 25;
                    temp = Distance_getDistance();
                    r_state = Ellipse;
                }

                break;        

            case Ellipse:
                turn = Run_getTurn_sensorPID2(rgb.r, PID_TARGET_VAL, 1.12, 0.10, 0.95);

                //if(rgb.r < 75 && rgb.g < 95 && rgb.b > 120)
                //
                //if(Distance_getDistance() > temp + 1100)    // 2つ目の青ラインを検知 (&& rgb.r > 70  && rgb.g > 100 && rgb.b > 80)
                if( Distance_getDistance() >= temp + 1420 && rgb.r < 35  && rgb.g < 40 && rgb.b < 30)     // 1つ目の青ラインを検知
                {
                /*if(Distance_getDistance() >= temp + 1)
                {
                    motor_ctrl(15,-200);         //90°方向転換（時計回り）
                    tslp_tsk(450 * 1000U);
                    motor_ctrl(0,0);
                    tslp_tsk(915 * 1000U);
                    
                    motor_ctrl(40,0);
                    tslp_tsk(1100 * 1000U);

                    motor_ctrl(15,-200);         //90°方向転換（時計回り）
                    tslp_tsk(750 * 1000U);
                    motor_ctrl(0,0);
                    tslp_tsk(915 * 1000U);

                    motor_ctrl(40,0);
                    tslp_tsk(1200 * 1000U);

                    motor_ctrl(15,-200);         //90°方向転換（時計回り）
                    tslp_tsk(850 * 1000U);
                    motor_ctrl(0,0);
                    tslp_tsk(915 * 1000U);
                    
                    motor_ctrl(40,0);
                    tslp_tsk(1300 * 1000U);
                    
                    motor_ctrl(15,-200);         //90°方向転換（時計回り）
                    tslp_tsk(850 * 1000U);
                    motor_ctrl(0,0);
                    tslp_tsk(915 * 1000U);*/
                    

                    log_stamp("\n\n\t Color detected5\n\n\n");
                    motor_ctrl(0,0);
                    tslp_tsk(1500 * 1000U);
                    motor_ctrl(-15,200);         
                    tslp_tsk(250 * 1000U);
                    motor_ctrl(0,0);
                    tslp_tsk(915 * 1000U);
    
                    motor_ctrl(-25,0);
                    tslp_tsk(3650 * 1000U);
                    motor_ctrl(0,0);
                    tslp_tsk(1500 * 1000U);

                    motor_ctrl(-15,200);         //90°方向転換（時計回り）
                    tslp_tsk(1190 * 1000U);
                    motor_ctrl(0,0);
                    tslp_tsk(915 * 1000U);

                    motor_ctrl(-25,0);
                    tslp_tsk(5500 * 1000U);
                    motor_ctrl(0,0);
                    tslp_tsk(1500 * 1000U); 

                    motor_ctrl(-15,200);         //70°くらい方向転換（時計回り）
                    tslp_tsk(685 * 1000U);
                    motor_ctrl(0,0);
                    tslp_tsk(930 * 1000U);


                    //motor_ctrl(20,0);         //90°方向転換（時計回り）
                    //tslp_tsk(1000 * 1000U);
                    power = 20;
                    temp = Distance_getDistance();
                    r_state = END;
                }
                motor_ctrl(power,turn);

                break;

            /*case Ellipse2:
                turn = -Run_getTurn_sensorPID(rgb.r, PID_TARGET_VAL);

                if( Distance_getDistance() >= temp + 1)     // 1つ目の青ラインを検知
                {
                    log_stamp("\n\n\tBlue detected\n\n\n");    
                    motor_ctrl(40,18);
                    tslp_tsk(1500 * 1000U);                
                    power = 33;
                    temp = Distance_getDistance();
                    r_state = EIGHT2;
                }
                motor_ctrl(power,turn);

                break;
    
*/

            /*case EIGHT2:
                turn = Run_getTurn_sensorPID(rgb.r, PID_TARGET_VAL);

                if(Distance_getDistance() > temp + 1700)    // 1つ目の青ラインを検知
                {
                    log_stamp("\n\n\tBlue detected3\n\n\n");
                    motor_ctrl(50,-40);
                    tslp_tsk(200 * 1000U);

                    power = 40;
                    temp = Distance_getDistance();
                    r_state = EIGHT2;
                }
                motor_ctrl(power, turn);
                break;

            */
            /*case EIGHT2:
                turn = -Run_getTurn_sensorPID(rgb.r, PID_TARGET_VAL);
                if(Distance_getDistance() > temp + 1700 )
                {
                    motor_ctrl(52,26);
                    tslp_tsk(1000 * 1000U);
                    power = 43;
                    r_state = END;
                }
                motor_ctrl(power,turn);                
                break;*/

            /*case Ellipse2:
                turn = Run_getTurn_sensorPID(rgb.r, PID_TARGET_VAL);
                motor_ctrl(power,turn);

                break; 
            */
            case END: // 青ラインを検知したら減速 **************************************************
                turn = Run_getTurn_sensorPID2(rgb.r, PID_TARGET_VAL,0.85,0.45,0.09);
                motor_ctrl(power, turn);

                if(Distance_getDistance() > temp + 800 && rgb.r > 120  && rgb.g > 55 && rgb.b < 30)   // 指定距離進むまで
            {
                    //power = Run_getPower_change(power, 30, 1);  // 指定出力になるように減速
                    //else                        // 減速が終了
                    //flag = 1;               // メインループ終了フラグ
                    log_stamp("\n\n\t Color detected6\n\n\n");
                    motor_ctrl(0,0);
                    tslp_tsk(1500 * 1000U);
            }

                turn = Run_getTurn_sensorPID(rgb.r, PID_TARGET_VAL);
                motor_ctrl(power, turn);    // PID制御で走行
                //
                //if(-50 < turn && turn < 50)             // 旋回量が少ない場合
                //    motor_ctrl_alt(power, turn, 0.5);       // 加速して走行
                //else                                    // 旋回量が多い場合
                //    motor_ctrl_alt(15, turn, 0.5);          // 減速して走行

                break;

            default: // **************************************************************************
                break;
        }
        tslp_tsk(4 * 1000U); /* 4msec周期起動 */
    }
    /**
    * Main loop END ************************************************************************************************************************************
    */

                /*    motor_ctrl(15,200);         //90°方向転換（時計回り）
                    tslp_tsk(913 * 1000U);
                    motor_ctrl(0,0);
                    tslp_tsk(915 * 1000U);*/
}
