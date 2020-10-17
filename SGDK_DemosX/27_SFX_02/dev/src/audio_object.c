#include "audio_object.h"
#include "sfx.h"

// Too many initializers
// https://www.iditect.com/how-to/53164385.html
const u8 *myaudio[128] =
{
	sonic_dead_sfx,
	sonic_kill_sfx,
	sonic_jump_sfx,
	sonic_mike_sfx,
	sonic_over_sfx,
	sonic_roll_sfx,
	sonic_ring_sfx,
	sonic_stop_sfx,
	
};

const u32 myaudio_size[128] =
{
	38656,
	69376,
	6144,
	218368,
	34560,
	28416,
	8448,
	6656,
	
};