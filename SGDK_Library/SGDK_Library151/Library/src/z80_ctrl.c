#include "z80_ctrl.h"

/**
 *  \brief
 *      Initialize Z80 sub system.
 *
 *  Request Z80 BUS and reset bank number.
 */
void Z80_init()
{
}

/**
 *  \brief
 *      Return Z80 BUS taken state.
 */
u16  Z80_isBusTaken()
{
	return 0;
}

/**
 *  \brief
 *      Request Z80 BUS.
 *  \param wait
 *      Wait for BUS request operation to complete.
 */
void Z80_requestBus( u16 wait )
{
}

/**
 *  \brief
 *      Release Z80 BUS.
 */
void Z80_releaseBus()
{
}

/**
 *  \brief
 *      Start Z80 reset.
 */
void Z80_startReset()
{
}

/**
 *  \brief
 *      End Z80 reset.
 */
void Z80_endReset()
{
}

/**
 *  \brief
 *      Set Z80 memory bank.
 *  \param bank
 *      Bank number to set (0x000-0x1FF)
 */
void Z80_setBank( const u16 bank )
{
}

/**
 *  \brief
 *      Read Z80 memory (Z80_RAM).
 *  \param addr
 *      Address to read (relative to start of Z80_RAM).
 *
 *  You need to request Z80 BUS to access Z80 memory.
 *
 *  \see Z80_requestBus(u16)
 */
u8 Z80_read( const u16 addr )
{
	return 0;
}

/**
 *  \brief
 *      Write to Z80 memory (Z80_RAM).
 *  \param addr
 *      Address to write (relative to start of Z80_RAM).
 *  \param value
 *      Value to write.
 *
 *  You need to request Z80 BUS to access Z80 memory.
 *
 *  \see Z80_requestBus(u16)
 */
void Z80_write( const u16 addr, const u8 value )
{
}

/**
 *  \brief
 *      Clear Z80 memory.
 *  \param dest
 *      Destination address (Z80 memory).
 *  \param size
 *      Size in byte of region to clear.
 *  \param resetz80
 *      Reset Z80 if set to TRUE.
 */
void Z80_clear( const u16 dest, const u16 size, const bool resetz80 )
{
}

/**
 *  \brief
 *      Upload data in Z80 memory.
 *  \param dest
 *      Destination address (Z80 memory).
 *  \param data
 *      Data to upload.
 *  \param size
 *      Size in byte of data to upload.
 *  \param resetz80
 *      Reset Z80 if set to TRUE.
 */
void Z80_upload( const u16 dest, const u8 *data, const u16 size, const bool resetz80 )
{
}

/**
 *  \brief
 *      Read data from Z80 memory.
 *
 *  \param from
 *      Source address (Z80 memory).
 *  \param dest
 *      Destination where to write data.
 *  \param size
 *      Size in byte of data to read.
 */
void Z80_download( const u16 from, u8 *dest, const u16 size )
{
}

/**
 *  \brief
 *      Return currently loaded Z80 driver.
 *
 *  Possible returned values are:<br>
 *  - #Z80_DRIVER_NULL<br>
 *  - #Z80_DRIVER_PCM<br>
 *  - #Z80_DRIVER_2ADPCM<br>
 *  - #Z80_DRIVER_4PCM<br>
 *  - #Z80_DRIVER_XGM<br>
 *  - #Z80_DRIVER_CUSTOM<br>
 */
u16  Z80_getLoadedDriver()
{
	return 0;
}

/**
 *  \brief
 *      Unload Z80 driver (actually clear Z80 ram).
 */
void Z80_unloadDriver()
{
}

/**
 *  \brief
 *      Load a Z80 driver.
 *
 *  \param driver
 *      Driver to load, possible values are:<br>
 *      - #Z80_DRIVER_NULL<br>
 *      - #Z80_DRIVER_PCM<br>
 *      - #Z80_DRIVER_2ADPCM<br>
 *      - #Z80_DRIVER_4PCM<br>
 *      - #Z80_DRIVER_XGM<br>
 *  \param waitReady
 *      Wait for driver to be ready.
 */
void Z80_loadDriver( const u16 driver, const bool waitReady )
{
}

/**
 *  \brief
 *      Load a custom Z80 driver.
 *
 *  \param drv
 *      Pointer to the driver binary to load.
 *  \param size
 *      Size (in bytes) of the driver binary.
 */
void Z80_loadCustomDriver( const u8 *drv, u16 size )
{
}

/**
 *  \brief
 *      Return driver ready state (only for non custom driver).
 */
u16  Z80_isDriverReady()
{
	return 0;
}