#include "mapper.h"

/**
 *  \brief
 *      Returns the current bank of specified region index.
 *
 *  \param regionIndex the 512KB region index we want to get. Accepted values: 1-7 as region 0 (0x080000-0x0FFFFF) is fixed.
 *  \return the effective 512KB data bank index mapped on this region (0 to 63)
 */
u16 SYS_getBank( u16 regionIndex )
{
	return 0;
}

/**
 *  \brief
 *      Set the current bank of specified region index.
 *
 *  \param regionIndex the 512KB region index we want to set. Accepted values: 1-7 as region 0 (0x080000-0x0FFFFF) is fixed.
 *  \param bankIndex the effective 512KB data bank index mapped on this region. Accepted values: 0-63
 */
void SYS_setBank( u16 regionIndex, u16 bankIndex )
{
}

/**
 *  \brief
 *      Make the given binary data ressource accessible and return a pointer to it.
 *
 *  \param data far data we want to access.
 *
 * This method will use bank switching to make the specified data accessible and return a valid pointer to it.<br>
 * <b>WARNING:</b> this method use the 0x00300000-0x003FFFFF range (2 regions) to make the requested data accessible using bank switching mechanism.<br>
 * If data bank is already accessible it re-uses the region otherwise it will change bank of one of the region so be careful of that if you want to access data
 * from different data bank at same time :p
 */
void* SYS_getFarData( void* data )
{
	return NULL;
}