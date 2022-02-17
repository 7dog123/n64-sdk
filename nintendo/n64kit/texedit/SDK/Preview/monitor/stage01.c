/*
  stage01.c 

  Notice: <<<...>>> is same comment in Japanese (SHIFT JIS code).
*/

#include <assert.h>
#include <nusys.h>
#include "main.h"
#include "graphic.h"

/* Angle of rotation of square */
/* <<< �����`�̉�]�p�x >>> */
static float theta;

void shadetri(Dynamic* dynamicp);


/* Initialize Stage 1 */
/* <<< �X�e�[�W�P�̏����� >>> */
void initStage01(void)
{
  theta = 0.0;
}


/* Create display list for Stage 1 and start task */
/* <<< �X�e�[�W�P�p�f�B�X�v���C���X�g�����A�^�X�N���N�� >>> */
void makeDL01(void)
{
  Dynamic* dynamicp;

  /* Display list buffer settings */
  /* <<< �f�B�X�v���C���X�g�o�b�t�@�̎w�� >>> */
  dynamicp = &gfx_dynamic[gfx_gtask_no];
  glistp = &gfx_glist[gfx_gtask_no][0];

  /* Initialize RCP */
  /* <<< RCP�̏����� >>> */
  gfxRCPInit();

  /* projection,modeling matrix set */
  guOrtho(&dynamicp->projection,
	  -(float)SCREEN_WD/2.0F, (float)SCREEN_WD/2.0F,
	  -(float)SCREEN_HT/2.0F, (float)SCREEN_HT/2.0F,
	  1.0F, 10.0F, 1.0F);
  guRotate(&dynamicp->modeling, theta, 0.0F, 0.0F, 1.0F);
  guTranslate(&dynamicp->translate, 0.0F, 0.0F, 0.0F);

  /* Draw a square */
  /* <<< �����`��`�� >>> */
  shadetri(dynamicp);

  gDPFullSync(glistp++);
  gSPEndDisplayList(glistp++);

  assert((glistp - gfx_glist[gfx_gtask_no]) < GFX_GLIST_LEN);

  /* Start task, and swap display buffer */
  /* <<< �^�X�N���N�����A�\���o�b�t�@��؂�ւ��܂��B >>> */
  nuGfxTaskStart(&gfx_glist[gfx_gtask_no][0],
		 (s32)(glistp - gfx_glist[gfx_gtask_no]) * sizeof (Gfx),
		 NU_GFX_UCODE_F3DEX , NU_SC_NOSWAPBUFFER);

  /* Change text display position */
  /* <<< �����\���ʒu�̕ύX >>> */
  nuDebConTextPos(0,11,5);
  /* Display text */
  /* <<< �����̕\�� >>> */
  nuDebConCPuts(0, "Stage 1 : A & B");
  /* Draw text to frame buffer */
  /* <<< �������t���[���o�b�t�@�ɕ`�� >>> */
  nuDebConDisp(NU_SC_SWAPBUFFER);

  /* Swap display list buffer */
  /* <<< �f�B�X�v���C���X�g�o�b�t�@�̐؂�ւ� >>> */
  gfx_gtask_no ^= 1;

  glistp = &gfx_clear_glist[gfx_gtask_no][0];

  /* Initialize RCP */
  /* <<< RCP�̏����� >>> */
  gfxRCPInit();

  /* Clear frame buffer and Z buffer */
  /* <<< �t���[���o�b�t�@�Ƃy�o�b�t�@�̃N���A >>> */
  gfxClearCfb();

  assert((glistp - gfx_clear_glist[gfx_gtask_no]) < GFX_CLEAR_GLIST_LEN);

  gDPFullSync(glistp++);
  gSPEndDisplayList(glistp++);

  /* Start task, and swap display buffer */
  /* <<< �^�X�N���N�����A�\���o�b�t�@��؂�ւ��܂��B >>> */
  nuGfxTaskStart(&gfx_clear_glist[gfx_gtask_no][0],
		 (s32)(glistp - gfx_clear_glist[gfx_gtask_no]) * sizeof (Gfx),
		 NU_GFX_UCODE_F3DEX , NU_SC_NOSWAPBUFFER);
}


/* Advance game process for Stage 1 */
/* <<< �X�e�[�W�P�p�̃Q�[���i�s���� >>> */
void updateGame01(void)
{  
  static float vel = 1.0;

  /* Read Controller 1 data */
  /* <<< �R���g���[���P�̃f�[�^�ǎ�� >>> */
  nuContDataGetEx(contdata,0);

  /* Rotate backwards with A button */
  /* <<< �`�{�^���ŋt��] >>> */
  if(contdata[0].trigger & A_BUTTON)
    vel = -vel;

  /* Accelerate rotation while B button is being pressed */
  /* <<< �a�{�^���������Ă���ԁA������] >>> */
  if(contdata[0].button & B_BUTTON)
    theta += vel * 3.0;
  else
    theta += vel;

  /* Move to Stage 1 after pressing Start button */
  /* <<< �X�^�[�g�{�^���������ꂽ��A�X�e�[�W�O�Ɉڍs >>> */
  if(contdata[0].trigger & START_BUTTON)
    {
      /* Remove callback function */
      /* <<< �R�[���o�b�N�֐�����菜���B >>> */
      nuGfxFuncRemove();
      /* Indicate next stage to Main */
      /* <<< ���̃X�e�[�W�����C���Ɏw�� >>> */
      stage = 0;
    }
}
