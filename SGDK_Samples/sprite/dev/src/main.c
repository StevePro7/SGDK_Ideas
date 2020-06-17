#include "main.h"

#define SFX_JUMP            64
#define SFX_ROLL            65
#define SFX_STOP            66

#define ANIM_STAND          0
#define ANIM_WAIT           1
#define ANIM_WALK           2
#define ANIM_RUN            3
#define ANIM_BRAKE          4
#define ANIM_UP             5
#define ANIM_CROUNCH        6
#define ANIM_ROLL           7

#define MAX_SPEED_MAX       FIX32(20L)
#define MAX_SPEED_MIN       FIX32(1L)
#define MAX_SPEED_DEFAULT   FIX32(8L)

#define RUN_SPEED           FIX32(6L)
#define BRAKE_SPEED         FIX32(2L)

#define JUMP_SPEED_MIN      FIX32(4L)
#define JUMP_SPEED_MAX      FIX32(15L)
#define JUMP_SPEED_DEFAULT  FIX32(7.8L)

#define GRAVITY_MIN         FIX32(0.15)
#define GRAVITY_MAX         FIX32(0.8)
#define GRAVITY_DEFAULT     FIX32(0.32)

#define ACCEL               FIX32(0.1)
#define DE_ACCEL            FIX32(0.15)

#define MIN_POSX            FIX32(10L)
#define MAX_POSX            FIX32(4000L)
#define MAX_POSY            FIX32(414L)


// forward
static void handleInput();
static void joyEvent( u16 joy, u16 changed, u16 state );

static void setSpritePosition( Sprite* sprite, s16 posX, s16 posY );

static void updateBarsVisitility();
static void updateBar( Sprite* bar, f32 min, f32 max, f32 current );
static void updatePhysic();
static void updateAnim();

static void updateCameraPosition();
static void setCameraPosition( s16 x, s16 y );
static void updateMap( VDPPlane plane, TileMap* tileMap, s16 xt, s16 yt );

static void updateVDPScroll();

static void frameChanged( Sprite* sprite );

TileMap* bgb;
TileMap* bga;

// player (sonic) sprite
Sprite* player;
// enemies sprites
Sprite* enemies[ 2 ];

// Speed, Jump and Gravity interface
Sprite* bars[ 3 ];

// maps (BGA and BGB) position (tile)
s16 mapTilePosX[ 2 ];
s16 mapTilePosY[ 2 ];
// absolute camera position (pixel)
s16 camPosX;
s16 camPosY;
// require scroll update
bool scrollNeedUpdate;

fix32 maxSpeed;
fix32 jumpSpeed;
fix32 gravity;

fix32 posX;
fix32 posY;
fix32 movX;
fix32 movY;
s16 xOrder;
s16 yOrder;

fix32 enemiesPosX[ 2 ];
fix32 enemiesPosY[ 2 ];
s16 enemiesXOrder[ 2 ];

// animation index table for enemies (static VRAM loading)
u16** sprTileIndexes[ 2 ];
// BG start tile index
u16 bgBaseTileIndex[ 2 ];

//s16 reseted = TRUE;
bool paused;

