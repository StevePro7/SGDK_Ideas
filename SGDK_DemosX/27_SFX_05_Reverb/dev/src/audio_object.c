#include "audio_object.h"
#include "sfx.h"

// Too many initializers
// https://www.iditect.com/how-to/53164385.html
const u8 *myaudio[] =
{
	sfx_good_enuf_rev_org,
	sfx_good_enuf_rev_low,
	sfx_low_00_60,
	sfx_med_00_60,
	sfx_org_00_60,
	sfx_strong_00_60,
};

const u32 myaudio_size[] =
{
	123136,
	123136,
	123136,
	123136,
	123136,
	123136,
};