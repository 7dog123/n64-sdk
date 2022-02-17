#include <ultra64.h>
#include "params.h"

Params params;

void SetParameters(void)
{
    params.once_check_sec	= ONCE_CHECK_SEC;
    params.output_rate		= OUTPUT_RATE;
    params.max_sounds		= MAX_SOUNDS;
    params.max_updates		= MAX_UPDATES;
    params.max_events		= MAX_EVENTS;
    params.max_acmd_length	= MAX_ACMD_LENGTH;
    params.audio_heap_size	= AUDIO_HEAP_SIZE;
    params.max_buffer_size	= MAX_BUFFER_SIZE;
    params.max_buffer_num	= MAX_BUFFER_NUM;
}
