/*
  stage01.c 

  Notice: <<<...>>> is same comment in Japanese (SHIFT JIS code).
*/

#include <assert.h>
#include <nusys.h>
#include "main.h"
#include "graphic.h"

/* Angle of rotation of square */
/* <<< 正方形の回転角度 >>> */
static float theta;

void shadetri(Dynamic* dynamicp);


/* Initialize Stage 1 */
/* <<< ステージ１の初期化 >>> */
void initStage01(void)
{
  theta = 0.0;
}


/* Create display list for Stage 1 and start task */
/* <<< ステージ１用ディスプレイリストを作り、タスクを起動 >>> */
void makeDL01(void)
{
  Dynamic* dynamicp;

  /* Display list buffer settings */
  /* <<< ディスプレイリストバッファの指定 >>> */
  dynamicp = &gfx_dynamic[gfx_gtask_no];
  glistp = &gfx_glist[gfx_gtask_no][0];

  /* Initialize RCP */
  /* <<< RCPの初期化 >>> */
  gfxRCPInit();

  /* projection,modeling matrix set */
  guOrtho(&dynamicp->projection,
	  -(float)SCREEN_WD/2.0F, (float)SCREEN_WD/2.0F,
	  -(float)SCREEN_HT/2.0F, (float)SCREEN_HT/2.0F,
	  1.0F, 10.0F, 1.0F);
  guRotate(&dynamicp->modeling, theta, 0.0F, 0.0F, 1.0F);
  guTranslate(&dynamicp->translate, 0.0F, 0.0F, 0.0F);

  /* Draw a square */
  /* <<< 正方形を描く >>> */
  shadetri(dynamicp);

  gDPFullSync(glistp++);
  gSPEndDisplayList(glistp++);

  assert((glistp - gfx_glist[gfx_gtask_no]) < GFX_GLIST_LEN);

  /* Start task, and swap display buffer */
  /* <<< タスクを起動し、表示バッファを切り替えます。 >>> */
  nuGfxTaskStart(&gfx_glist[gfx_gtask_no][0],
		 (s32)(glistp - gfx_glist[gfx_gtask_no]) * sizeof (Gfx),
		 NU_GFX_UCODE_F3DEX , NU_SC_NOSWAPBUFFER);

  /* Change text display position */
  /* <<< 文字表示位置の変更 >>> */
  nuDebConTextPos(0,11,5);
  /* Display text */
  /* <<< 文字の表示 >>> */
  nuDebConCPuts(0, "Stage 1 : A & B");
  /* Draw text to frame buffer */
  /* <<< 文字をフレームバッファに描画 >>> */
  nuDebConDisp(NU_SC_SWAPBUFFER);

  /* Swap display list buffer */
  /* <<< ディスプレイリストバッファの切り替え >>> */
  gfx_gtask_no ^= 1;

  glistp = &gfx_clear_glist[gfx_gtask_no][0];

  /* Initialize RCP */
  /* <<< RCPの初期化 >>> */
  gfxRCPInit();

  /* Clear frame buffer and Z buffer */
  /* <<< フレームバッファとＺバッファのクリア >>> */
  gfxClearCfb();

  assert((glistp - gfx_clear_glist[gfx_gtask_no]) < GFX_CLEAR_GLIST_LEN);

  gDPFullSync(glistp++);
  gSPEndDisplayList(glistp++);

  /* Start task, and swap display buffer */
  /* <<< タスクを起動し、表示バッファを切り替えます。 >>> */
  nuGfxTaskStart(&gfx_clear_glist[gfx_gtask_no][0],
		 (s32)(glistp - gfx_clear_glist[gfx_gtask_no]) * sizeof (Gfx),
		 NU_GFX_UCODE_F3DEX , NU_SC_NOSWAPBUFFER);
}


/* Advance game process for Stage 1 */
/* <<< ステージ１用のゲーム進行処理 >>> */
void updateGame01(void)
{  
  static float vel = 1.0;

  /* Read Controller 1 data */
  /* <<< コントローラ１のデータ読取り >>> */
  nuContDataGetEx(contdata,0);

  /* Rotate backwards with A button */
  /* <<< Ａボタンで逆回転 >>> */
  if(contdata[0].trigger & A_BUTTON)
    vel = -vel;

  /* Accelerate rotation while B button is being pressed */
  /* <<< Ｂボタンを押している間、速く回転 >>> */
  if(contdata[0].button & B_BUTTON)
    theta += vel * 3.0;
  else
    theta += vel;

  /* Move to Stage 1 after pressing Start button */
  /* <<< スタートボタンが押されたら、ステージ０に移行 >>> */
  if(contdata[0].trigger & START_BUTTON)
    {
      /* Remove callback function */
      /* <<< コールバック関数を取り除く。 >>> */
      nuGfxFuncRemove();
      /* Indicate next stage to Main */
      /* <<< 次のステージをメインに指示 >>> */
      stage = 0;
    }
}