int main()
{
	u16 palette[ 64 ];
	u16 ind;
	u16 numTile;
	u16 *data;

	// disable interrupt when accessing VDP
	SYS_disableInts();
	// initialization
	VDP_setScreenWidth320();

	// init SFX
	SND_setPCM_XGM( SFX_JUMP, sonic_jump_sfx, sizeof( sonic_jump_sfx ) );
	SND_setPCM_XGM( SFX_ROLL, sonic_roll_sfx, sizeof( sonic_roll_sfx ) );
	SND_setPCM_XGM( SFX_STOP, sonic_stop_sfx, sizeof( sonic_stop_sfx ) );
	// start music
	SND_startPlay_XGM( sonic_music );

	// init sprite engine with default parameters
	SPR_init();

	// set all palette to black
	VDP_setPaletteColors( 0, ( u16* ) palette_black, 64 );

	// load background tilesets in VRAM
	ind = TILE_USERINDEX;
	bgBaseTileIndex[ 0 ] = ind;
	VDP_loadTileSet( bga_image.tileset, ind, DMA );

	numTile = 0;
#ifndef _CONSOLE
	numTile = bga_image.tileset->numTile;
#endif
	//ind += bga_image.tileset->numTile;
	ind += numTile;

	bgBaseTileIndex[ 1 ] = ind;
	VDP_loadTileSet( bgb_image.tileset, ind, DMA );

	numTile = 0;
#ifndef _CONSOLE
	numTile = bgb_image.tileset->numTile;
#endif
	//ind += bgb_image.tileset->numTile;
	ind += numTile;

	// BG A is too big to fit in RAM so it is stored unpacked in ROM (need to work that out)
	bga = bga_image.tilemap;
	// unpack BG B map (small enough to fit in RAM)
	bgb = unpackTileMap( bgb_image.tilemap, NULL );

	// draw backgrounds
	//    VDP_setTileMapEx(BG_A, bga, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, bgBaseTileIndex[0]), 0, 0, 0, 0 + 32, 42, 32, DMA);
	//    VDP_setTileMapEx(BG_B, bgb, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, bgBaseTileIndex[1]), 0, 0, 0, 0, 42, 32, DMA);

	// VDP process done, we can re enable interrupts
	SYS_enableInts();

	paused = FALSE;

	// BGB/BGA tile position (force refresh)
	mapTilePosX[ 0 ] = -100;
	mapTilePosY[ 0 ] = -100;
	mapTilePosX[ 1 ] = -100;
	mapTilePosY[ 1 ] = -100;
	// camera position (force refresh)
	camPosX = -1;
	camPosY = -1;
	scrollNeedUpdate = FALSE;

	maxSpeed = MAX_SPEED_DEFAULT;
	jumpSpeed = JUMP_SPEED_DEFAULT;
	gravity = GRAVITY_DEFAULT;

	// set main sprite position (camera position may be adjusted depending it)
	posX = FIX32( 48L );
	posY = MAX_POSY;
	movX = FIX32( 0 );
	movY = FIX32( 0 );
	xOrder = 0;
	yOrder = 0;

	enemiesPosX[ 0 ] = FIX32( 300L );
	enemiesPosY[ 0 ] = FIX32( 304L );
	enemiesPosX[ 1 ] = FIX32( 128L );
	enemiesPosY[ 1 ] = FIX32( 418L );
	enemiesXOrder[ 0 ] = -1;
	enemiesXOrder[ 1 ] = 1;

	// init scrolling
	updateCameraPosition();
	updateVDPScroll();

	// init sonic sprite
	player = SPR_addSprite( &sonic_sprite, fix32ToInt( posX ) - camPosX, fix32ToInt( posY ) - camPosY, TILE_ATTR( PAL0, TRUE, FALSE, FALSE ) );
	// init enemies sprites
	enemies[ 0 ] = SPR_addSprite( &enemy01_sprite, fix32ToInt( enemiesPosX[ 0 ] ) - camPosX, fix32ToInt( enemiesPosY[ 0 ] ) - camPosY, TILE_ATTR( PAL0, TRUE, FALSE, FALSE ) );
	enemies[ 1 ] = SPR_addSprite( &enemy02_sprite, fix32ToInt( enemiesPosX[ 1 ] ) - camPosX, fix32ToInt( enemiesPosY[ 1 ] ) - camPosY, TILE_ATTR( PAL0, TRUE, FALSE, FALSE ) );

	// Speed, Jump and Gravity setting interface
	bars[ 0 ] = SPR_addSprite( &sbar_sprite, 10, 180, TILE_ATTR( PAL0, TRUE, FALSE, FALSE ) );
	bars[ 1 ] = SPR_addSprite( &jbar_sprite, 18, 180, TILE_ATTR( PAL0, TRUE, FALSE, FALSE ) );
	bars[ 2 ] = SPR_addSprite( &gbar_sprite, 26, 180, TILE_ATTR( PAL0, TRUE, FALSE, FALSE ) );

	// disable auto tile upload for enemies sprites as we will pre-load all animation frams in VRAM for them
	SPR_setAutoTileUpload( enemies[ 0 ], FALSE );
	SPR_setAutoTileUpload( enemies[ 1 ], FALSE );
	// set frame change callback for enemies so we can update tile index easily
	SPR_setFrameChangeCallback( enemies[ 0 ], &frameChanged );
	SPR_setFrameChangeCallback( enemies[ 1 ], &frameChanged );

	// pre-load all animation frames into VRAM for enemies
	sprTileIndexes[ 0 ] = SPR_loadAllFrames( &enemy01_sprite, ind, &numTile );
	ind += numTile;
	sprTileIndexes[ 1 ] = SPR_loadAllFrames( &enemy02_sprite, ind, &numTile );
	ind += numTile;

	// store enemy 'sprTileIndexes' table index in 'data' field (can be used freely)
	if( NULL != enemies[0] )
	{
		enemies[ 0 ]->data = 0;
	}
	if( NULL != enemies[ 1 ] )
	{
		enemies[ 1 ]->data = 1;
	}

	// update BAR sprites
	updateBar( bars[ 0 ], MAX_SPEED_MIN, MAX_SPEED_MAX, maxSpeed );
	updateBar( bars[ 1 ], JUMP_SPEED_MIN, JUMP_SPEED_MAX, jumpSpeed );
	updateBar( bars[ 2 ], GRAVITY_MIN, GRAVITY_MAX, gravity );
	updateBarsVisitility();

	SPR_update();

	// prepare palettes (BGB image contains the 4 palettes data)
	data = NULL;
#ifndef _CONSOLE
	data = bgb_image.palette->data;
#endif
	//memcpy( &palette[ 0 ], bgb_image.palette->data, 64 * 2 );
	memcpy( &palette[ 0 ], data, 64 * 2 );
	//    memcpy(&palette[16], bga_image.palette->data, 16 * 2);
	//    memcpy(&palette[32], sonic_sprite.palette->data, 16 * 2);
	//    memcpy(&palette[48], enemies_sprite.palette->data, 16 * 2);

	// fade in
	VDP_fadeIn( 0, ( 4 * 16 ) - 1, palette, 20, FALSE );

	JOY_setEventHandler( joyEvent );

	// just to monitor frame CPU usage
	SYS_showFrameLoad();

	//    reseted = FALSE;

	while( TRUE )
	{
		handleInput();

		if( !paused )
		{
			// update internal sprite position
			updatePhysic();
			updateAnim();
		}

		// update sprites
		SPR_update();

		VDP_waitVInt();

		if( scrollNeedUpdate )
		{
			updateVDPScroll();
			scrollNeedUpdate = FALSE;
		}

		//        KLog_U1("CPU usage = ", SYS_getCPULoad());
	}

	return 0;
}


