
/*---------------------------------------------------------------------*
        Copyright (C) 1998 Nintendo.
        
        $RCSfile: err.c,v $
        $Revision: 1.1 $
        $Date: 1999/07/05 02:20:04 $
 *---------------------------------------------------------------------*/

#include "hmenu.h"
#include "herr.h"


u8 err_str[60];
static s32 err_show=0;

#define LABEL_NUM 7
#define BTILE_NUM 1

static TStringBar  _label[LABEL_NUM];
static TBackTile   _btile[BTILE_NUM];
static void _print(void);
static s32 _init(void);

static s32 _mode ;

void
_print(void)
{
  s32 i,j,mes_num=0,max_width=1;
  TDDStatus *p;

  p = dd_getStatus();

  _mode = p->errmes;
  FORI(LABEL_NUM) _label[i].visible = false;
  if( p->mode & ( DDSTAT_DEAD | DDSTAT_DIALOGUE) )
	{
	  switch( _mode & 0xFF) 
		{
/*  Essential messages (Area 1)  */

		case ERRMES__DDROMCART_NOT_CONNECTED:
		  sprintf( _label[mes_num++].str ,"#error No %d",p->errno) ;
		  sprintf( _label[mes_num++].str ,"#No IPL ROM cart.") ;
		  sprintf( _label[mes_num++].str ,"#Please set.") ;
		  break;

		case ERRMES__RAMPACK_NOT_CONNECTED:
		  sprintf( _label[mes_num++].str ,"error number %d",p->errno) ;
		  sprintf( _label[mes_num++].str ,"Is the memory expansion ") ;
		  sprintf( _label[mes_num++].str ,"pak inserted correctly?") ;
		  sprintf( _label[mes_num++].str ,"For details, please read the manual.") ;
		  break;

		case ERRMES__TORISETSU_YOME:
		  sprintf( _label[mes_num++].str ,"error number %d",p->errno) ;
		  sprintf( _label[mes_num++].str ,"Please read the manual.") ;
		  break;

		case ERRMES__NOW_IN_RESTORE:  
		  sprintf( _label[mes_num++].str ,"All data could not ");
		  sprintf( _label[mes_num++].str ,"be saved last time.");
		  sprintf( _label[mes_num++].str ,"This data will be deleted.");
		  sprintf( _label[mes_num++].str ,"Press button A.");
		  break;

		case ERRMES__ACCESSLAMP:
		  sprintf( _label[mes_num++].str ,"error number %d",p->errno) ;
		  sprintf( _label[mes_num++].str ,"Do not remove the disk ") ;
		  sprintf( _label[mes_num++].str ,"while access lamp is lit.") ;
		  sprintf( _label[mes_num++].str ,"Please read the manual for details.") ;
		  break;

		case ERRMES__WRONG_DISK:
		  sprintf( _label[mes_num++].str ,"Wrong disk might") ;
		  sprintf( _label[mes_num++].str ,"be inserted.") ;
		  sprintf( _label[mes_num++].str ,"Insert the correct disk.") ;
		  break;

/*  message for each application */

		case ERRMES__DRIVE_NOT_FOUND:
		  sprintf( _label[mes_num++].str ,"#64DD not connected") ;

		default:
		  break;
		}

	  switch( _mode & 0xFF00 ) 
		{
/*  Essential messages (Area 2)   */
		case ERRMES__DISK_WO_NUKE:
		  sprintf( _label[mes_num++].str ,"Remove the disk.") ;
		  break;

		case ERRMES__DISK_WO_IRERO:
		  sprintf( _label[mes_num++].str ,"Insert the disk.") ;
		  break;

		case ERRMES__INSERT_AGAIN:
		  if( mes_num==0 ) sprintf( _label[mes_num++].str ,"error number %d",p->errno) ;
		  sprintf( _label[mes_num++].str ,"Reinsert the disk.") ;
		  break;

		}
	}
  else
	{
	  if( err_show )
		{
		  err_show--;
		  mes_num = 1;
		}
	}

	  /*  Adjusts the display position. */
	  FORI(mes_num)
	    {
	      j = sbar_getWidth(&_label[i]);
	      max_width = (j>max_width) ? j : max_width;
	    }
	  _btile[0].w = max_width + 10;
	  FORI(mes_num) _label[i].visible = true;
	  j = ( SCREEN_WD - max_width ) / 2 ;
	  FORI(mes_num) _label[i].x = j;
          _btile[0].x = j - 5;
	  _btile[0].h = mes_num * 16;

	  /*  Display  */
	  btile_show(&_btile[0]);
	  FORI(LABEL_NUM) sbar_show(&_label[i]);
}

void
err_setString(u8 * message)
{
  err_show = 180;
  sprintf(_label[0].str,"%s",message);
}

void
scr_error(void)
{
  static s32 _first = 1;

  if(_first)
	{
	  --_first;
	  _init();
	}

  _print();

  if( _trig == A_BUTTON )
	{
	  switch ( _mode & 0xFF )
		{
		case ERRMES__NOW_IN_RESTORE:
		  dd_thaw(ERRMES__NOW_IN_RESTORE);
		  break;
		}
	}
	
}

static s32
_init(void)
{
  s32 xpos,ypos,i;
  
  xpos = 0;
  ypos = 100;

  FORI(LABEL_NUM) sbar_create(&_label[i],"*" ,45 ,50 + i * 16 );
  
  btile_create(&_btile[0] ,40 ,50 ,240 ,100 ,RGBA_VIOLET );

  return -1;
}
