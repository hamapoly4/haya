/******************************************************************************
 *  ファイル名：app.cpp
 *　　　　内容：タスクであるmain_taskの実施
 *  　　作成日：2024/8/20
 *  　　作成者：近藤　悠太
 *****************************************************************************/

#include "app.h"
#include "Scenario.h"

/*----------------------------------------------------
*                      内部結合
*-----------------------------------------------------*/
namespace {
    /* オブジェクトの定義 */
    Scenario* gScenario;

    /* システムの生成 */
    void system_create()
    {
        /* オブジェクトを動的に確保 */
        gScenario = new Scenario;
    }

    /* システムの破棄 */
    void system_destroy()
    {
        /* 動的なオブジェクトの解放 */
        delete gScenario;
    }
}

/*----------------------------------------------------
*                    メインタスク
*-----------------------------------------------------*/
void main_task(intptr_t unused)
{
    system_create();

    /* 周期ハンドラ開始 */
    sta_cyc(CYC_DOUBLE_LOOP_NEO);

    slp_tsk();  /* メインタスクの起床待ち */

    /* 周期ハンドラ停止 */
    stp_cyc(CYC_DOUBLE_LOOP_NEO);

    system_destroy();  /* 終了処理 */

    ext_tsk();  /* タスクの終了 */
}

void double_loop_NEO_task(intptr_t exinf)
{
    if (gScenario->finish() == true)
    {
        wup_tsk(MAIN_TASK);
    }
    else
    {
        gScenario->run();
    }
}
