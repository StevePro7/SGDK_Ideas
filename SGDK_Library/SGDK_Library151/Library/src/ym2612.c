#include "ym2612.h"

/**
 *  \brief
 *      Reset YM2612 chip
 */
void YM2612_reset()
{
}

/**
 *  \brief
 *      Read YM2612 port.
 *
 *  \param port
 *      Port number (0-3)
 *  \return YM2612 port value.
 *
 *  Reading YM2612 always return YM2612 status (busy and timer flag) whatever is the port read.
 */
u8 YM2612_read( const u16 port )
{
	return 0;
}

/**
 *  \brief
 *      Write YM2612 port.
 *
 *  \param port
 *      Port number (0-3)
 *  \param data
 *      Data to write
 *
 *  This function does not perform busy check before writing to YM port.<br>
 *  See also YM2612_writeSafe().
 */
void YM2612_write( const u16 port, const u8 data )
{
}

/**
 *  \deprecated Use YM2612_write(..) method instead.
 */
void YM2612_writeSafe( const u16 port, const u8 data )
{
}

/**
 *  \brief
 *      Set YM2612 register value.
 *
 *  \param part
 *      part number (0-1)
 *  \param reg
 *      register number
 *  \param data
 *      register value
 *
 *  This function does not perform busy check before writing to YM port.<br>
 *  See also YM2612_writeRegSafe().
 */
void YM2612_writeReg( const u16 part, const u8 reg, const u8 data )
{
}

/**
 *  \deprecated Use YM2612_writeReg(..) method instead.
 */
void YM2612_writeRegSafe( const u16 part, const u8 reg, const u8 data )
{
}

/**
 *  \brief
 *      Enable YM2612 DAC.
 */
void YM2612_enableDAC()
{
}

/**
 *  \brief
 *      Disable YM2612 DAC.
 */
void YM2612_disableDAC()
{
}