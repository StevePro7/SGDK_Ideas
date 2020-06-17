#include "main.h"

#define ANIM_RUN	0
#define ANIM_JUMP	1

// General stuff
const char msg_start[ 22 ] = "Press START to Begin!";
const char msg_reset[ 22 ] = "Press START to Reset!";
unsigned char game_on = FALSE;

const int scrollspeed = 2;

Sprite* player;
const int player_x = 32;
fix16 player_y = FIX16( 112 );
fix16 player_vel_y = FIX16( 0 );

int player_height = 16;
const int floor_height = 128;
fix16 gravity = FIX16( 0.2 );
unsigned char jumping = FALSE;

Sprite* obstacle;
int obstacle_x = 320;
const int obstacle_y = 120;
int obstacle_vel_x = 0;

int score = 0;
char label_score[ 6 ] = "SCORE\0";
char str_score[ 3 ] = "0";
unsigned char score_added = FALSE;

void updateScoreDisplay()
{
	sprintf( str_score, "%d", score );
	VDP_clearText( 10, 2, 3 );
	VDP_drawText( str_score, 10, 2 );
}

void showText( const char s[] )
{
	VDP_drawText( s, 20 - strlen( s ) / 2, 10 );
}
void  clearText()
{
	VDP_clearText( 0, 10, 32 );
}

void startGame()
{
	VDP_drawText( label_score, 10, 1 );
	score = 0;
	updateScoreDisplay();
	obstacle_x = 320;

	if( !game_on )
	{
		game_on = TRUE;
		clearText();
	}
}
void endGame()
{
	if( game_on )
	{
		clearText();
		showText( msg_reset );
		game_on = FALSE;
	}
}

void myJoyHandler( u16 joy, u16 changed, u16 state )
{
	if( joy == JOY_1 )
	{
		// Start game if START is pressed
		if( state & BUTTON_START )
		{
			if( !game_on )
			{
				startGame();
			}
		}
		if( state & BUTTON_C )
		{
			if( !jumping )
			{
				jumping = TRUE;
				player_vel_y = FIX16( -4 );
				SPR_setAnim( player, ANIM_JUMP );
			}
		}
		if( changed & BUTTON_A )
		{

		}
	}
}

int main()
{
	u16 *light_data = NULL;
	u16 *runner_data = NULL;

#ifndef _CONSOLE
	light_data = light.palette->data;
	runner_data = runner.palette->data;
#endif

	JOY_init();
	JOY_setEventHandler( myJoyHandler );

	VDP_setPaletteColor( 0, RGB24_TO_VDPCOLOR( 0x6dc2ca ) );
	VDP_setPlanSize( 32, 32 );

	VDP_loadTileSet( floor.tileset, 1, DMA );
	VDP_loadTileSet( wall.tileset, 2, DMA );
	VDP_loadTileSet( light.tileset, 3, DMA );

	//VDP_setPalette( PAL1, light.palette->data );		// OLD
	VDP_setPalette( PAL1, light_data );

	VDP_fillTileMapRect( BG_B, TILE_ATTR_FULL( PAL1, 0, FALSE, FALSE, 1 ), 0, 16, 32, 1 );
	VDP_fillTileMapRect( BG_B, TILE_ATTR_FULL( PAL1, 0, FALSE, TRUE, 2 ), 0, 17, 32, 14 );

	VDP_fillTileMapRectInc( BG_B, TILE_ATTR_FULL( PAL1, 0, FALSE, FALSE, 3 ), 15, 13, 2, 3 );

	VDP_setScrollingMode( HSCROLL_PLANE, VSCROLL_PLANE );

	//VDP_setPalette( PAL2, runner.palette->data );		// OLD
	VDP_setPalette( PAL2, runner_data );

	SPR_init( 0, 0, 0 );

	//player = SPR_addSprite( &runner, player_x, player_y, TILE_ATTR( PAL2, 0, FALSE, FALSE ) );
	player = SPR_addSprite( &runner, player_x, fix16ToInt( player_y ), TILE_ATTR( PAL2, 0, FALSE, FALSE ) );

	SPR_setAnim( player, ANIM_RUN );

	obstacle = SPR_addSprite( &rock, obstacle_x, obstacle_y, TILE_ATTR( PAL2, 0, FALSE, FALSE ) );
	SPR_update();

	showText( msg_start );

	int offset = 0;
	obstacle_vel_x = -scrollspeed;
	while( 1 )
	{
		if( game_on )
		{
			VDP_setHorizontalScroll( BG_B, offset -= scrollspeed );
			if( offset <= -256 )
			{
				offset = 0;
			}

			// Move the obstacle
			obstacle_x += obstacle_vel_x;
			if( obstacle_x < -8 )
			{
				obstacle_x = 320;
			}
			SPR_setPosition( obstacle, obstacle_x, obstacle_y );

			// Apply velocity
			player_y = fix16Add( player_y, player_vel_y );
			if( jumping )
			{
				player_vel_y = fix16Add( player_vel_y, gravity );

				// Check if player is on floor
				if( fix16ToInt( player_y ) + player_height >= floor_height )
				{
					jumping = FALSE;
					player_vel_y = FIX16( 0 );
					player_y = intToFix16( floor_height - player_height );
					SPR_setAnim( player, ANIM_RUN );
					score_added = FALSE;
				}
			}
			SPR_setPosition( player, player_x, fix16ToInt( player_y ) );

			// Collision
			if( player_x < obstacle_x + 8 && player_x + 8 > obstacle_x )
			{
				if( !jumping )
				{
					endGame();
				}
				else
				{
					if( !score_added )
					{
						score++;
						updateScoreDisplay();
						score_added = TRUE;
					}
				}
			}

			SPR_update();
		}

		VDP_waitVSync();
	}

	return 0;
}