static void updateBarsVisitility()
{
	if( paused )
	{
		SPR_setVisibility( bars[ 0 ], VISIBLE );
		SPR_setVisibility( bars[ 1 ], VISIBLE );
		SPR_setVisibility( bars[ 2 ], VISIBLE );
	}
	else
	{
		SPR_setVisibility( bars[ 0 ], HIDDEN );
		SPR_setVisibility( bars[ 1 ], HIDDEN );
		SPR_setVisibility( bars[ 2 ], HIDDEN );
	}
}

static void updateBar( Sprite* bar, f32 min, f32 max, f32 current )
{
	f32 levelf;
	s16 leveli;

	levelf = fix32Mul( current, FIX32( 16 ) );
	levelf = fix32Div( levelf, ( max - min ) );
	levelf -= min;

	leveli = fix32ToInt( levelf );
	if( leveli < 0 ) leveli = 0;
	else if( leveli > 16 ) leveli = 16;

	SPR_setFrame( bar, leveli );
}

static void updatePhysic()
{
	u16 i;

	// sonic physic
	if( xOrder > 0 )
	{
		movX += ACCEL;
		// going opposite side, quick breaking
		if( movX < 0 ) movX += ACCEL;

		if( movX >= maxSpeed ) movX = maxSpeed;
	}
	else if( xOrder < 0 )
	{
		movX -= ACCEL;
		// going opposite side, quick breaking
		if( movX > 0 ) movX -= ACCEL;

		if( movX <= -maxSpeed ) movX = -maxSpeed;
	}
	else
	{
		if( ( movX < FIX32( 0.1 ) ) && ( movX > FIX32( -0.1 ) ) )
			movX = 0;
		else if( ( movX < FIX32( 0.3 ) ) && ( movX > FIX32( -0.3 ) ) )
			movX -= movX >> 2;
		else if( ( movX < FIX32( 1 ) ) && ( movX > FIX32( -1 ) ) )
			movX -= movX >> 3;
		else
			movX -= movX >> 4;
	}

	posX += movX;
	posY += movY;

	if( movY )
	{
		if( posY > MAX_POSY )
		{
			posY = MAX_POSY;
			movY = 0;
		}
		else movY += gravity;
	}

	if( posX >= MAX_POSX )
	{
		posX = MAX_POSX;
		movX = 0;
	}
	else if( posX <= MIN_POSX )
	{
		posX = MIN_POSX;
		movX = 0;
	}

	// enemies physic
	if( enemiesXOrder[ 0 ] > 0 ) enemiesPosX[ 0 ] += FIX32( 1.5 );
	else enemiesPosX[ 0 ] -= FIX32( 1.5 );
	if( enemiesXOrder[ 1 ] > 0 ) enemiesPosX[ 1 ] += FIX32( 0.7 );
	else enemiesPosX[ 1 ] -= FIX32( 0.7 );
	for( i = 0; i < 2; i++ )
	{
		if( ( enemiesPosX[ i ] >= MAX_POSX ) || ( enemiesPosX[ i ] <= MIN_POSX ) )
			enemiesXOrder[ i ] = -enemiesXOrder[ i ];
	}

	// update camera position (*after* player sprite position has been updated)
	updateCameraPosition();

	// set sprites position
	setSpritePosition( player, fix32ToInt( posX ) - camPosX, fix32ToInt( posY ) - camPosY );
	setSpritePosition( enemies[ 0 ], fix32ToInt( enemiesPosX[ 0 ] ) - camPosX, fix32ToInt( enemiesPosY[ 0 ] ) - camPosY );
	setSpritePosition( enemies[ 1 ], fix32ToInt( enemiesPosX[ 1 ] ) - camPosX, fix32ToInt( enemiesPosY[ 1 ] ) - camPosY );
}

