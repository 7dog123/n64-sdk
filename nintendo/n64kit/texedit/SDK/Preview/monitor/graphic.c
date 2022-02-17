/*
  graphic.c

  General-use graphic routine (initialize and clear frame buffer) and external variable definitions
  <<< �O���t�B�b�N�ėp���[�`���i�������ƃt���[���o�b�t�@�N���A)�ƊO���ϐ���` >>>

  Notice: <<<...>>> is same comment in Japanese (SHIFT JIS code).
*/

#include <nusys.h>
#include "graphic.h"

Gfx          gfx_glist[2][GFX_GLIST_LEN];
Gfx          gfx_clear_glist[2][GFX_CLEAR_GLIST_LEN];
Dynamic      gfx_dynamic[2];
Gfx*         glistp;
u32          gfx_gtask_no = 0;

/*----------------------------------------------------------------------------
  gfxRCPIinit

  Initialize RSP/RDP
----------------------------------------------------------------------------*/
void gfxRCPInit(void)
{
  /* RSP segment register settings */
  /* <<< RSP�Z�O�����g���W�X�^�̐ݒ� >>> */
 
  /* For CPU virtual address */
  /* <<< CPU���z�A�h���X�p >>> */
  gSPSegment(glistp++, 0, 0x0);

  /* RSP setting */
  /* <<< RSP�̐ݒ� >>> */
  gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(setup_rspstate));

  /* RDP setting */
  /* <<< RDP�̐ݒ� >>> */
  gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(setup_rdpstate));
}

/*----------------------------------------------------------------------------
  gfxClearCfb

  Set address and clear frame buffer/Z buffer
  <<< �t���[���o�b�t�@�^�y�o�b�t�@�̃A�h���X�ݒ�ƃN���A >>>

  Use the NuSYSTEM global variables nuGfxZBuffer (Z buffer address) and nuGfxCfb_ptr (frame buffer address)
  <<< NuSYSTEM�̃O���[�o���ϐ��ł��� nuGfxZBuffer�i�y�o�b�t�@�̃A�h���X�j��
      nuGfxCfb_ptr�i�t���[���o�b�t�@�̃A�h���X�j���g�p���Ă��܂��B >>>
----------------------------------------------------------------------------*/
void gfxClearCfb(void)
{
  /* Clear Z buffer */
  /* <<< �y�o�b�t�@�̃N���A >>> */
  gDPSetDepthImage(glistp++, OS_K0_TO_PHYSICAL(nuGfxZBuffer));
  gDPSetCycleType(glistp++, G_CYC_FILL);
  gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b,SCREEN_WD,
		   OS_K0_TO_PHYSICAL(nuGfxZBuffer));
  gDPSetFillColor(glistp++,(GPACK_ZDZ(G_MAXFBZ,0) << 16 |
			       GPACK_ZDZ(G_MAXFBZ,0)));
  gDPFillRectangle(glistp++, 0, 0, SCREEN_WD-1, SCREEN_HT-1);
  gDPPipeSync(glistp++);
  
  /* Clear frame buffer */
  /* <<< �t���[���o�b�t�@�̃N���A >>> */
  gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD,
		   osVirtualToPhysical(nuGfxCfb_ptr));
  gDPSetFillColor(glistp++, (GPACK_RGBA5551(0, 0, 0, 1) << 16 | 
				GPACK_RGBA5551(0, 0, 0, 1)));
  gDPFillRectangle(glistp++, 0, 0, SCREEN_WD-1, SCREEN_HT-1);
  gDPPipeSync(glistp++);
}

