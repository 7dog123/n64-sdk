#include <ultra64.h>
#include "params.h"


u8 *bin_start[] = {
#ifdef BIN_DATA1
    _bin1SegmentRomStart,
#endif
#ifdef BIN_DATA2
    _bin2SegmentRomStart,
#endif
#ifdef BIN_DATA3
    _bin3SegmentRomStart,
#endif
#ifdef BIN_DATA4
    _bin4SegmentRomStart,
#endif
#ifdef BIN_DATA5
    _bin5SegmentRomStart,
#endif
#ifdef BIN_DATA6
    _bin6SegmentRomStart,
#endif
#ifdef BIN_DATA7
    _bin7SegmentRomStart,
#endif
#ifdef BIN_DATA8
    _bin8SegmentRomStart,
#endif
#ifdef BIN_DATA9
    _bin9SegmentRomStart,
#endif
#ifdef BIN_DATA10
    _bin10SegmentRomStart,
#endif
    NULL,
};
u8 *bin_end[] = {
#ifdef BIN_DATA1
    _bin1SegmentRomEnd,
#endif
#ifdef BIN_DATA2
    _bin2SegmentRomEnd,
#endif
#ifdef BIN_DATA3
    _bin3SegmentRomEnd,
#endif
#ifdef BIN_DATA4
    _bin4SegmentRomEnd,
#endif
#ifdef BIN_DATA5
    _bin5SegmentRomEnd,
#endif
#ifdef BIN_DATA6
    _bin6SegmentRomEnd,
#endif
#ifdef BIN_DATA7
    _bin7SegmentRomEnd,
#endif
#ifdef BIN_DATA8
    _bin8SegmentRomEnd,
#endif
#ifdef BIN_DATA9
    _bin9SegmentRomEnd,
#endif
#ifdef BIN_DATA10
    _bin10SegmentRomEnd,
#endif
    NULL,
};
u8 *ptr_start[] = {
#ifdef PTR_DATA1
    _ptr1SegmentRomStart,
#endif
#ifdef PTR_DATA2
    _ptr2SegmentRomStart,
#endif
#ifdef PTR_DATA3
    _ptr3SegmentRomStart,
#endif
#ifdef PTR_DATA4
    _ptr4SegmentRomStart,
#endif
#ifdef PTR_DATA5
    _ptr5SegmentRomStart,
#endif
#ifdef PTR_DATA6
    _ptr6SegmentRomStart,
#endif
#ifdef PTR_DATA7
    _ptr7SegmentRomStart,
#endif
#ifdef PTR_DATA8
    _ptr8SegmentRomStart,
#endif
#ifdef PTR_DATA9
    _ptr9SegmentRomStart,
#endif
#ifdef PTR_DATA10
    _ptr10SegmentRomStart,
#endif
    NULL,
};
u8 *ptr_end[] = {
#ifdef PTR_DATA1
    _ptr1SegmentRomEnd,
#endif
#ifdef PTR_DATA2
    _ptr2SegmentRomEnd,
#endif
#ifdef PTR_DATA3
    _ptr3SegmentRomEnd,
#endif
#ifdef PTR_DATA4
    _ptr4SegmentRomEnd,
#endif
#ifdef PTR_DATA5
    _ptr5SegmentRomEnd,
#endif
#ifdef PTR_DATA6
    _ptr6SegmentRomEnd,
#endif
#ifdef PTR_DATA7
    _ptr7SegmentRomEnd,
#endif
#ifdef PTR_DATA8
    _ptr8SegmentRomEnd,
#endif
#ifdef PTR_DATA9
    _ptr9SegmentRomEnd,
#endif
#ifdef PTR_DATA10
    _ptr10SegmentRomEnd,
#endif
    NULL,
};
u8 *wbk_start[] = {
#ifdef WBK_DATA1
    _wbk1SegmentRomStart,
#endif
#ifdef WBK_DATA2
    _wbk2SegmentRomStart,
#endif
#ifdef WBK_DATA3
    _wbk3SegmentRomStart,
#endif
#ifdef WBK_DATA4
    _wbk4SegmentRomStart,
#endif
#ifdef WBK_DATA5
    _wbk5SegmentRomStart,
#endif
#ifdef WBK_DATA6
    _wbk6SegmentRomStart,
#endif
#ifdef WBK_DATA7
    _wbk7SegmentRomStart,
#endif
#ifdef WBK_DATA8
    _wbk8SegmentRomStart,
#endif
#ifdef WBK_DATA9
    _wbk9SegmentRomStart,
#endif
#ifdef WBK_DATA10
    _wbk10SegmentRomStart,
#endif
    NULL,
};
u8 *wbk_end[] = {
#ifdef WBK_DATA1
    _wbk1SegmentRomEnd,
#endif
#ifdef WBK_DATA2
    _wbk2SegmentRomEnd,
#endif
#ifdef WBK_DATA3
    _wbk3SegmentRomEnd,
#endif
#ifdef WBK_DATA4
    _wbk4SegmentRomEnd,
#endif
#ifdef WBK_DATA5
    _wbk5SegmentRomEnd,
#endif
#ifdef WBK_DATA6
    _wbk6SegmentRomEnd,
#endif
#ifdef WBK_DATA7
    _wbk7SegmentRomEnd,
#endif
#ifdef WBK_DATA8
    _wbk8SegmentRomEnd,
#endif
#ifdef WBK_DATA9
    _wbk9SegmentRomEnd,
#endif
#ifdef WBK_DATA10
    _wbk10SegmentRomEnd,
#endif
    NULL,
};

Params params;

void SetParameters(void)
{
    params.once_check_sec	= ONCE_CHECK_SEC;
    params.output_rate		= OUTPUT_RATE;
    params.max_channels		= MAX_CHANNELS;
    params.max_updates		= MAX_UPDATES;
    params.max_acmd_length	= MAX_ACMD_LENGTH;
    params.audio_heap_size	= AUDIO_HEAP_SIZE;
    params.max_buffer_size	= MAX_BUFFER_SIZE;
    params.max_buffer_num	= MAX_BUFFER_NUM;
}
