#include "vdp.h"

// used by define
u16 window_addr = 0;
u16 bga_addr = 0;
u16 bgb_addr = 0;
u16 hscrl_addr = 0;
u16 slist_addr = 0;
u16 maps_addr = 0;
u16 userTileMaxIndex = 0;

/**
 *  \brief
 *      Current screen width (horizontale resolution)
 */
u16 screenWidth = 0;
/**
 *  \brief
 *      Current screen height (verticale resolution)
 */
u16 screenHeight = 0;
/**
 *  \brief
 *      Current background plane width (in tile)
 *
 *  Possible values are: 32, 64, 128
 */
u16 planeWidth = 0;
/**
 *  \brief
 *      Current background plane height (in tile)
 *
 *  Possible values are: 32, 64, 128
 */
u16 planeHeight = 0;
/**
 *  \brief
 *      Current window width (in tile)
 *
 *  Possible values are: 32, 64
 */
u16 windowWidth = 0;
/**
 *  \brief
 *      Current background plane width bit shift
 *
 *  Possible values are: 5, 6 or 7 (corresponding to plane width 32, 64 and 128)
 */
u16 planeWidthSft = 0;
/**
 *  \brief
 *      Current background plane height bit shift
 *
 *  Possible values are: 5, 6 or 7 (corresponding to plane height 32, 64 and 128)
 */
u16 planeHeightSft = 0;
/**
 *  \brief
 *      Current window width bit shift
 *
 *  Possible values are: 5 or 6 (corresponding to window width 32 or 64)
 */
u16 windowWidthSft = 0;


/**
 *  \brief
 *      Initialize the VDP sub system.
 *
 * Reset VDP registers, clear VRAM, set defaults grey, red, green & blue palette.
 */
void VDP_init()
{
}

/**
 *  \brief
 *      Reset background plane and palette.
 *
 *  Clear background plans, reset palette to grey / red / green / blue and reset scrolls.
 */
void VDP_resetScreen()
{
}

/**
 *  \brief
 *      Get VDP register value.
 *
 *  \param reg
 *      Register number we want to retrieve value.
 *  \return specified register value.
 */
u8 VDP_getReg( u16 reg )
{
	return 0;
}

/**
 *  \brief
 *      Set VDP register value.
 *
 *  \param reg
 *      Register number we want to set value.
 *  \param value
 *      value to set.
 */
void VDP_setReg(u16 reg, u8 value)
{
}

/**
 *  \brief
 *      Returns VDP enable state.
 */
u8 VDP_getEnable()
{
	return 0;
}
/**
 *  \brief
 *      Set VDP enable state.
 *
 *  You can temporary disable VDP to speed up VDP memory transfert.
 */
void VDP_setEnable( u8 value ) 
{
}

/**
 *  \brief
 *      Returns number of total scanline.
 *
 *  312 for PAL system and 262 for NTSC system.
 */
u16  VDP_getScanlineNumber()
{
	return 0;
}

/**
 *  \brief
 *      Returns vertical screen resolution.
 *
 *  Always returns 224 on NTSC system as they only support this mode.<br>
 *  PAL system supports 240 pixels mode.
 */
u16  VDP_getScreenHeight()
{
	return 0;
}

/**
 *  \brief
 *      Set vertical resolution to 224 pixels.
 *
 *  This is the only accepted mode for NTSC system.
 */
void VDP_setScreenHeight224()
{
}

/**
 *  \brief
 *      Set vertical resolution to 240 pixels.
 *
 *  Only work on PAL system.
 */
void VDP_setScreenHeight240()
{
}

/**
 *  \brief
 *      Returns horizontal screen resolution.
 *
 *  Returns 320 or 256 depending current horizontal resolution mode.
 */
u16  VDP_getScreenWidth()
{
	return 0;
}

/**
 *  \brief
 *      Set horizontal resolution to 256 pixels.
 */
void VDP_setScreenWidth256()
{
}

/**
 *  \brief
 *      Set horizontal resolution to 320 pixels.
 */
void VDP_setScreenWidth320()
{
}

/**
 *  \brief
 *      Return background plane width (in tile).
 */
u16 VDP_getPlaneWidth()
{
	return 0;
}