static void setSpritePosition( Sprite* sprite, s16 x, s16 y )
{
	// clip out of screen sprites
	if( ( x < -100 ) || ( x > 320 ) || ( y < -100 ) || ( y > 240 ) ) SPR_setVisibility( sprite, HIDDEN );
	else
	{
		SPR_setVisibility( sprite, VISIBLE );
		SPR_setPosition( sprite, x, y );
	}
}

static void updateAnim()
{
	// jumping
	if( movY ) SPR_setAnim( player, ANIM_ROLL );
	else
	{
		if( ( ( movX >= BRAKE_SPEED ) && ( xOrder < 0 ) ) || ( ( movX <= -BRAKE_SPEED ) && ( xOrder > 0 ) ) )
		{
			if( player->animInd != ANIM_BRAKE )
			{
				SND_startPlayPCM_XGM( SFX_STOP, 1, SOUND_PCM_CH2 );
				SPR_setAnim( player, ANIM_BRAKE );
			}
		}
		else if( ( movX >= RUN_SPEED ) || ( movX <= -RUN_SPEED ) )
			SPR_setAnim( player, ANIM_RUN );
		else if( movX != 0 )
			SPR_setAnim( player, ANIM_WALK );
		else
		{
			if( yOrder < 0 )
				SPR_setAnim( player, ANIM_UP );
			else if( yOrder > 0 )
				SPR_setAnim( player, ANIM_CROUNCH );
			else
				SPR_setAnim( player, ANIM_STAND );
		}
	}

	if( movX > 0 ) SPR_setHFlip( player, FALSE );
	else if( movX < 0 ) SPR_setHFlip( player, TRUE );

	// enemies
	if( enemiesXOrder[ 0 ] > 0 ) SPR_setHFlip( enemies[ 0 ], TRUE );
	else SPR_setHFlip( enemies[ 0 ], FALSE );
	//    for(i = 0; i < 2; i++)
	//    {
	//        if (enemiesXOrder[i] > 0) SPR_setHFlip(sprites[i + 1], TRUE);
	//        else SPR_setHFlip(sprites[i + 1], FALSE);
	//    }
}

