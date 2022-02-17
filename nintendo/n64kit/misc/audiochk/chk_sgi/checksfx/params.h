/*
 * params.h
 */
#ifndef _PARAMS_H_
#define _PARAMS_H_

#define ONCE_CHECK_SEC  1*60	/* play time a data */
#define OUTPUT_RATE 32000	/* output rate */

#define MAX_SOUNDS 0x400	/* max number of sounds */
#define MAX_UPDATES 0x1000	/* max updates */
#define MAX_EVENTS 0x800	/* max events */
#define MAX_ACMD_LENGTH 0x4000	/* max ACMD length */
#define AUDIO_HEAP_SIZE 0x200000
#define MAX_BUFFER_SIZE 0x1000	/* each DMA buffer size */
#define MAX_BUFFER_NUM  0x100	/* number of DMA buffers */

/* target data */
#define CTL_DATA    "../data/se.ctl"
#define TBL_DATA    "../data/se.tbl"

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

extern u8 _ctlSegmentRomStart[];
extern u8 _ctlSegmentRomEnd[];
extern u8 _tblSegmentRomStart[];
extern u8 _tblSegmentRomEnd[];

typedef struct Params_st {
    u32 once_check_sec;
    u32 output_rate;
    u32 max_sounds;
    u32 max_updates;
    u32 max_events;
    u32 max_acmd_length;
    u32 audio_heap_size;
    u32 max_buffer_size;
    u32 max_buffer_num;
} Params;

extern Params params;
extern void SetParameters(void);

#endif	/* defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS) */
#endif	/* _PARAMS_H_ */