/**
 *  \brief
 *      Return background plane height (in tile).
 */
u16 VDP_getPlaneHeight()
{
	return 0;
}

/**
 *  \brief
 *      Set background plane size (in tile).<br>
 *      WARNING: take attention to properly setup VRAM so tilemaps has enough space.
 *
 *  \param w
 *      width in tile.<br>
 *      Possible values are 32, 64 or 128.
 *  \param h
 *      height in tile.<br>
 *      Possible values are 32, 64 or 128.
 *  \param setupVram
 *      If set to TRUE then tilemaps and tables will be automatically remapped in VRAM depending
 *      the plane size.<br>
 *      If you don't know what that means then it's better to keep this value to TRUE :p
 */
void VDP_setPlaneSize(u16 w, u16 h, bool setupVram)
{
}

/**
 *  \deprecated
 *      Use #VDP_setPlaneSize(..) instead.
 */
void VDP_setPlanSize(u16 w, u16 h)
{
}

/**
 *  \brief
 *      Returns plane horizontal scrolling mode.
 *
 *  Possible values are: HSCROLL_PLANE, HSCROLL_TILE, HSCROLL_LINE
 *
 *  \see VDP_setScrollingMode for more informations about scrolling mode.
 */
u8 VDP_getHorizontalScrollingMode()
{
	return 0;
}

/**
 *  \brief
 *      Returns plane vertical scrolling mode.
 *
 *  Possible values are: VSCROLL_PLANE, VSCROLL_2TILE
 *
 *  \see VDP_setScrollingMode for more informations about scrolling mode.
 */
u8 VDP_getVerticalScrollingMode()
{
	return 0;
}

/**
 *  \brief
 *      Set plane scrolling mode.
 *
 *  \param hscroll
 *      Horizontal scrolling mode :<br>
 *      <b>HSCROLL_PLANE</b> = Scroll offset is applied to the whole plane.<br>
 *      <b>HSCROLL_TILE</b> = Scroll offset is applied on a tile basis granularity (8 pixels bloc).<br>
 *      <b>HSCROLL_LINE</b> = Scroll offset is applied on a line basis granularity (1 pixel).<br>
 *  \param vscroll
 *      Vertical scrolling mode :<br>
 *      <b>VSCROLL_PLANE</b> = Scroll offset is applied to the whole plane.<br>
 *      <b>VSCROLL_2TILE</b> = Scroll offset is applied on 2 tiles basis granularity (16 pixels bloc).<br>
 *
 *  \see VDP_setHorizontalScroll() to set horizontal scroll offset in mode plane.<br>
 *  \see VDP_setHorizontalScrollTile() to set horizontal scroll offset(s) in mode tile.<br>
 *  \see VDP_setHorizontalScrollLine() to set horizontal scroll offset(s) in mode line.<br>
 *  \see VDP_setVerticalScroll() to set vertical scroll offset in mode plane.<br>
 *  \see VDP_setVerticalScrollTile() to set vertical scroll offset(s) in mode 2-tile.<br>
 */
void VDP_setScrollingMode(u16 hscroll, u16 vscroll)
{
}

/**
 *  \brief
 *      Returns the background color index.
 */
u8 VDP_getBackgroundColor()
{
	return 0;
}

/**
 *  \brief
 *      Set the background color index.
 */
void VDP_setBackgroundColor(u8 value)
{
}

/**
 *  \brief
 *      Returns auto increment register value.
 */
u8 VDP_getAutoInc()
{
	return 0;
}

/**
 *  \brief
 *      Set auto increment register value.
 */
void VDP_setAutoInc(u8 value)
{
}

/**
 *  \brief
 *      Returns DMA enabled state
 */
u8 VDP_getDMAEnabled()
{
	return 0;
}

/**
 *  \brief
 *      Set DMA enabled state.
 *
 *  Note that by default SGDK always enable DMA (there is no reason to disable it)
 */
void VDP_setDMAEnabled(u8 value)
{
}

/**
 *  \brief
 *      Returns HV counter latching on INT2 (used for light gun)
 */
u8 VDP_getHVLatching()
{
	return 0;
}

/**
 *  \brief
 *      Set HV counter latching on INT2 (used for light gun)
 *
 *  You can ask the HV Counter to fix its value on INT2 for accurate light gun positionning.
 */
