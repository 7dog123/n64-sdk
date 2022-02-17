/*
 * params.h
 */
#ifndef _PARAMS_H_
#define _PARAMS_H_

#define ONCE_CHECK_SEC  3*60	/* play time a data */
#define OUTPUT_RATE 32000	/* output rate */

#define MAX_CHANNELS 48		/* max channels */
#define MAX_UPDATES 0x1000	/* max updates */
#define MAX_ACMD_LENGTH 0x4000	/* max ACMD length */
#define AUDIO_HEAP_SIZE 0x200000
#define MAX_BUFFER_SIZE 0x1000	/* each DMA buffer size */
#define MAX_BUFFER_NUM  0x100	/* number of DMA buffers */

/* 1st data */
#define BIN_DATA1    "../data/demo1_1.bin"
#define PTR_DATA1    "../data/demo1_1.ptr"
#define WBK_DATA1    "../data/demo1_1.wbk"

/* 2nd data */
#define BIN_DATA2    "../data/demo1_2.bin"
#define PTR_DATA2    "../data/demo1_1.ptr"
#define WBK_DATA2    "../data/demo1_1.wbk"

/* 3rd data */
#define BIN_DATA3    "../data/demo2_1.bin"
#define PTR_DATA3    "../data/demo2_1.ptr"
#define WBK_DATA3    "../data/demo2_1.wbk"

/* 4th data */
#define BIN_DATA4    "../data/demo2_2.bin"
#define PTR_DATA4    "../data/demo2_1.ptr"
#define WBK_DATA4    "../data/demo2_1.wbk"

/* 5th data */
// #define BIN_DATA5    
// #define PTR_DATA5    
// #define WBK_DATA5    

/* 6th data */
// #define BIN_DATA6    
// #define PTR_DATA6    
// #define WBK_DATA6    

/* 7th data */
// #define BIN_DATA7    
// #define PTR_DATA7    
// #define WBK_DATA7    

/* 8th data */
// #define BIN_DATA8    
// #define PTR_DATA8    
// #define WBK_DATA8    

/* 9th data */
// #define BIN_DATA9    
// #define PTR_DATA9    
// #define WBK_DATA9    

/* 10th data */
// #define BIN_DATA10   
// #define PTR_DATA10   
// #define WBK_DATA10   

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)
#if defined(BIN_DATA1) && defined(PTR_DATA1) && defined (WBK_DATA1)
extern u8 _bin1SegmentRomStart[];
extern u8 _bin1SegmentRomEnd[];
extern u8 _ptr1SegmentRomStart[];
extern u8 _ptr1SegmentRomEnd[];
extern u8 _wbk1SegmentRomStart[];
extern u8 _wbk1SegmentRomEnd[];
#endif
#if defined(BIN_DATA2) && defined(PTR_DATA2) && defined (WBK_DATA2)
extern u8 _bin2SegmentRomStart[];
extern u8 _bin2SegmentRomEnd[];
extern u8 _ptr2SegmentRomStart[];
extern u8 _ptr2SegmentRomEnd[];
extern u8 _wbk2SegmentRomStart[];
extern u8 _wbk2SegmentRomEnd[];
#endif
#if defined(BIN_DATA3) && defined(PTR_DATA3) && defined (WBK_DATA3)
extern u8 _bin3SegmentRomStart[];
extern u8 _bin3SegmentRomEnd[];
extern u8 _ptr3SegmentRomStart[];
extern u8 _ptr3SegmentRomEnd[];
extern u8 _wbk3SegmentRomStart[];
extern u8 _wbk3SegmentRomEnd[];
#endif
#if defined(BIN_DATA4) && defined(PTR_DATA4) && defined (WBK_DATA4)
extern u8 _bin4SegmentRomStart[];
extern u8 _bin4SegmentRomEnd[];
extern u8 _ptr4SegmentRomStart[];
extern u8 _ptr4SegmentRomEnd[];
extern u8 _wbk4SegmentRomStart[];
extern u8 _wbk4SegmentRomEnd[];
#endif
#if defined(BIN_DATA5) && defined(PTR_DATA5) && defined (WBK_DATA5)
extern u8 _bin5SegmentRomStart[];
extern u8 _bin5SegmentRomEnd[];
extern u8 _ptr5SegmentRomStart[];
extern u8 _ptr5SegmentRomEnd[];
extern u8 _wbk5SegmentRomStart[];
extern u8 _wbk5SegmentRomEnd[];
#endif
#if defined(BIN_DATA6) && defined(PTR_DATA6) && defined (WBK_DATA6)
extern u8 _bin6SegmentRomStart[];
extern u8 _bin6SegmentRomEnd[];
extern u8 _ptr6SegmentRomStart[];
extern u8 _ptr6SegmentRomEnd[];
extern u8 _wbk6SegmentRomStart[];
extern u8 _wbk6SegmentRomEnd[];
#endif
#if defined(BIN_DATA7) && defined(PTR_DATA7) && defined (WBK_DATA7)
extern u8 _bin7SegmentRomStart[];
extern u8 _bin7SegmentRomEnd[];
extern u8 _ptr7SegmentRomStart[];
extern u8 _ptr7SegmentRomEnd[];
extern u8 _wbk7SegmentRomStart[];
extern u8 _wbk7SegmentRomEnd[];
#endif
#if defined(BIN_DATA8) && defined(PTR_DATA8) && defined (WBK_DATA8)
extern u8 _bin8SegmentRomStart[];
extern u8 _bin8SegmentRomEnd[];
extern u8 _ptr8SegmentRomStart[];
extern u8 _ptr8SegmentRomEnd[];
extern u8 _wbk8SegmentRomStart[];
extern u8 _wbk8SegmentRomEnd[];
#endif
#if defined(BIN_DATA9) && defined(PTR_DATA9) && defined (WBK_DATA9)
extern u8 _bin9SegmentRomStart[];
extern u8 _bin9SegmentRomEnd[];
extern u8 _ptr9SegmentRomStart[];
extern u8 _ptr9SegmentRomEnd[];
extern u8 _wbk9SegmentRomStart[];
extern u8 _wbk9SegmentRomEnd[];
#endif
#if defined(BIN_DATA10) && defined(PTR_DATA10) && defined (WBK_DATA10)
extern u8 _bin10SegmentRomStart[];
extern u8 _bin10SegmentRomEnd[];
extern u8 _ptr10SegmentRomStart[];
extern u8 _ptr10SegmentRomEnd[];
extern u8 _wbk10SegmentRomStart[];
extern u8 _wbk10SegmentRomEnd[];
#endif

typedef struct Params_st {
    u32 once_check_sec;
    u32 output_rate;
    u32 max_channels;
    u32 max_updates;
    u32 max_acmd_length;
    u32 audio_heap_size;
    u32 max_buffer_size;
    u32 max_buffer_num;
} Params;

extern u8 *bin_start[];
extern u8 *bin_end[];
extern u8 *ptr_start[];
extern u8 *ptr_end[];
extern u8 *wbk_start[];
extern u8 *wbk_end[];
extern Params params;
extern void SetParameters(void);

#endif	/* defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS) */
#endif	/* _PARAMS_H_ */
