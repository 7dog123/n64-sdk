/*
 * [CCBL]
 *
 * ccbl_host.c
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#include "common_include.h"
#include "ccbl_host.h"
#include "rom_reg.h"
#include "pad.h"
#include "mysys.h"
#include "rcp_reg.h"
#include "malloc.h"
#include "model_load.h"
#ifndef __sgi
#include "./include/dptstcmd.h"
#endif /* !__sgi */

#define B_UP(s) ((s +1)&~1)

void
__write_cart(u32 romadr, void *buf,u32 size)
{
#ifndef FINAL

  OSIoMesg	dmaIoMesgBuf;
  OSMesgQueue dmaMesgQ;
  OSMesg	dmaMesgBuf;
#ifndef __sgi
  u32 sink;
#endif /* !__sgi */
  /* Create message queue.*/
  osCreateMesgQueue(&dmaMesgQ, &dmaMesgBuf, 1);
  
  dmaIoMesgBuf.hdr.pri      = OS_MESG_PRI_NORMAL;
  dmaIoMesgBuf.hdr.retQueue = &dmaMesgQ;
  dmaIoMesgBuf.dramAddr     = buf;
  dmaIoMesgBuf.devAddr      = (u32)romadr;
  dmaIoMesgBuf.size         = size;

  osWritebackDCache(buf,size);
  osInvalDCache((void*)buf, (s32)size);	/* precaution */
#ifndef __sgi
  osEPiReadIo(pih,REG_T_RUN_OFF,&sink);
#endif /* !__sgi */
  osEPiStartDma(pih, &dmaIoMesgBuf, OS_WRITE);

  /* Wait for end. */
  osRecvMesg(&dmaMesgQ, &dmaMesgBuf, OS_MESG_BLOCK);
#ifndef __sgi
  osEPiReadIo(pih,REG_T_RUN_ON,&sink);
#endif /* !__sgi */

#endif /* !FINAL */
}

/* --- DMA object --- */
#ifdef __GNUC__

static CCBL_CMD tcmd __attribute__ ((aligned (8))) = {
    {'C','C'},
    {0,0,0,0},
    {'B','L'}
};
#ifndef FINAL
static CCBL_CMD hcmd __attribute__ ((aligned (8)));
#endif
#else  /* __GNUC__ */

#ifdef __sgi
#pragma pack(8)
#else
#ifdef __MWERKS__
#pragma align(8)
#endif /* __MWERKS__ */
#endif /* __sgi */
static CCBL_CMD tcmd = {
    {'C','C'},
    {0,0,0,0},
    {'B','L'}
};
#ifndef FINAL
static CCBL_CMD hcmd;
#endif
#ifdef __sgi
#pragma pack(0)
#else
#ifdef __MWERKS__
#pragma align
#endif /* __MWERKS__ */
#endif /* __sgi */

#endif /* __GNUC__ */
/* --- end of DMA object --- */

ROM_REG *rom_data;
static u32 *tlen_p;

void
init_ccbl_hostio(void )
{
  rom_data = malloc(B_UP(sizeof(ROM_REG)));
  tlen_p = malloc(sizeof(u32));
#ifdef DPTEST
  DPTst_Init(pih);
#endif
}

/* to CART ROM */
void
save_parameters(void)
{
#ifndef FINAL

  ROM_REG *rr = rom_data;
  RCP_MODULE *rcp = &rcp_regs;

  bcopy(rcp->cycl,&rr->rr_cycl,sizeof(CYCLE_TYPE));
  bcopy(rcp->gm,&rr->rr_gm,sizeof(GEO_MODE));
  bcopy(rcp->ccac,&rr->rr_ccac,sizeof(CC_REG));
  bcopy(rcp->rm,&rr->rr_rm,sizeof(RENDER_MODE));
  bcopy(rcp->prm,&rr->rr_prm,sizeof(PRIM_COL));
  bcopy(rcp->env,&rr->rr_env,sizeof(ENV_COL));
  bcopy(rcp->blnd,&rr->rr_blnd,sizeof(BLEND_COL));
  bcopy(rcp->fog,&rr->rr_fog,sizeof(FOG_COL));
  bcopy(rcp->cd,&rr->rr_cd,sizeof(COLOR_DITHER));
  bcopy(rcp->ad,&rr->rr_ad,sizeof(ALPHA_DITHER));
  bcopy(rcp->ac,&rr->rr_ac,sizeof(ALPHA_COMPARE));
  bcopy(rcp->lc,&rr->rr_lc,sizeof(LIGHT_COL));
  bcopy(rcp->vsf,&rr->rr_vsf,sizeof(VSF));
  bcopy(rcp->fp,&rr->rr_fp,sizeof(FOG_POS));
  bcopy(rcp->tf,&rr->rr_tf,sizeof(TEX_FILT));
  
  *tlen_p = B_UP(sizeof(ROM_REG));
  __write_cart(ROM_REG_DATA_START,tlen_p,B_UP(sizeof(u32)));
  __write_cart(ROM_REG_DATA_BODY,rom_data,*tlen_p);

#endif /* !FINAL */
}