static void updateCameraPosition()
{
	// get player position (pixel)
	s16 px = fix32ToInt( posX );
	s16 py = fix32ToInt( posY );
	// current sprite position on screen
	s16 px_scr = px - camPosX;
	s16 py_scr = py - camPosY;

	s16 npx_cam, npy_cam;

	// adjust new camera position
	if( px_scr > 240 ) npx_cam = px - 240;
	else if( px_scr < 40 ) npx_cam = px - 40;
	else npx_cam = camPosX;
	if( py_scr > 140 ) npy_cam = py - 140;
	else if( py_scr < 60 ) npy_cam = py - 60;
	else npy_cam = camPosY;

	// clip camera position
	if( npx_cam < 0 ) npx_cam = 0;
	else if( npx_cam > ( 4096 - 320 ) ) npx_cam = ( 4096 - 320 );
	if( npy_cam < 0 ) npy_cam = 0;
	else if( npy_cam > ( 512 - 224 ) ) npy_cam = ( 512 - 224 );

	// set new camera position
	setCameraPosition( npx_cam, npy_cam );
}

static void setCameraPosition( s16 x, s16 y )
{
	if( ( x != camPosX ) || ( y != camPosY ) )
	{
		camPosX = x;
		camPosY = y;

		// update maps (convert pixel to tile coordinate)
		updateMap( BG_A, bga, x >> 3, y >> 3 );
		// scrolling is slower on BGB, no vertical scroll (should be consisten with updateVDPScroll())
		updateMap( BG_B, bgb, x >> 6, 0 );

		scrollNeedUpdate = TRUE;
	}
}

static void updateMap( VDPPlane plane, TileMap* tileMap, s16 xt, s16 yt )
{
	// BGA = 0; BGB = 1
	s16 curPosX = mapTilePosX[ plane ];
	s16 curPosY = mapTilePosY[ plane ];

	s16 deltaX = xt - curPosX;
	s16 deltaY = yt - curPosY;

	// no update --> exit
	if( ( deltaX == 0 ) && ( deltaY == 0 ) ) return;

	SYS_disableInts();

	// many row/column updates ? --> better to do a full screen update
	if( ( abs( deltaX * 2 ) + abs( deltaY ) ) > 20 )
	{
		VDP_setTileMapEx( plane, tileMap, TILE_ATTR_FULL( PAL0, FALSE, FALSE, FALSE, bgBaseTileIndex[ plane ] ),
			xt & 0x003F, yt & 0x001F, xt, yt, 42, 30, DMA_QUEUE );
	}
	else
	{
		if( deltaX > 0 )
		{
			// need to update map column on right
			while( deltaX-- )
			{
				VDP_setTileMapColumnEx( plane, tileMap, TILE_ATTR_FULL( PAL0, FALSE, FALSE, FALSE, bgBaseTileIndex[ plane ] ),
					( curPosX + 42 ) & 0x3F, curPosX + 42, yt, 30, DMA_QUEUE );
				curPosX++;
			}
		}
		else if( deltaX < 0 )
		{
			// need to update map column on left
			while( deltaX++ )
			{
				curPosX--;
				VDP_setTileMapColumnEx( plane, tileMap, TILE_ATTR_FULL( PAL0, FALSE, FALSE, FALSE, bgBaseTileIndex[ plane ] ),
					curPosX & 0x3F, curPosX, yt, 30, DMA_QUEUE );
			}
		}


		if( deltaY > 0 )
		{
			// need to update map row on bottom
			while( deltaY-- )
			{
				VDP_setTileMapRowEx( plane, tileMap, TILE_ATTR_FULL( PAL0, FALSE, FALSE, FALSE, bgBaseTileIndex[ plane ] ),
					( curPosY + 30 ) & 0x1F, xt, curPosY + 30, 42, DMA_QUEUE );
				curPosY++;
			}
		}
		else if( deltaY < 0 )
		{
			// need to update map row on top
			while( deltaY++ )
			{
				curPosY--;
				VDP_setTileMapRowEx( plane, tileMap, TILE_ATTR_FULL( PAL0, FALSE, FALSE, FALSE, bgBaseTileIndex[ plane ] ),
					curPosY & 0x1F, xt, curPosY, 42, DMA_QUEUE );
			}
		}
	}

	SYS_enableInts();

	mapTilePosX[ plane ] = xt;
	mapTilePosY[ plane ] = yt;
}

