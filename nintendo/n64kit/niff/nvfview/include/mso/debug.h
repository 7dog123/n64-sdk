/*
  mso/debug.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 21, 1998.
*/

#ifndef _mso_debug_h
#define _mso_debug_h 1

#include <ultra64.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define MSO_DEBUG_OS	(0)
#define MSO_DEBUG_ISV	(1)

extern void msoPrintfInit( const u32 mode );
extern void ( *msoPrintf )( const char *fmt, ... );

/* Macro which creates compatibility with the previous version. */
#ifdef __ISV__
#define _msoPrintfInit() msoPrintfInit( MSO_DEBUG_ISV )
#else /* __ISV__ */
#define _msoPrintfInit() msoPrintfInit( MSO_DEBUG_OS )
#endif /* __ISV__ */
#define _msoPrintf msoPrintf

#ifdef __DEBUG__

#define CDEBUG(level,block) \
{ \
    if ( (__DEBUG__) >= (level) ) { block; }\
}
#define CASSERT(level,ex) \
{ \
    if ( (__DEBUG__) >= (level) ) \
    { \
	if ( ex ) _msoPrintf( "ASSERT %s:%d %s", __FILE__, __LINE__, # ex ); \
    } \
}

#else /* __DEBUG__ */

#define CDEBUG(level,block) ( ( void )0 )
#define CASSERT(level,ex) ( ( void )0 )

#endif /* __DEBUG__ */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mso_debug_h */