void VDP_setHVLatching(u8 value)
{
}

/**
 *  \brief
 *      Enable or Disable Horizontal interrupt.
 *
 *  \see VDP_setHIntCounter()
 */
void VDP_setHInterrupt(u8 value)
{
}

/**
 *  \brief
 *      Enable or Disable Hilight / Shadow effect.
 */
void VDP_setHilightShadow(u8 value)
{
}

/**
 *  \brief
 *      Get Horizontal interrupt counter value.
 */
u8 VDP_getHIntCounter()
{
	return 0;
}

/**
 *  \brief
 *      Set Horizontal interrupt counter value.
 *
 *  When Horizontal interrupt is enabled, setting 5 here means that H int will occurs each (5+1) scanline.<br>
 *  Set value 0 to get H int at each scanline.
 */
void VDP_setHIntCounter(u8 value)
{
}

/**
 *  \brief
 *      Get VRAM address (location) of BG A tilemap.
 */
u16 VDP_getBGAAddress()
{
	return 0;
}

/**
 *  \brief
 *      Get VRAM address (location) of BG B tilemap.
 */
u16 VDP_getBGBAddress()
{
	return 0;
}

/**
 *  \deprecated
 *      Use #VDP_getBGAAddress(..) instead.
 */
u16 VDP_getAPlanAddress()
{
	return 0;
}

/**
 *  \deprecated
 *      Use #VDP_getBGBAddress(..) instead.
 */
u16 VDP_getBPlanAddress()
{
	return 0;
}

/**
 *  \brief
 *      Get VRAM address (location) of Window tilemap.
 */
u16 VDP_getWindowAddress()
{
	return 0;
}

/**
 *  \deprecated
 *      Use #VDP_getWindowAddress(..) instead.
 */
u16 VDP_getWindowPlanAddress()
{
	return 0;
}

/**
 *  \brief
 *      Get VRAM address (location) of Sprite list.
 */
u16 VDP_getSpriteListAddress()
{
	return 0;
}

/**
 *  \brief
 *      Get VRAM address (location) of H SCroll table.
 */
u16 VDP_getHScrollTableAddress()
{
	return 0;
}

/**
 *  \brief
 *      Set VRAM address (location) of BG A tilemap.
 *      The address should be at multiple of $2000<br>
 *      <br>
 *      Ex:<br>
 *      VDP_setBGAAddress(0xC000)<br>
 *      Will set the BG A to at address 0xC000 in VRAM.
 */
void VDP_setBGAAddress( u16 value )
{
}

/**
 *  \brief
 *      Set VRAM address (location) of BG B tilemap.<br>
 *      The address should be at multiple of $2000<br>
 *      <br>
 *      Ex:<br>
 *      VDP_setBGBAddress(0xE000)<br>
 *      Will set the BG B tilemap at address 0xE000 in VRAM.
 */
void VDP_setBGBAddress(u16 value)
{
}

/**
 *  \deprecated
 *      Use #VDP_setWindowAddress(..) instead.
 */
void VDP_setAPlanAddress(u16 value)
{
}

/**
 *  \deprecated
 *      Use #VDP_setWindowAddress(..) instead.
 */
void VDP_setBPlanAddress(u16 value)
{
}

/**
 *  \brief
 *      Set VRAM address (location) of Window tilemap.<br>
 *      The address should be at multiple of $1000 in H40 and $800 in H32<br>
 *      <br>
 *      Ex:<br>
 *      VDP_setWindowAddress(0xA000)<br>
 *      Will set the Window tilemap at address 0xA000 in VRAM.
 */
void VDP_setWindowAddress(u16 value)
{
}

/**
 *  \deprecated
 *      Use #VDP_setWindowAddress(..) instead.
 */
void VDP_setWindowPlanAddress(u16 value)
{
}

/**
 *  \brief
 *      Set VRAM address (location) of Sprite list.<br>
 *      The address should be at multiple of $400 in H40 and $200 in H32<br>
 *      <br>
 *      Ex:<br>
 *      VDP_setSpriteListAddress(0xD800)<br>
 *      Will set the Sprite list to at address 0xD800 in VRAM.
 */
