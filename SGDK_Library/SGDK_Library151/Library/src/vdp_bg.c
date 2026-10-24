#include "vdp_bg.h"

/**
 *  Contains current VRAM tile position where we will upload next tile data.
 *
 *  \see VDP_drawBitmap()
 *  \see VDP_drawImage()
 */
u16 curTileInd = 0;

/**
 *  \brief
 *      Set plane horizontal scroll (plain scroll mode).<br>
 *      3 horizontal scroll modes are supported:<br>
 *      - Plain (whole plane)<br>
 *      - Tile (8 pixels bloc)<br>
 *      - Line (per pixel scroll)<br>
 *
 *  \param plane
 *      Plane we want to set the horizontal scroll.<br>
 *      Accepted values are:<br>
 *      - BG_A<br>
 *      - BG_B<br>
 *  \param value
 *      H scroll offset.<br>
 *      Negative value will move the plane to the left while positive
 *      value will move it to the right.
 *
 *  \see VDP_setScrollingMode() function to change scroll mode.
 */
void VDP_setHorizontalScroll( VDPPlane plane, s16 value )
{
}

/**
 *  \brief
 *      Set plane horizontal scroll (tile scroll mode).<br>
 *      3 horizontal scroll modes are supported:<br>
 *      - Plain (whole plane)<br>
 *      - Tile (8 pixels bloc)<br>
 *      - Line (per pixel scroll)<br>
 *
 *  \param plane
 *      Plane we want to set the horizontal scroll.<br>
 *      Accepted values are:<br>
 *      - BG_A<br>
 *      - BG_B<br>
 *  \param tile
 *      First tile we want to set the horizontal scroll.
 *  \param values
 *      H scroll offsets.<br>
 *      Negative values will move the plane to the left while positive
 *      values will move it to the right.
 *  \param len
 *      Number of tile to set.
 *  \param tm
 *      Transfer method.<br>
 *      Accepted values are:<br>
 *      - CPU<br>
 *      - DMA<br>
 *      - DMA_QUEUE<br>
 *      - DMA_QUEUE_COPY
 *
 *  \see VDP_setScrollingMode() function to change scroll mode.
 */
void VDP_setHorizontalScrollTile(VDPPlane plane, u16 tile, s16* values, u16 len, TransferMethod tm)
{
}

/**
 *  \brief
 *      Set plane horizontal scroll (line scroll mode).<br>
 *      3 horizontal scroll modes are supported:<br>
 *      - Plain (whole plane)<br>
 *      - Tile (8 pixels bloc)<br>
 *      - Line (per pixel scroll)<br>
 *
 *  \param plane
 *      Plane we want to set the horizontal scroll.<br>
 *      Accepted values are:<br>
 *      - BG_A<br>
 *      - BG_B<br>
 *  \param line
 *      First line we want to set the horizontal scroll.
 *  \param values
 *      H scroll offsets.<br>
 *      Negative values will move the plane to the left while positive values will move it to the right.
 *  \param len
 *      Number of line to set.
 *  \param tm
 *      Transfer method.<br>
 *      Accepted values are:<br>
 *      - CPU<br>
 *      - DMA<br>
 *      - DMA_QUEUE<br>
 *      - DMA_QUEUE_COPY
 *
 *  \see VDP_setScrollingMode()
 */
void VDP_setHorizontalScrollLine(VDPPlane plane, u16 line, s16* values, u16 len, TransferMethod tm)
{
}

/**
 *  \brief
 *      Set plane vertical scroll (plain scroll mode).
 *      2 vertical scroll modes are supported:<br>
 *      - Plain (whole plane)<br>
 *      - 2-Tiles (16 pixels bloc)<br>
 *
 *  \param plane
 *      Plane we want to set the vertical scroll.<br>
 *      Accepted values are:<br>
 *      - BG_A<br>
 *      - BG_B<br>
 *  \param value
 *      V scroll offset.<br>
 *      Negative value will move the plane down while positive value will move it up.
 *
 *  \see VDP_setScrollingMode()
 */
void VDP_setVerticalScroll(VDPPlane plane, s16 value)
{
}