static void updateVDPScroll()
{
	SYS_disableInts();
	VDP_setHorizontalScroll( BG_A, -camPosX );
	VDP_setHorizontalScroll( BG_B, ( -camPosX ) >> 3 );
	VDP_setVerticalScroll( BG_A, camPosY );
	VDP_setVerticalScroll( BG_B, 0 );
	SYS_enableInts();
}

static void frameChanged( Sprite* sprite )
{
	// get enemy index (stored in data field)
	u16 enemyIndex = sprite->data;
	// get VRAM tile index for this animation of this sprite
	u16 tileIndex = sprTileIndexes[ enemyIndex ][ sprite->animInd ][ sprite->frameInd ];
	// manually set tile index for the current frame (preloaded in VRAM)
	SPR_setVRAMTileIndex( sprite, tileIndex );
}

static void handleInput()
{
	u16 value = JOY_readJoypad( JOY_1 );

	// game is paused ? adjust physics settings
	if( paused )
	{

		if( value & BUTTON_RIGHT )
		{
			maxSpeed += FIX32( 0.2 );
			if( maxSpeed > MAX_SPEED_MAX ) maxSpeed = MAX_SPEED_MAX;
			updateBar( bars[ 0 ], MAX_SPEED_MIN, MAX_SPEED_MAX, maxSpeed );
		}
		else if( value & BUTTON_LEFT )
		{
			maxSpeed -= FIX32( 0.2 );
			if( maxSpeed < MAX_SPEED_MIN ) maxSpeed = MAX_SPEED_MIN;
			updateBar( bars[ 0 ], MAX_SPEED_MIN, MAX_SPEED_MAX, maxSpeed );
		}

		if( value & BUTTON_UP )
		{
			jumpSpeed += FIX32( 0.1 );
			if( jumpSpeed > JUMP_SPEED_MAX ) jumpSpeed = JUMP_SPEED_MAX;
			updateBar( bars[ 1 ], JUMP_SPEED_MIN, JUMP_SPEED_MAX, jumpSpeed );
		}
		else if( value & BUTTON_DOWN )
		{
			jumpSpeed -= FIX32( 0.1 );
			if( jumpSpeed < JUMP_SPEED_MIN ) jumpSpeed = JUMP_SPEED_MIN;
			updateBar( bars[ 1 ], JUMP_SPEED_MIN, JUMP_SPEED_MAX, jumpSpeed );
		}

		if( value & BUTTON_A )
		{
			gravity -= FIX32( 0.005 );
			if( gravity < GRAVITY_MIN ) gravity = GRAVITY_MIN;
			updateBar( bars[ 2 ], GRAVITY_MIN, GRAVITY_MAX, gravity );
		}
		else if( value & BUTTON_B )
		{
			gravity += FIX32( 0.005 );
			if( gravity > GRAVITY_MAX ) gravity = GRAVITY_MAX;
			updateBar( bars[ 2 ], GRAVITY_MIN, GRAVITY_MAX, gravity );
		}
	}
	// can affect game play
	else
	{
		if( value & BUTTON_UP ) yOrder = -1;
		else if( value & BUTTON_DOWN ) yOrder = +1;
		else yOrder = 0;

		if( value & BUTTON_LEFT ) xOrder = -1;
		else if( value & BUTTON_RIGHT ) xOrder = +1;
		else xOrder = 0;
	}
}

static void joyEvent( u16 joy, u16 changed, u16 state )
{
	if( joy != JOY_1 )
	{
		return;
	}

	// START button state changed --> pause / unpause
	if( changed & state & BUTTON_START )
	{
		paused = !paused;
		updateBarsVisitility();
	}

	// can't do more in paused state
	if( paused ) return;

	if( changed & state & ( BUTTON_A | BUTTON_B | BUTTON_C ) )
	{
		if( movY == 0 )
		{
			movY = -jumpSpeed;
			SND_startPlayPCM_XGM( SFX_JUMP, 1, SOUND_PCM_CH2 );
		}
	}
}
