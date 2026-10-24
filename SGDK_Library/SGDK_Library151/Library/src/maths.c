#include "maths.h"

const fix32 sintab32[1024] = { 0 };
const fix16 sintab16[1024] = { 0 };

#if (MATH_BIG_TABLES != 0)
const fix16 log2tab16[0x10000] = { 0 };
const fix16 log10tab16[0x10000] = { 0 };
const fix16 sqrttab16[0x10000] = { 0 };
#endif

/**
 *  \brief
 *      Binary to Decimal conversion.
 *
 *  \param value
 *      Value to convert.
 */
u32 intToBCD( u32 value )
{
	return 0;
}

/**
 *  \deprecated
 *      Use #getApproximatedDistance(..) instead.
 */
u32 distance_approx(s32 dx, s32 dy)
{
	return 0;
}

/**
 *  \brief
 *      Return euclidean distance approximation for specified vector.<br>
 *      The returned distance is not 100% perfect but calculation is fast.
 *
 *  \param dx
 *      delta X.
 *  \param dy
 *      delta Y.
 */
u32 getApproximatedDistance(s32 dx, s32 dy)
{
	return 0;
}

/**
 *  \brief
 *      Return 16.16 fixed point *approximation* of log2 of the specified 16.16 fixed point value.
 *      Ex:<br>
 *      getLog2(1 << 16) = 0<br>
 *      getLog2(12345 << 16) = ~9.5 (real value = ~13.6)<br>
 *
 *  \param value
 *      16.16 fixed point value to return log2 of
 */
s32 getApproximatedLog2(s32 value)
{
	return 0;
}

/**
 *  \brief
 *      Return integer log2 of specified 32 bits unsigned value.
 *      Ex:<br>
 *      getLog2Int(1024) = 10<br>
 *      getLog2Int(12345) = 13<br>
 *
 *  \param value
 *      value to return log2 of
 */
u16 getLog2Int(u32 value)
{
	return 0;
}