/*
 * dptstcmd.h
 */

#ifndef _dptstcmd_h_
#define _dptstcmd_h_

#include <ultra64.h>

/* Register addresses for the target.
 */
#define REG_T_RUN_ON    (0x1ff08008 | 0xa0000000)
#define REG_T_RUN_OFF   (0x1ff0800c | 0xa0000000)
#define REG_T_RX_PORT   (0x1ff08000 | 0xa0000000)
#define REG_T_TXW_PORT  (0x1ff08000 | 0xa0000000)
#define REG_TSTAT       (0x1ff08004 | 0xa0000000)
#define REG_T_WR_METHOD (0x1ff08014 | 0xa0000000)

/* TSTAT mask
 */
#define MSK_T_TX_RDY 0x00000004
#define MSK_T_RX_RDY 0x00000002

/* Command buffers
 */
#define DPTST_CMDSNDAREA (0x00f00000 | 0xb0000000)
#define DPTST_CMDRCVAREA (0x00f00010 | 0xb0000000)

/* Command ID characters
 */
#define DPTST_CMDID0 'C'
#define DPTST_CMDID1 'C'
#define DPTST_CMDID2 'B'
#define DPTST_CMDID3 'L'


#define RevDWORD(x) ((((x)>>24)&0x000000ff) | (((x)>>8 )&0x0000ff00) \
		     | (((x)<<8 )&0x00ff0000) | (((x)<<24)&0xff000000))

#ifndef max
#define max(x,y) (((x) > (y)) ? (x) : (y))
#endif


/* Command structure
 */
typedef struct{
  char Id0 ;
  char Id1 ;
  char Cmd[4] ;
  char Id2 ;
  char Id3 ;
}DPTst_Cmd ;


/* Initialize DPTstCmd library
 * 
 * IN: 		pih <-- PI handle initialized for cartridge
 * OUT :	0
 * Note:
 *   Must be called before other library functions.  If possible, should be called at the
 *   beginning of the program. 
 *  
 */
extern int DPTst_Init( OSPiHandle *pih ) ;

/* Send command 
 * 
 * IN: 		pih <-- PI handle initialized for cartridge
 * 		cmd <-- command
 * OUT:	0
 * Note:
 *   Cannot be called before host reads the previously sent command.
 */
extern int DPTst_PutCmd( OSPiHandle *pih, unsigned long cmd ) ;

/* Receive command
 * 
 * IN: 		pih <-- PI handle initialized for cartridge
 * OUT : 	0xffffffff --> reception failure
 *  		other --> received command 
 */
extern unsigned long DPTst_GetCmd( OSPiHandle *pih ) ;

#endif /* _dptstcmd_h_ */
