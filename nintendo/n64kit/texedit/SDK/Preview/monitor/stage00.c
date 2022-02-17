/*
  stage00.c 

  Notice: <<<...>>> is same comment in Japanese (SHIFT JIS code).
*/

#include <assert.h>
#include <nusys.h>
#include "main.h"
#include "graphic.h"
#include "teapi.h"

/* Display X position */
/* <<< 表示位置Ｘ >>> */
static float triPos_x;
/* Display Y position */
/* <<< 表示位置Ｙ >>> */
static float triPos_y;

void shadetri(Dynamic* dynamicp);

/* Initialize Stage 0 */
/* <<< ステージ０の初期化 >>> */
void initStage00(void)
{
  triPos_x = 0.0;
  triPos_y = 0.0;
#if	1
  teInit();
#endif
}

/* Make display list and start task */
/* <<< ディスプレイリストを作り、タスクを起動 >>> */
void makeDL00(void)
{
  Dynamic* dynamicp;

  /* Display list buffer settings */
  /* <<< ディスプレイリストバッファの指定 >>> */
  dynamicp = &gfx_dynamic[gfx_gtask_no];
  glistp = &gfx_glist[gfx_gtask_no][0];

  /* Initialize RCP */
  /* <<< RCPの初期化 >>> */
  gfxRCPInit();

  /* Clear frame buffer and Z buffer */
  /* <<< フレームバッファとＺバッファのクリア >>> */
  gfxClearCfb();

  /* projection,modeling matrix set */
  guOrtho(&dynamicp->projection,
	  -(float)SCREEN_WD/2.0F, (float)SCREEN_WD/2.0F,
	  -(float)SCREEN_HT/2.0F, (float)SCREEN_HT/2.0F,
	  1.0F, 10.0F, 1.0F);
  guRotate(&dynamicp->modeling, 0.0F, 0.0F, 0.0F, 1.0F);
  guTranslate(&dynamicp->translate, triPos_x, triPos_y, 0.0F);

#if	1
	/* Draw background */
	/* <<< 背景の描画 >>> */
	glistp = teDrawBackground(glistp);
	/* Paste texture on square shape */
	/* <<< 正方形にテクスチャを貼る >>> */
	glistp = teDrawTextures(glistp);
	/* Draw menus */
	/* <<< メニューを描画 >>> */
	glistp = teDrawMenu(glistp, 2, 2);
#else
  /* Draw square */
  /* <<< 正方形を描く >>> */
  shadetri(dynamicp);
#endif

  gDPFullSync(glistp++);
  gSPEndDisplayList(glistp++);

  assert((glistp - gfx_glist[gfx_gtask_no]) < GFX_GLIST_LEN);

  /* Start task, and swap display buffer */
  /* <<< タスクを起動し、表示バッファを切り替えます。 >>> */
	if (teMenu_disp) {
		/* Menu display time */
		/* <<< メニュー表示時 >>> */
		nuGfxTaskStart(&gfx_glist[gfx_gtask_no][0],
			(s32)(glistp - gfx_glist[gfx_gtask_no]) * sizeof (Gfx),
			NU_GFX_UCODE_F3DEX2 , NU_SC_NOSWAPBUFFER);
#if	1
		/* If nothing drawn, SWAPBUFFER not performed? Problem with nusys/os? */
		/* <<< 何か描画されていないとSWAPBUFFERされない？nusys/osの不具合？ >>> */
		/* Change location of text display */
		/* <<< 文字表示位置の変更 >>> */
		nuDebConTextPos(0,0,0);
		/* Display text */
		/* <<< 文字の表示 >>> */
		/* Space and line feed didn't work, so used "'". */
		/* <<< 空白や改行では駄目でしたのでやもえず・・・「'」で。 >>> */
		nuDebConPutc(0, '\'');
#endif
		/* Draw text to frame buffer */
		/* <<< 文字をフレームバッファに描画 >>> */
		nuDebConDisp(NU_SC_NOSWAPBUFFER);
		/* Add to performance meter draw list */
		/* <<< パフォーマンスメーターの描画リストの追加 >>> */
		nuDebTaskPerfBar1(1, 200, NU_SC_SWAPBUFFER);
	} else {
		/* No menu */
		/* <<< メニュー無し >>> */
		nuGfxTaskStart(&gfx_glist[gfx_gtask_no][0],
			(s32)(glistp - gfx_glist[gfx_gtask_no]) * sizeof (Gfx),
			NU_GFX_UCODE_F3DEX2 , NU_SC_SWAPBUFFER);
	}
  /* Swap display list buffer */
  /* <<< ディスプレイリストバッファの切り替え >>> */
  gfx_gtask_no ^= 1;
}


/* Advance game process for Stage 0 */
/* <<< ステージ０用のゲーム進行処理 >>> */
void updateGame00(void)
{  
  /* Read Controller 1 data */
  /* <<< コントローラ１のデータ読取り >>> */
  nuContDataGetEx(contdata,0);

  /* Change display position according to Control Stick data */
  /* <<< スティックデータにより表示位置を変更する >>> */
  triPos_x = contdata->stick_x;
  triPos_y = contdata->stick_y;
#if	1
  /* Controller-based menu manipulation process */
  /* <<< コントローラーによるメニュー操作処理 >>> */
  teControl(contdata);
#else
  /* Move to Stage 1 after pressing Start button */
  /* <<< スタートボタンが押されたら、ステージ１に移行 >>> */
  if(contdata[0].trigger & START_BUTTON){
    /* Remove callback function */
    /* <<< コールバック関数を取り除く。 >>> */
    nuGfxFuncRemove();
    /* Indicate next stage to Main */
    /* <<< 次のステージをメインに指示 >>> */
    stage = 1;
  }
#endif
}

/* Vertex coordinates */
/* <<< 頂点の座標 >>> */
static Vtx shade_vtx[] =  {
        {        -64,  64, -5, 0, 0, 0, 0, 0xff, 0, 0xff	},
        {         64,  64, -5, 0, 0, 0, 0, 0, 0, 0xff	},
        {         64, -64, -5, 0, 0, 0, 0, 0, 0xff, 0xff	},
        {        -64, -64, -5, 0, 0, 0, 0xff, 0, 0, 0xff	},
};

/* Compose a square */
/* <<< 正方形を書く >>> */
void shadetri(Dynamic* dynamicp)
{
  gSPMatrix(glistp++,OS_K0_TO_PHYSICAL(&(dynamicp->projection)),
		G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);
  gSPMatrix(glistp++,OS_K0_TO_PHYSICAL(&(dynamicp->modeling)),
		G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);
  gSPMatrix(glistp++,OS_K0_TO_PHYSICAL(&(dynamicp->translate)),
		G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

  gSPVertex(glistp++,&(shade_vtx[0]),4, 0);

  gDPPipeSync(glistp++);
  gDPSetCycleType(glistp++,G_CYC_1CYCLE);
  gDPSetRenderMode(glistp++,G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
  gSPClearGeometryMode(glistp++,0xFFFFFFFF);
  gSPSetGeometryMode(glistp++,G_SHADE| G_SHADING_SMOOTH);

  gSP2Triangles(glistp++,0,1,2,0,0,2,3,0);
}

