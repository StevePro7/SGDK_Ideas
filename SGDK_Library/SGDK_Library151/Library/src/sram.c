#include "sram.h"

/**
 *  \brief
 *      Enable SRAM in Read Write mode.
 */
void SRAM_enable()
{
}

/**
 *  \brief
 *      Enable SRAM in Read Only mode.
 */
void SRAM_enableRO()
{
}

/**
 *  \brief
 *      Disable SRAM.
 */
void SRAM_disable()
{
}

/**
 *  \brief
 *      Read a byte from the SRAM.
 *
 *  \param offset
 *      Offset where we want to read.
 *  \return value.
 */
u8 SRAM_readByte(u32 offset)
{
	return 0;
}

/**
 *  \brief
 *      Read a word from the SRAM.
 *
 *  \param offset
 *      Offset where we want to read.
 *  \return value.
 */
u16 SRAM_readWord(u32 offset)
{
	return 0;
}

/**
 *  \brief
 *      Read a long from the SRAM.
 *
 *  \param offset
 *      Offset where we want to read.
 *  \return value.
 */
u32 SRAM_readLong(u32 offset)
{
	return 0;
}

/**
 *  \brief
 *      Write a byte to the SRAM.
 *
 *  \param offset
 *      Offset where we want to write.
 *  \param val
 *      Value wto write.
 */
void SRAM_writeByte(u32 offset, u8 val)
{
}

/**
 *  \brief
 *      Write a word to the SRAM.
 *
 *  \param offset
 *      Offset where we want to write.
 *  \param val
 *      Value wto write.
 */
void SRAM_writeWord(u32 offset, u16 val)
{
}

/**
 *  \brief
 *      Write a long to the SRAM.
 *
 *  \param offset
 *      Offset where we want to write.
 *  \param val
 *      Value wto write.
 */
void SRAM_writeLong( u32 offset, u32 val )
{
}