/* from CART ROM */
void
load_parameters(void)
{
#ifndef FINAL
  ROM_REG *rr = rom_data;
  RCP_MODULE *rcp = &rcp_regs;

  
  nuPiReadRom(ROM_REG_DATA_START,tlen_p,B_UP(sizeof(u32)));
  nuPiReadRom(ROM_REG_DATA_BODY,rom_data,B_UP(*tlen_p));

  bcopy(&rr->rr_cycl,rcp->cycl,sizeof(CYCLE_TYPE));
  bcopy(&rr->rr_gm,rcp->gm,sizeof(GEO_MODE));
  bcopy(&rr->rr_ccac,rcp->ccac,sizeof(CC_REG));
  bcopy(&rr->rr_rm,rcp->rm,sizeof(RENDER_MODE));
  bcopy(&rr->rr_prm,rcp->prm,sizeof(PRIM_COL));
  bcopy(&rr->rr_env,rcp->env,sizeof(ENV_COL));
  bcopy(&rr->rr_blnd,rcp->blnd,sizeof(BLEND_COL));
  bcopy(&rr->rr_fog,rcp->fog,sizeof(FOG_COL));
  bcopy(&rr->rr_cd,rcp->cd,sizeof(COLOR_DITHER));
  bcopy(&rr->rr_ad,rcp->ad,sizeof(ALPHA_DITHER));
  bcopy(&rr->rr_ac,rcp->ac,sizeof(ALPHA_COMPARE));
  bcopy(&rr->rr_lc,rcp->lc,sizeof(LIGHT_COL));
  bcopy(&rr->rr_vsf,rcp->vsf,sizeof(VSF));
  bcopy(&rr->rr_fp,rcp->fp,sizeof(FOG_POS));
  bcopy(&rr->rr_tf,rcp->tf,sizeof(TEX_FILT));

#endif /* !FINAL */
}

/* user model */
void
define_user_model(void)
{
#ifndef FINAL
  nuPiReadRom(ROM_REG_DATA_START,tlen_p,B_UP(sizeof(u32)));
  set_user_model_length(*tlen_p);
  set_user_model_sw(1);
#endif /* !FINAL */

}

int
get_hostio_cmd(void)
{
#ifdef FINAL
  return -1;
#else
#ifdef DPTEST
  u32 ut;

  ut = DPTst_GetCmd(pih);
  if(ut == 0xffffffff) return -1;
  return ut;
#else
  nuPiReadRom(HOSTIO_ROM_START,&hcmd,B_UP(sizeof(CCBL_CMD)));
  if((hcmd.cmd_id0[0]=='C')&&
     (hcmd.cmd_id0[1]=='C')&&
     (hcmd.cmd_id1[0]=='B')&&
     (hcmd.cmd_id1[1]=='L')) return hcmd.cmd_reg[0];
  return -1;
#endif /* DPTEST */
#endif /* FINAL */
}


void
put_hostio_done(void)
{
#ifdef DPTEST
  DPTst_PutCmd(pih,CCBL_COMMAND_DONE);
#else
  tcmd.cmd_reg[0] = CCBL_COMMAND_IDEL;
  __write_cart(HOSTIO_ROM_START,&tcmd,B_UP(sizeof(tcmd)));
#endif /* DPTEST */
}


void
ccbl_hostio_main(void)
{
  int cmd;

  if((cmd = get_hostio_cmd()) < 0) return; 
  switch(cmd) {
  case CCBL_DATA_TO_TARGET:
    load_parameters();
    put_hostio_done();
    break;
  case CCBL_DATA_FROM_TARGET:
    save_parameters();
    put_hostio_done();
    break;
  case CCBL_NIFF_GBI_TO_TARGET:
    define_user_model();
    put_hostio_done();
    break;
  case CCBL_TEXTURE_TO_TARGET: 
    put_hostio_done();
    break;
  case CCBL_GBITEXT_FROM_TARGET:
  case CCBL_GBITEXT_S_FROM_TARGET:
    __write_cart(ROM_REG_DATA_START,
		 printRCP_REG(cmd-CCBL_GBITEXT_FROM_TARGET),
		 B_UP(sizeof(PRNT)));
    put_hostio_done();
    break;
  default:
#ifdef DPTEST
  DPTst_PutCmd(pih,CCBL_COMMAND_FAIL);
#endif /* DPETST */
    break;
  };
}

void
hostio_test_code(void)
{
#ifndef FINAL

#ifndef DPTEST
  Pad_D *pd = &Mpad[1];

  if(pd->button & PAD_ZT){
    if(pd->trigger & PAD_CD){
      tcmd.cmd_reg[0] = CCBL_DATA_FROM_TARGET;
      __write_cart(HOSTIO_ROM_START,&tcmd,B_UP(sizeof(tcmd)));
      //osSyncPrintf("SAVE COMMAND\n");
    }else if(pd->trigger & PAD_CR){
      tcmd.cmd_reg[0] = CCBL_DATA_TO_TARGET;
      __write_cart(HOSTIO_ROM_START,&tcmd,B_UP(sizeof(tcmd)));
      //osSyncPrintf("LOAD COMMAND\n");
    }else if(pd->trigger & PAD_CU){
      tcmd.cmd_reg[0] = CCBL_NIFF_GBI_TO_TARGET;
      __write_cart(HOSTIO_ROM_START,&tcmd,B_UP(sizeof(tcmd)));
      *tlen_p = 0x20000;
      __write_cart(ROM_REG_DATA_START,tlen_p,B_UP(sizeof(u32)));
      //osSyncPrintf("DEFINE USER MODEL\n");
    }
  }

#endif /* DPTEST */

#endif /* !FINAL */
}

