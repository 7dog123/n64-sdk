/*
   main.c

   NuSYSTEM sample nu2

  Notice: <<<...>>> is same comment in Japanese (SHIFT JIS code).

 */

#include <nusys.h>
#include "main.h"

/* Stage number */
/* <<< ステージ番号 >>> */
volatile int stage;

/* Declare prototypes */
/* <<< プロトタイプ宣言 >>> */
void stage00(int);
void stage01(int);

/* Declare external functions */
/* <<< 外部関数宣言 >>> */
void initStage00(void);
void makeDL00(void);
void updateGame00(void);

void initStage01(void);
void makeDL01(void);
void updateGame01(void);

/* Read Controller 1 data */
/* <<< １コントローラ読取データ >>> */
NUContData	contdata[1];

/*------------------------
	Main
	<<< メイン >>>
--------------------------*/
void mainproc(void)
{
  /* Initialize graphic */
  /* <<< グラフィックの初期化 >>> */
  nuGfxInit();

  /* Initialize controller manager */
  /* <<< コントローラマネージャの初期化 >>> */
  nuContInit();
	
  /* Set Stage number to 0*/
  /* <<< ステージ番号を０にセットする。>>> */
  stage = 0;

  while(1)
    {
      switch(stage)
	{
	  /* 
	     Register callback function corresponding to stage number.
	     On the callback function side,
	     set value in stage if a change in registration is
	     required in another callback function.
	     */
	  /* <<<
	     ステージ番号により、対応するコールバック関数を登録します。
	     コールバック関数側では、
	     他のコールバック関数に登録変更が必要になった時に、
	     stage に値をセットします。
	     >>> */
	case 0:
	  /* Set a value of -1 in stage in order to wait
	     for the value to be set in the callback function. */
	  /* <<< コールバック関数が値をセットするのを待つために、
	     stage の値を-1にセットしておきます >>>*/
	  stage = -1;
	  /* Initialize Stage 0 */
	  /* <<< ステージ０の初期化 >>> */
	  initStage00();
	  /* Register callback */
	  /* <<< コールバック登録 >>> */
	  nuGfxFuncSet((NUGfxFunc)stage00);
	  /* Start display */
	  /* <<< 表示開始 >>> */
	  nuGfxDisplayOn();
	  break;
	case 1:
	  stage = -1;
	  initStage01();
	  nuGfxFuncSet((NUGfxFunc)stage01);
	  nuGfxDisplayOn();
	  break;
	default:
	  break;
	}
      
      /* Callback function waits for value to change (scene to change) */
      /* <<< コールバック関数が値を切り替えるの（場面切り替え）を待つ >>> */
      while(stage == -1)
	;
      /* Turn off display */
      /* <<< 表示を消す >>> */
      nuGfxDisplayOff();
    }
}


/*-----------------------------------------------------------------------------
  Callback function
  <<< コールバック関数 >>>

  The value of pendingGfx, which is passed from Nusystem as an argument of the 
  callback function, is the sum of the currently processing and waiting to 
  process status of the RCP.
  <<< Nusystem からコールバック関数の引数として渡される pendingGfx は 
   現在処理中および処理待ちの RCPタスクの合計数です。 >>>
-----------------------------------------------------------------------------*/

/* Stage 0 */
/* <<< ステージ０ >>> */
void stage00(int pendingGfx)
{
  /* <<< 処理中／処理待ちのRCPタスクが２つ以下場合、表示処理行う >>> */
  if(pendingGfx < 3)
    makeDL00();		

  /* <<< ゲーム進行処理 >>> */
  updateGame00(); 
}

/* <<< ステージ１ >>> */
void stage01(int pendingGfx)
{
  /* If the processing/waiting to process status of the RCP is 2 or less, perform display process */
  /* <<< 処理中／処理待ちのRCPタスクが２つ以下場合、表示処理行う >>> */
  if(pendingGfx < 3)
    makeDL01();

  /* Advance game process */
  /* <<< ゲーム進行処理 >>> */
  updateGame01();
}
