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
/* <<< �\���ʒu�w >>> */
static float triPos_x;
/* Display Y position */
/* <<< �\���ʒu�x >>> */
static float triPos_y;

void shadetri(Dynamic* dynamicp);

/* Initialize Stage 0 */
/* <<< �X�e�[�W�O�̏����� >>> */
void initStage00(void)
{
  triPos_x = 0.0;
  triPos_y = 0.0;
#if	1
  teInit();
#endif
}

/* Make display list and start task */
/* <<< �f�B�X�v���C���X�g�����A�^�X�N���N�� >>> */
void makeDL00(void)
{
  Dynamic* dynamicp;

  /* Display list buffer settings */
  /* <<< �f�B�X�v���C���X�g�o�b�t�@�̎w�� >>> */
  dynamicp = &gfx_dynamic[gfx_gtask_no];
  glistp = &gfx_glist[gfx_gtask_no][0];

  /* Initialize RCP */
  /* <<< RCP�̏����� >>> */
  gfxRCPInit();

  /* Clear frame buffer and Z buffer */
  /* <<< �t���[���o�b�t�@�Ƃy�o�b�t�@�̃N���A >>> */
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
	/* <<< �w�i�̕`�� >>> */
	glistp = teDrawBackground(glistp);
	/* Paste texture on square shape */
	/* <<< �����`�Ƀe�N�X�`����\�� >>> */
	glistp = teDrawTextures(glistp);
	/* Draw menus */
	/* <<< ���j���[��`�� >>> */
	glistp = teDrawMenu(glistp, 2, 2);
#else
  /* Draw square */
  /* <<< �����`��`�� >>> */
  shadetri(dynamicp);
#endif

  gDPFullSync(glistp++);
  gSPEndDisplayList(glistp++);

  assert((glistp - gfx_glist[gfx_gtask_no]) < GFX_GLIST_LEN);

  /* Start task, and swap display buffer */
  /* <<< �^�X�N���N�����A�\���o�b�t�@��؂�ւ��܂��B >>> */
	if (teMenu_disp) {
		/* Menu display time */
		/* <<< ���j���[�\���� >>> */
		nuGfxTaskStart(&gfx_glist[gfx_gtask_no][0],
			(s32)(glistp - gfx_glist[gfx_gtask_no]) * sizeof (Gfx),
			NU_GFX_UCODE_F3DEX2 , NU_SC_NOSWAPBUFFER);
#if	1
		/* If nothing drawn, SWAPBUFFER not performed? Problem with nusys/os? */
		/* <<< �����`�悳��Ă��Ȃ���SWAPBUFFER����Ȃ��Hnusys/os�̕s��H >>> */
		/* Change location of text display */
		/* <<< �����\���ʒu�̕ύX >>> */
		nuDebConTextPos(0,0,0);
		/* Display text */
		/* <<< �����̕\�� >>> */
		/* Space and line feed didn't work, so used "'". */
		/* <<< �󔒂���s�ł͑ʖڂł����̂ł�������E�E�E�u'�v�ŁB >>> */
		nuDebConPutc(0, '\'');
#endif
		/* Draw text to frame buffer */
		/* <<< �������t���[���o�b�t�@�ɕ`�� >>> */
		nuDebConDisp(NU_SC_NOSWAPBUFFER);
		/* Add to performance meter draw list */
		/* <<< �p�t�H�[�}���X���[�^�[�̕`�惊�X�g�̒ǉ� >>> */
		nuDebTaskPerfBar1(1, 200, NU_SC_SWAPBUFFER);
	} else {
		/* No menu */
		/* <<< ���j���[���� >>> */
		nuGfxTaskStart(&gfx_glist[gfx_gtask_no][0],
			(s32)(glistp - gfx_glist[gfx_gtask_no]) * sizeof (Gfx),
			NU_GFX_UCODE_F3DEX2 , NU_SC_SWAPBUFFER);
	}
  /* Swap display list buffer */
  /* <<< �f�B�X�v���C���X�g�o�b�t�@�̐؂�ւ� >>> */
  gfx_gtask_no ^= 1;
}


/* Advance game process for Stage 0 */
/* <<< �X�e�[�W�O�p�̃Q�[���i�s���� >>> */
void updateGame00(void)
{  
  /* Read Controller 1 data */
  /* <<< �R���g���[���P�̃f�[�^�ǎ�� >>> */
  nuContDataGetEx(contdata,0);

  /* Change display position according to Control Stick data */
  /* <<< �X�e�B�b�N�f�[�^�ɂ��\���ʒu��ύX���� >>> */
  triPos_x = contdata->stick_x;
  triPos_y = contdata->stick_y;
#if	1
  /* Controller-based menu manipulation process */
  /* <<< �R���g���[���[�ɂ�郁�j���[���쏈�� >>> */
  teControl(contdata);
#else
  /* Move to Stage 1 after pressing Start button */
  /* <<< �X�^�[�g�{�^���������ꂽ��A�X�e�[�W�P�Ɉڍs >>> */
  if(contdata[0].trigger & START_BUTTON){
    /* Remove callback function */
    /* <<< �R�[���o�b�N�֐�����菜���B >>> */
    nuGfxFuncRemove();
    /* Indicate next stage to Main */
    /* <<< ���̃X�e�[�W�����C���Ɏw�� >>> */
    stage = 1;
  }
#endif
}

/* Vertex coordinates */
/* <<< ���_�̍��W >>> */
static Vtx shade_vtx[] =  {
        {        -64,  64, -5, 0, 0, 0, 0, 0xff, 0, 0xff	},
        {         64,  64, -5, 0, 0, 0, 0, 0, 0, 0xff	},
        {         64, -64, -5, 0, 0, 0, 0, 0, 0xff, 0xff	},
        {        -64, -64, -5, 0, 0, 0, 0xff, 0, 0, 0xff	},
};

/* Compose a square */
/* <<< �����`������ >>> */
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

