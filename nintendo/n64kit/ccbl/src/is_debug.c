#include <ultra64.h>
#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>

/*
   Intelligent Systems Co.,Ltd.

   _IS_MSGBUFFER_AD and _IS_MSGBUFFER_LEN are the address and size of the communication buffer for debug printing.  When problems related to buffer location occur, the location can be changed in 4 K increments.  Straddling a 64 K segment (e.g., from 0xb1f88000 to 0xb1f98000) is not permitted.  If the values are changed, the host setting must be changed to a corresponding address.  If these conditions do not agree, proper operation cannot be guaranteed.  Values other than those of _IS_MSGBUFFER_AD and _IS_MSGBUFFER_LEN should not be changed.

Default address: 		_IS_MSGBUFFER_AD= 0xb1ff0000
Default size: 		_IS_MSGBUFFER_LEN = 0x10000

*/
#ifdef ISVGDB
#define _IS_MSGBUFFER_AD 0xb1bf0000 /* 32Mbyte RAM bottom for gdb*/
#else
#define _IS_MSGBUFFER_AD 0xb1ff0000 /* 32Mbyte RAM bottom for nload */
#endif
#define _IS_MSGBUFFER_LEN 0x10000 /* bbuffer length */



#define _IS_MSGBUF_HEADLEN	0x20
#define _IS_MSGBUF_CHKAD	(_IS_MSGBUFFER_AD+0x00)		/* V810->N64  "IS64"		*/
#define _IS_MSGBUF_GETPT	(_IS_MSGBUFFER_AD+0x04)		/* V810->N64  get pt		*/
#define _IS_MSGBUF_PUTPT	(_IS_MSGBUFFER_AD+0x14)		/* N64->V810  put pt		*/
#define _IS_MSGBUF_MSGTOP	(_IS_MSGBUFFER_AD+_IS_MSGBUF_HEADLEN)

#define _IS_MSGBUF_CHK_CODE	(('I'<<24)+('S'<<16)+('6'<<8)+'4')

#if 0
#if 1	/* normal 1 */
#define _is_WriteIo osPiWriteIo
#define _is_ReadIo osPiReadIo
#else	/* isPrintf debug */
#define _IS_MSGBUFFER_AD	0x800f0000
#define _is_WriteIo TestWrite
#define _is_ReadIo TestRead
TestRead(int ad, int *dt)
{ *dt = *(int *)ad; }
TestWrite(int ad, int dt)
{ *(int *)ad	= dt; }
#endif
#endif

#ifdef ISVIEWER
OSPiHandle *is_pih;

s32
_is_WriteIo(u32 devAddr,u32 data)
{
  return osEPiWriteIo(is_pih,devAddr,data);
}

s32
_is_ReadIo(u32 devAddr,u32 *data)
{
  return osEPiReadIo(is_pih,devAddr,data);
}
#endif

void isPrintfInit(OSPiHandle *pih)
{
#ifdef ISVIEWER
  is_pih = pih;
  _is_WriteIo(_IS_MSGBUF_PUTPT, 0);
  _is_WriteIo(_IS_MSGBUF_GETPT, 0);
  _is_WriteIo(_IS_MSGBUF_CHKAD, _IS_MSGBUF_CHK_CODE);
#endif
}

#ifdef ISVIEWER
static void *_is_printf_s(void *, const char *, int);

extern void _Printf(void (*)(void *), int, const char *, va_list);
#endif

void isPrintf(const char *fmt, ...)
{
#ifdef ISVIEWER
  va_list ap;

  va_start(ap, fmt);
  _Printf((void(*)(void *))_is_printf_s, 0, fmt, ap);
  va_end(ap);
#endif
}

#ifdef ISVIEWER
void osSyncPrintf(const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  _Printf((void(*)(void *))_is_printf_s, 0, fmt, ap);
  va_end(ap);
}

void rmonPrintf(const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  _Printf((void(*)(void *))_is_printf_s, 0, fmt, ap);
  va_end(ap);
}

#endif

#ifdef ISVIEWER
static void *_is_printf_s(void *str, register const char *buf, register int n)
{
  u32 dt;
  register int	putad, getad, newad;
  register int	sft, ad;

  _is_ReadIo(_IS_MSGBUF_CHKAD, &dt);
  if (dt != _IS_MSGBUF_CHK_CODE) return((void *)1);

  _is_ReadIo(_IS_MSGBUF_GETPT, &dt); getad = dt;
  _is_ReadIo(_IS_MSGBUF_PUTPT, &dt); putad = dt;
  newad = putad + n;
  if (newad >= (_IS_MSGBUFFER_LEN - _IS_MSGBUF_HEADLEN)) {
    newad -= (_IS_MSGBUFFER_LEN - _IS_MSGBUF_HEADLEN);
    if ((getad < (newad)) || (getad > putad)) return((void *)1);
  } else {
    if ((getad > putad) && (getad < (newad))) return((void *)1);
  }

  while(n) {
    if (*buf) {
      sft = (3 - (putad & 0x03)) << 3;
      ad = _IS_MSGBUF_MSGTOP+(putad & 0x0ffffffc);
      _is_ReadIo(ad, &dt);
      _is_WriteIo(ad, (dt & (~(0xff << sft)))|(*buf << sft));
      putad++;
      if (putad >= (_IS_MSGBUFFER_LEN - _IS_MSGBUF_HEADLEN))
	putad -= (_IS_MSGBUFFER_LEN - _IS_MSGBUF_HEADLEN);
    }
    buf++;
    n--;
  }
  _is_WriteIo(_IS_MSGBUF_PUTPT, putad);
  return((void *)1);
}

#endif