void VDP_setSpriteListAddress(u16 value)
{
}

/**
 *  \brief
 *      Set VRAM address (location) of H Scroll table.<br>
 *      The address should be at multiple of $400<br>
 *      <br>
 *      Ex:<br>
 *      VDP_setHScrollTableAddress(0xD400)<br>
 *      Will set the HScroll table to at address 0xD400 in VRAM.
 */
void VDP_setHScrollTableAddress(u16 value)
{
}

/**
 *  \brief
 *      Sets the scan mode of the display.
 *
 *  \param mode
 *      Accepted values : #INTERLACED_NONE, #INTERLACED_MODE1, #INTERLACED_MODE2
 *
 * This function changes the scanning mode on the next display blanking period.<br>
 * In Interlaced Mode 1, the same pattern will be displayed on the adjacent lines of even and odd numbered fields.<br>
 * In Interlaced Mode 2, different patterns can be displayed on the adjacent lines of even and odd numbered fields.<br>
 * The number of cells on the screen stays the same regardless of which scanning mode is active.
 */
void VDP_setScanMode(u16 mode)
{
}

/**
 *  \brief
 *      Sets the window Horizontal position.
 *
 *  \param right
 *      If set to <i>FALSE</i> the window is displayed from column 0 up to column <i>pos</i>
 *      If set to <i>TRUE</i> the window is displayed from column <i>pos</i> up to last column
 *  \param pos
 *      The Horizontal position of the window in 2 tiles unit (16 pixels).
 */
void VDP_setWindowHPos(u16 right, u16 pos)
{
}

/**
 *  \brief
 *      Sets the window Vertical position.
 *
 *  \param down
 *      If set to <i>FALSE</i> the window is displayed from row 0 up to row <i>pos</i>
 *      If set to <i>TRUE</i> the window is displayed from row <i>pos</i> up to last row
 *  \param pos
 *      The Vertical position of the window in 1 tile unit (8 pixels).
 */
void VDP_setWindowVPos(u16 down, u16 pos)
{
}

/**
 *  \brief
 *      Wait for DMA operation to complete.
 *  \deprecated Use #DMA_waitCompletion() instead
 */
void VDP_waitDMACompletion()
{
}

/**
 *  \brief
 *      Wait for VDP FIFO to be empty.
 */
void VDP_waitFIFOEmpty()
{
}

/**
 *  \brief
 *      Wait for Vertical Synchro.
 *
 *  The method actually wait for the next start of Vertical blanking.
 */
void VDP_waitVSync()
{
}

/**
 *  \brief
 *      Wait for next Vertical Interruption.
 *
 *  The method actually wait for the next start of Vertical Interruption.
 *  It returns immediately if we are already in VInt handler.
 */
void VDP_waitVInt()
{
}

/**
 *  \brief
 *      Wait for next vertical blank period (same as #VDP_waitVSync())
 *
 *  The method actually wait for the next start of Vertical blanking.
 */
void VDP_waitVBlank()
{
}

/**
 *  \brief
 *      Wait for next vertical active area (end of vertical blank period)
 *
 *  The method actually wait for the next start of Vertical active area.
 */
void VDP_waitVActive()
{
}

/**
 *  \brief
 *      Return an enhanced V Counter representation.
 *
 *  Using direct V counter from VDP may give troubles as the VDP V-Counter rollback during V-Blank period.<br>
 *  This function aim to make ease the use of V-Counter by adjusting it to a [0-255] range where 0 is the start of VBlank area and 255 the end of active display area.
 */
u16 VDP_getAdjustedVCounter()
{
	return 0;
}

/**
 *  \brief
 *      Display number of Frame Per Second.
 *
 *  \param asFloat
 *      Display in float number format.
 *
 * This function actually display the number of time it was called in the last second.<br>
 * i.e: for benchmarking you should call this method only once per frame update.
 *
 * \see #getFPS(..)
 */
void VDP_showFPS(u16 asFloat)
{
}

/**
 *  \brief
 *      Display the estimated CPU load (in %).
 *
 * This function actually display an estimation of the CPU load (in %) for the last frame.
 *
 * \see #SYS_getCPULoad()
 */
void VDP_showCPULoad()
{
}