/**
 *  \brief
 *      Set plane vertical scroll (2-Tiles scroll mode).
 *      2 vertical scroll modes are supported:<br>
 *      - Plain (whole plane)<br>
 *      - 2-Tiles (16 pixels bloc)<br>
 *
 *  \param plane
 *      Plane we want to set the vertical scroll.<br>
 *      Accepted values are:<br>
 *      - BG_A<br>
 *      - BG_B<br>
 *  \param tile
 *      First tile we want to set the vertical scroll.
 *  \param values
 *      V scroll offsets.<br>
 *      Negative values will move the plane down while positive values will move it up.
 *  \param len
 *      Number of tile to set.
 *  \param tm
 *      Transfer method.<br>
 *      Accepted values are:<br>
 *      - CPU<br>
 *      - DMA<br>
 *      - DMA_QUEUE<br>
 *      - DMA_QUEUE_COPY
 *
 *  \see VDP_setScrollingMode()
 */
void VDP_setVerticalScrollTile(VDPPlane plane, u16 tile, s16* values, u16 len, TransferMethod tm)
{
}

/**
 *  \brief
 *      Clear specified plane (using DMA).
 *
 *  \param plane
 *      Plane we want to clear.<br>
 *      Accepted values are:<br>
 *      - BG_A<br>
 *      - BG_B<br>
 *      - WINDOW<br>
 *  \param wait
 *      Wait the operation to complete when set to TRUE otherwise it returns immediately
 *      but then you will require to wait for DMA completion (#DMA_waitCompletion()) before accessing the VDP.
 */
void VDP_clearPlane(VDPPlane plane, bool wait)
{
}

/**
 *  \brief
 *      Returns the plane used to display text.
 *
 *  Returned value should be either equals to BG_A, BG_B or WINDOW.
 *
 *  \see VDP_drawText(..)
 *  \see VDP_clearText(..)
 */
VDPPlane VDP_getTextPlane()
{
	return NULL;
}
/**
 *  \brief
 *      Returns the palette number used to display text.
 *
 *  \see VDP_drawText(..)
 *  \see VDP_clearText(..)
 */
u16 VDP_getTextPalette()
{
	return 0;
}

/**
 *  \brief
 *      Returns the priority used to display text.
 *
 *  \see VDP_drawText(..)
 *  \see VDP_clearText(..)
 */
u16 VDP_getTextPriority()
{
	return 0;
}

/**
 *  \brief
 *      Define the plane to use to display text.
 *
 *  \param plane
 *      Plane where to display text.<br>
 *      Accepted values are:<br>
 *      - BG_A<br>
 *      - BG_B<br>
 *      - WINDOW<br>
 *
 *  \see VDP_drawText(..)
 *  \see VDP_clearText(..)
 */
void VDP_setTextPlane(VDPPlane plane)
{
}

/**
 *  \brief
 *      Define the palette to use to display text.
 *
 *  \param palette
 *      Palette number.
 *
 *  \see VDP_drawText(..)
 *  \see VDP_clearText(..)
 */
void VDP_setTextPalette(u16 palette)
{
}

/**
 *  \brief
 *      Define the priority to use to display text.
 *
 *  \param prio
 *      Priority:<br>
 *      1 = HIGH PRIORITY TILE.<br>
 *      0 = LOW PRIORITY TILE.<br>
 *
 *  \see VDP_drawText(..)
 *  \see VDP_clearText(..)
 */
void VDP_setTextPriority(u16 prio)
{
}

/**
 *  \brief
 *      Draw text in specified plane.
 *
 *  \param plane
 *      Plane where we want to draw text.<br>
 *      Accepted values are:<br>
 *      - BG_A<br>
 *      - BG_B<br>
 *      - WINDOW<br>
 *  \param str
 *      String to draw.
 *  \param x
 *      X position (in tile).
 *  \param y
 *      y position (in tile).
 *
 *  \see VDP_clearText(..)
 *  \see VDP_setTextPalette(..)
 *  \see VDP_setTextPriority(..)
 *  \see VDP_setTextPlane(..)
 */
void VDP_drawTextBG(VDPPlane plane, const char *str, u16 x, u16 y)
{
}

