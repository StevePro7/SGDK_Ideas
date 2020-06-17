#include "main.h"

#define MAX_ENEMIES			6
#define MAX_BULLETS			6
#define MAX_PLAYER_BULLETS	3
#define LEFT_EDGE			0
#define RIGHT_EDGE			320
#define BOTTOM_EDGE			224
#define ANIM_STRAIGHT		0
#define ANIM_MOVE			1
#define SHOT_INTERVAL		120
#define SFX_LASTER			64
#define SFX_EXPLOSION		65

int i = 0;
int thex = 0;
int they = 0;
int val = 1;

typedef struct
{
	int x;
	int y;
	int w;
	int h;
	int velx;
	int vely;
	int health;
	Sprite *sprite;
	char name[ 6 ];
} Entity;

Entity player = { 0, 0, 16, 16, 0, 0, 1, 0, "PLAYER" };
Entity enemies[ MAX_ENEMIES ];
Entity bullets[ MAX_BULLETS ];

u16 enemiesLeft = 0;
u16 bulletsOnScreen = 0;
u16 shotTicker = 0;
u16 shotsByPlayer = 0;
int score;
char hud_string[ 40 ] = "";

void killEntity( Entity *e )
{
	e->health = 0;
	SPR_setVisibility( e->sprite, HIDDEN );
}
void reviveEntity( Entity *e )
{
	e->health = 1;
	SPR_setVisibility( e->sprite, VISIBLE );
}
void updateScoreDisplay()
{
	sprintf( hud_string, "SCORE: %d - LEFT: %d", score, enemiesLeft );
	VDP_clearText( 0, 0, 40 );
	VDP_drawText( hud_string, 0, 0 );
}

void shootBullet( Entity shooter )
{
	unsigned char fromPlayer = shooter.y > 100;
	if( fromPlayer )
	{
		if( shotsByPlayer >= MAX_PLAYER_BULLETS )
		{
			return;
		}
	}

	if( bulletsOnScreen < MAX_BULLETS )
	{
		Entity *b;
		u16 i = 0;
		for( i = 0; i < MAX_BULLETS; i++ )
		{
			b = &bullets[ i ];
			if( 0 == b->health )
			{
				b->x = shooter.x + 4;
				b->y = shooter.y;

				reviveEntity( b );
				if( fromPlayer )
				{
					b->vely = -3;
					shotsByPlayer++;
				}
				else
				{
					b->vely = 2;
				}

				SPR_setPosition( b->sprite, b->x, b->y );
				bulletsOnScreen++;

				XGM_startPlayPCM( SFX_LASTER, 1, SOUND_PCM_CH2 );
				break;
			}
		}
	}
}

void positionEnemies()
{
	u8 i = 0;
	shotTicker++;
	for( i = 0; i < MAX_ENEMIES; i++ )
	{
		Entity *e = &enemies[ i ];
		if( 0 == e->health )
		{
			continue;
		}

		e->x += e->velx;
		if( ( e->x + e->w ) > RIGHT_EDGE )
		{
			e->velx = -1;
		}
		else if( e->x < LEFT_EDGE )
		{
			e->velx = 1;
		}

		SPR_setPosition( e->sprite, e->x, e->y );

		// Shooting
		if( shotTicker >= SHOT_INTERVAL )
		{
			if( ( random() % ( 10 - 1 + 1 ) + 1 ) > 4 )
			{
				shootBullet( *e );
				shotTicker = 0;
			}
		}
	}
}

void positionPlayer()
{
	// Add the player's velocity to its position
	player.x += player.velx;

	// Keep the player within the bound of the screen
	if( player.x < LEFT_EDGE )
	{
		player.x = LEFT_EDGE;
	}
	if( player.x + player.w > RIGHT_EDGE )
	{
		player.x = RIGHT_EDGE - player.w;
	}

	// Let the sprite engine position the sprite
	SPR_setPosition( player.sprite, player.x, player.y );
}

void positionBullets()
{
	u16 i = 0;
	Entity *b;
	for( i = 0; i < MAX_BULLETS; i++ )
	{
		b = &bullets[ i ];
		if( 1 == b->health )
		{
			b->y += b->vely;

			if( b->y + b->h < 0 )
			{
				killEntity( b );
				bulletsOnScreen--;
				shotsByPlayer--;
			}
			else if( b->y > BOTTOM_EDGE )
			{
				killEntity( b );
				bulletsOnScreen--;
			}
			else
			{
				SPR_setPosition( b->sprite, b->x, b->y );
			}
		}
	}
}

