#include "vram.h"

/**
 *  \brief
 *      Initialize a new VRAM region structure.
 *
 *  \param region
 *      Region to initialize.
 *  \param startIndex
 *      Tile start index in VRAM.
 *  \param size
 *      Size in tile of the region.
 *
 * Set parameters and allocate memory for the VRAM region structure.
 *
 * \see VRAM_releaseRegion(..)
 *
 */
void VRAM_createRegion(VRAMRegion *region, u16 startIndex, u16 size)
{
}

/**
 *  \brief
 *      Release the VRAM region structure.
 *
 *  \param region
 *      VRAMRegion we want to release.
 *
 * Release memory used by the VRAM region structure.
 *
 * \see VRAM_createRegion(..)
 */
void VRAM_releaseRegion(VRAMRegion *region)
{
}

/**
 *  \brief
 *      Release all allocations from specified VRAM region.
 *
 *  \param region
 *      VRAM region we want to clear.
 */
void VRAM_clearRegion(VRAMRegion *region)
{
}

/**
 *  \brief
 *      Return the number of free tile remaining in the specified VRAM region.
 *
 *  \param region
 *      VRAM region
 *  \return
 *      the number of free tile in the specified VRAM region
 */
u16 VRAM_getFree(VRAMRegion *region)
{
	return 0;
}

/**
 *  \brief
 *      Return the number of allocated tile in the specified VRAM region.
 *
 *  \param region
 *      VRAM region
 *  \return
 *      the number of allocated tile in the specified VRAM region.
 */
u16 VRAM_getAllocated(VRAMRegion *region)
{
	return 0;
}

/**
 *  \brief
 *      Return the largest free block index in the specified VRAM region.
 *
 *  \param region
 *      VRAM region
 *  \return
 *      the largest free block index in the specified VRAM region.
 */
u16 VRAM_getLargestFreeBlock(VRAMRegion *region)
{
	return 0;
}

/**
 *  \brief
 *      Try to allocate the specified number of tile in the given VRAM region and return its index.
 *
 *  \param region
 *      VRAM region
 *  \param size
 *      Number of tile we want to allocate in VRAM (need to be > 0).
 *  \return
 *      the index in VRAM where we allocated the bloc of tile.<br>
 *      -1 if there is no enough available VRAM in the region.
 *
 *  \see VRAM_free(..)
 */
s16 VRAM_alloc(VRAMRegion *region, u16 size)
{
	return 0;
}

/**
 *  \brief
 *      Release the previously allocated VRAM block at specified index in the given VRAM region.<br>
 *
 *  \param region
 *      VRAM region
 *  \param index
 *      The index of the VRAM block we want to release
 *
 *  \see VRAM_alloc(..)
 */
void VRAM_free(VRAMRegion *region, u16 index)
{
}