/**
 *  \brief
 *      Clear a single line portion of text.
 *
 *  \param plane
 *      Plane where we want to clear text.<br>
 *      Accepted values are:<br>
 *      - BG_A<br>
 *      - BG_B<br>
 *      - WINDOW<br>
 *  \param x
 *      X position (in tile).
 *  \param y
 *      y position (in tile).
 *  \param w
 *      width to clear (in tile).
 *
 *  \see VDP_drawText(..)
 *  \see VDP_clearTextArea(..)
 *  \see VDP_clearTextLine(..)
 */
void VDP_clearTextBG(VDPPlane plane, u16 x, u16 y, u16 w)
{
}

/**
 *  \brief
 *      Clear a specific area of text.
 *
 *  \param plane
 *      Plane where we want to clear text.<br>
 *      Accepted values are:<br>
 *      - BG_A<br>
 *      - BG_B<br>
 *      - WINDOW<br>
 *  \param x
 *      X position (in tile).
 *  \param y
 *      y position (in tile).
 *  \param w
 *      width to clear (in tile).
 *  \param h
 *      heigth to clear (in tile).
 *
 *  \see VDP_drawText(..)
 *  \see VDP_clearText(..)
 *  \see VDP_clearTextLine(..)
 */
void VDP_clearTextAreaBG(VDPPlane plane, u16 x, u16 y, u16 w, u16 h)
{
}

/**
 *  \brief
 *      Clear a complete line of text.
 *
 *  \param plane
 *      Plane where we want to clear text.<br>
 *      Accepted values are:<br>
 *      - BG_A<br>
 *      - BG_B<br>
 *      - WINDOW<br>
 *  \param y
 *      y position (in tile).
 *
 *  \see VDP_drawText(..)
 *  \see VDP_clearText(..)
 *  \see VDP_clearTextArea(..)
 */
void VDP_clearTextLineBG(VDPPlane plane, u16 y)
{
}

/**
 *  \brief
 *      Draw text.
 *
 *  \param str
 *      String to draw.
 *  \param x
 *      X position (in tile).
 *  \param y
 *      y position (in tile).
 *
 *  \see VDP_clearText(..)
 *  \see VDP_setTextPalette(..)
 *  \see VDP_setTextPriority(..)
 *  \see VDP_setTextPlane(..)
 */
void VDP_drawText(const char *str, u16 x, u16 y)
{
}

/**
 *  \brief
 *      Clear a single line portion of text.
 *
 *  \param x
 *      X position (in tile).
 *  \param y
 *      y position (in tile).
 *  \param w
 *      width to clear (in tile).
 *
 *  \see VDP_drawText(..)
 *  \see VDP_clearTextArea(..)
 *  \see VDP_clearTextLine(..)
 */
void VDP_clearText(u16 x, u16 y, u16 w)
{
}

/**
 *  \brief
 *      Clear a specific area of text.
 *
 *  \param x
 *      X position (in tile).
 *  \param y
 *      y position (in tile).
 *  \param w
 *      width to clear (in tile).
 *  \param h
 *      heigth to clear (in tile).
 *
 *  \see VDP_drawText(..)
 *  \see VDP_clearText(..)
 *  \see VDP_clearTextLine(..)
 */
void VDP_clearTextArea(u16 x, u16 y, u16 w, u16 h)
{
}

/**
 *  \brief
 *      Clear a complete line of text.
 *
 *  \param y
 *      y position (in tile).
 *
 *  \see VDP_drawText(..)
 *  \see VDP_clearText(..)
 *  \see VDP_clearTextArea(..)
 */
void VDP_clearTextLine(u16 y)
{
}