int collideEntities( Entity *a, Entity *b )
{
	return	a->x < b->x + b->w &&
		a->x + a->w > b->x &&
		a->y < b->y + b->h &&
		a->y + a->h > b->y;
}
void handleCollisions()
{
	Entity *b;
	Entity *e;
	int i = 0;
	int j = 0;

	for( i = 0; i < MAX_BULLETS; i++ )
	{
		b = &bullets[ i ];
		if( 1 == b->health )
		{
			if( b->vely < 0 )
			{
				for( j = 0; j < MAX_ENEMIES; j++ )
				{
					e = &enemies[ j ];
					if( 1 == e->health )
					{
						if( collideEntities( b, e ) )
						{
							killEntity( b );
							killEntity( e );

							enemiesLeft--;
							bulletsOnScreen--;
							shotsByPlayer--;

							score += 10;
							updateScoreDisplay();

							XGM_startPlayPCM( SFX_EXPLOSION, 2, SOUND_PCM_CH2 );
							break;
						}
					}
				}
			}
			else
			{
				if( collideEntities( b, &player ) )
				{
					killEntity( &player );
					XGM_startPlayPCM( SFX_EXPLOSION, 2, SOUND_PCM_CH2 );
				}
			}

		}
	}
}

void myJoyHandler( u16 joy, u16 changed, u16 state )
{
	u8 multiplier = 1;
	if( joy != JOY_1 )
	{
		return;
	}

	if( state & BUTTON_A )
	{
		multiplier = 2;
	}
	if( state & BUTTON_B & changed )
	{
		if( 1 == player.health )
		{
			shootBullet( player );
		}
	}
	if( state & BUTTON_RIGHT )
	{
		player.velx = 2 * multiplier;
		SPR_setAnim( player.sprite, ANIM_MOVE );
		SPR_setHFlip( player.sprite, TRUE );
	}
	else if( state  & BUTTON_LEFT )
	{
		player.velx = -2 * multiplier;
		SPR_setAnim( player.sprite, ANIM_MOVE );
		SPR_setHFlip( player.sprite, FALSE );
	}
	else
	{
		if( ( changed & BUTTON_RIGHT ) | ( changed & BUTTON_LEFT ) )
		{
			player.velx = 0;
			SPR_setAnim( player.sprite, ANIM_STRAIGHT );
		}
	}
}

int main()
{
	int offset = 0;
	u16 *data = NULL;

	JOY_init();
	JOY_setEventHandler( myJoyHandler );

	SYS_disableInts();

	VDP_loadTileSet( background.tileset, 1, DMA );
#ifndef _CONSOLE
	data = background.palette->data;
#endif
	VDP_setPalette( PAL1, data );
	VDP_setPalette( PAL2, data );
	VDP_setPaletteColor( 34, RGB24_TO_VDPCOLOR( 0x0078f8 ) );

	for( i = 0; i < 1280; i++ )
	{
		thex = i % 40;
		they = i / 40;
		val = ( random() % ( 10 - 1 + 1 ) ) + 1;
		if( val > 3 )
		{
			val = 1;
		}

		VDP_setTileMapXY( BG_B, TILE_ATTR_FULL( PAL1, 0, 0, 0, val ), thex, they );
	}

	VDP_setScrollingMode( HSCROLL_PLANE, VSCROLL_PLANE );
	SYS_enableInts();

	SPR_init( 0, 0, 0 );
	// Add the player.
	player.x = 152;
	player.y = 192;
	player.health = 1;
	player.sprite = SPR_addSprite( &ship, player.x, player.y, TILE_ATTR( PAL1, 0, FALSE, FALSE ) );

	// Create all enemy sprites
	Entity *e = enemies;
	for( i = 0; i < MAX_ENEMIES; i++ )
	{
		e->x = i * 32;
		e->y = 32;
		e->w = 16;
		e->h = 16;
		e->velx = 1;
		e->health = 1;
		e->sprite = SPR_addSprite( &ship, e->x, e->y, TILE_ATTR( PAL2, 0, TRUE, FALSE ) );
		sprintf( e->name, "En%d", i );
		enemiesLeft++;
		e++;
	}

	// Create all bullet sprites
	Entity *b = bullets;
	for( i = 0; i < MAX_BULLETS; i++ )
	{
		b->x = 0;
		b->y = -10;
		b->w = 8;
		b->h = 8;
		b->sprite = SPR_addSprite( &bullet, bullets[ 0 ].x, bullets[ 0 ].y, TILE_ATTR( PAL1, 0, FALSE, FALSE ) );
		sprintf( b->name, "Bu%d", i );
		b++;
	}

	updateScoreDisplay();

	XGM_setPCM( SFX_LASTER, sfx_laser, sizeof( sfx_laser ) );
	XGM_setPCM( SFX_EXPLOSION, sfx_explosion, sizeof( sfx_explosion ) );
	SPR_update();
	while( 1 )
	{
		SYS_disableInts();
		VDP_setVerticalScroll( BG_B, offset -= 2 );
		if( offset <= -256 )
		{
			offset = 0;
		}
		SYS_enableInts();

		positionPlayer();
		positionEnemies();
		positionBullets();
		handleCollisions();

		SPR_update();
		VDP_waitVSync();
	}

	return 0;
}