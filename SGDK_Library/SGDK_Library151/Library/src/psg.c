#include "psg.h"

/**
 *  \brief
 *      Initialize PSG chip
 */
void PSG_init()
{
}

/**
 *  \brief
 *      Write to PSG port.
 *
 *  \param data
 *      value to write to the port.
 *
 * Write the specified value to PSG data port.
 *
 */
void PSG_write( u8 data )
{
}

/**
 *  \brief
 *      Set envelope level.
 *
 *  \param channel
 *      Channel we want to set envelope (0-3).
 *  \param value
 *      Envelope level to set (#PSG_ENVELOPE_MIN - #PSG_ENVELOPE_MAX).
 *
 * Set envelope level for the specified PSG channel.
 */
void PSG_setEnvelope( u8 channel, u8 value )
{
}

/**
 *  \brief
 *      Set tone.
 *
 *  \param channel
 *      Channel we want to set tone (0-3).
 *  \param value
 *      Tone value to set (0-1023).
 *
 * Set direct tone value for the specified PSG channel.
 */
void PSG_setTone( u8 channel, u16 value )
{
}

/**
 *  \brief
 *      Set frequency.
 *
 *  \param channel
 *      Channel we want to set frequency (0-3).
 *  \param value
 *      Frequency value to set in Hz (0-4095).
 *
 * Set frequency for the specified PSG channel.<br>
 * This method actually converts the specified frequency value in PSG tone value.
 */
void PSG_setFrequency( u8 channel, u16 value )
{
}

/**
 *  \brief
 *      Set noise type and frequency.
 *
 *  \param type
 *      Noise type, accepted values are:<br>
 *      #PSG_NOISE_TYPE_PERIODIC<br>
 *      #PSG_NOISE_TYPE_WHITE
 *  \param frequency
 *      Noise frequency, accepted values are:<br>
 *      #PSG_NOISE_FREQ_CLOCK2<br>
 *      #PSG_NOISE_FREQ_CLOCK4<br>
 *      #PSG_NOISE_FREQ_CLOCK8<br>
 *      #PSG_NOISE_FREQ_TONE3
 */
void PSG_setNoise( u8 type, u8 frequency )
{
}