/**
 *  \brief
 *      Draw Bitmap in specified background plane and at given position.
 *
 *  \param plane
 *      Plane where we want to draw the bitmap.<br>
 *      Accepted values are:<br>
 *      - BG_A<br>
 *      - BG_B<br>
 *      - WINDOW<br>
 *  \param bitmap
 *      Genesis bitmap (the width and height should be aligned to 8).<br>
 *      The Bitmap is unpacked "on the fly" if needed (require some memory).
 *  \param x
 *      Plane X position (in tile).
 *  \param y
 *      Plane Y position (in tile).
 *  \return
 *      FALSE if there is not enough memory to unpack the specified Bitmap (only if compression was enabled).
 *
 *  This function does "on the fly" 4bpp bitmap conversion to tile data and transfert them to VRAM.<br>
 *  It's very helpful when you use bitmap images but the conversion eats sometime so you should use it only for static screen only.<br>
 *  For "in-game" condition you should use VDP_loadTileData() method with prepared tile data.
 *
 *  \see VDP_loadBMPTileData()
 */
u16 VDP_drawBitmap(VDPPlane plane, const Bitmap *bitmap, u16 x, u16 y)
{
	return 0;
}

/**
 *  \brief
 *      Draw Bitmap in specified background plane and at given position.
 *
 *  \param plane
 *      Plane where we want to draw the bitmap.<br>
 *      Accepted values are:<br>
 *      - BG_A<br>
 *      - BG_B<br>
 *      - WINDOW<br>
 *  \param bitmap
 *      Genesis bitmap (the width and height should be aligned to 8).<br>
 *      The Bitmap is unpacked "on the fly" if needed (require some memory).
 *  \param basetile
 *      Base tile attributes data (see TILE_ATTR_FULL() macro).
 *  \param x
 *      Plane X position (in tile).
 *  \param y
 *      Plane Y position (in tile).
 *  \param loadpal
 *      Load the bitmap palette information when non zero.
 *  \return
 *      FALSE if there is not enough memory to unpack the specified Bitmap (only if compression was enabled).
 *
 *  This function does "on the fly" 4bpp bitmap conversion to tile data and transfert them to VRAM.<br>
 *  It's very helpful when you use bitmap images but the conversion eats sometime so you should use it only for static screen only.<br>
 *  For "in-game" condition you should use VDP_loadTileData() method with prepared tile data.<br>
 *
 *  \see VDP_loadBMPTileData()
 */
u16 VDP_drawBitmapEx( VDPPlane plane, const Bitmap *bitmap, u16 basetile, u16 x, u16 y, u16 loadpal )
{
	return 0;
}

/**
 *  \brief
 *      Draw Image (using DMA) in specified background plane and at given position.
 *
 *  \param plane
 *      Plane where we want to draw the tilemap.<br>
 *      Accepted values are:<br>
 *      - BG_A<br>
 *      - BG_B<br>
 *      - WINDOW<br>
 *  \param image
 *      Image structure to draw.<br>
 *      The Image is unpacked "on the fly" if needed (require some memory).
 *  \param x
 *      Plane X position (in tile).
 *  \param y
 *      Plane Y position (in tile).
 *  \return
 *      FALSE if there is not enough memory to unpack the specified Image (only if compression was enabled).
 *
 *  Load the image tiles data in VRAM and display it at specified plane position.
 *
 *  \see VDP_drawImageEx()
 */
u16 VDP_drawImage(VDPPlane plane, const Image *image, u16 x, u16 y)
{
	return 0;
}

/**
 *  \brief
 *      Draw Image in specified background plane and at given position.
 *
 *  \param plane
 *      Plane where we want to load tilemap.<br>
 *      Accepted values are:<br>
 *      - BG_A<br>
 *      - BG_B<br>
 *      - WINDOW<br>
 *  \param image
 *      Image structure to draw.<br>
 *      The Image is unpacked "on the fly" if needed (require some memory).
 *  \param basetile
 *      Base tile attributes data (see TILE_ATTR_FULL() macro).
 *  \param x
 *      Plane X position (in tile).
 *  \param y
 *      Plane Y position (in tile).
 *  \param loadpal
 *      Load the bitmap palette information when non zero (can be TRUE or FALSE)
 *  \param dma
 *      use DMA
 *  \return
 *      FALSE if there is not enough memory to unpack the specified Image (only if image was packed).
 *
 *  Load the image tiles data in VRAM and display it at specified plane position.
 *
 *  \see VDP_drawImage()
 */
u16 VDP_drawImageEx( VDPPlane plane, const Image *image, u16 basetile, u16 x, u16 y, u16 loadpal, bool dma )
{
	return 0;
}