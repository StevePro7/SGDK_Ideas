#include "main.h"

#define ANIM_STAND      0
#define ANIM_WALK       1

#define SCREEN_WIDTH_TILES     40
#define SCREEEN_HEIGHT_TILES   28

#define SCENARIO_POS_X          0
#define SCENARIO_POS_Y          0

#define SCENARIO_WIDTH_TILES    SCREEN_WIDTH_TILES
#define SCENARIO_HEIGHT_TILES   SCREEEN_HEIGHT_TILES
//Total tiles de la pantalla = 40x28 = 1120 tiles
#define SCENARIO_NUM_TILES      SCENARIO_WIDTH_TILES * SCENARIO_HEIGHT_TILES

Sprite* spr_ryu;
Sprite* spr_sombra;
Sprite* spr_hadoken;

//Posición inicial en pantalla del sprite
s16 ryu_posx = 120;
s16 ryu_posy = 120;
s16 hadoken_posx = 150;
s16 hadoken_posy = 130;

static void handleInput();

int main()
{
	u16 *tilemap = NULL;
	u16 *data1 = NULL;
	u16 *data2 = NULL;
	u16 *data3 = NULL;

	u16 tilemap_buffer[ SCENARIO_NUM_TILES ];
	u16 *apain_tilemap = &tilemap_buffer[ 0 ];

	for( int j = 0; j < SCENARIO_NUM_TILES; j++ )
		tilemap_buffer[ j ] = 0;

#ifndef _CONSOLE
	tilemap = bg_prioridad.tilemap->tilemap;
	data1 = bg_B_real.palette->data;
	data2 = mi_sprite_ryu.palette->data;
	data3 = mi_sprite_hadoken.palette->data;
#endif
	u16 *shadowmap_tilemap = tilemap;
	u16 numtiles = SCENARIO_NUM_TILES;

	while( numtiles-- )
	{
		if( *shadowmap_tilemap )
		{
			*apain_tilemap |= TILE_ATTR_PRIORITY_MASK;
		}

		apain_tilemap++;
		shadowmap_tilemap++;
	}

	VDP_setTileMapDataRectEx( BG_A, &tilemap_buffer[ 0 ], 0, SCENARIO_POS_X, SCENARIO_POS_Y, SCENARIO_WIDTH_TILES, SCREEEN_HEIGHT_TILES, SCREEN_WIDTH_TILES, DMA );
	VDP_drawImage( BG_B, &bg_B_real, SCENARIO_POS_X, SCENARIO_POS_Y );
	
	SPR_init( 16, 256, 256 );

	VDP_setPalette( PAL0, data1 );
	VDP_setPalette( PAL1, data2 );
	VDP_setPalette( PAL3, data3 );

	spr_ryu = SPR_addSprite( &mi_sprite_ryu, ryu_posx, ryu_posy, TILE_ATTR( PAL1, FALSE, FALSE, FALSE ) );
	spr_sombra = SPR_addSprite( &mi_sprite_sombra, ryu_posx, ryu_posy+70, TILE_ATTR( PAL3, FALSE, FALSE, FALSE ) );
	spr_hadoken = SPR_addSprite( &mi_sprite_hadoken, hadoken_posx, hadoken_posy, TILE_ATTR( PAL3, TRUE, FALSE, FALSE ) );
	
	VDP_setHilightShadow( 1 );
	
	SPR_setHFlip( spr_ryu, TRUE );
	SPR_setHFlip( spr_hadoken, TRUE );
	SPR_update();
	while( 1 )
	{
		handleInput();
		SPR_update();
		VDP_waitVSync();
	}

	return 0;
}

//Recoge la entrada del mando y actualiza la posicion del sprite
static void handleInput()
{
	//variable donde se guarda la entrada del mando
	u16 value = JOY_readJoypad( JOY_1 );

	//si pulsamos izquierda...
	if( value & BUTTON_LEFT )
	{
		SPR_setPosition( spr_ryu, ryu_posx--, ryu_posy );
		SPR_setPosition( spr_sombra, ryu_posx--, ryu_posy + 70 );
		SPR_setAnim( spr_ryu, ANIM_WALK );
		SPR_setHFlip( spr_ryu, FALSE );
	}

	//si pulsamos derecha...
	if( value & BUTTON_RIGHT )
	{
		SPR_setPosition( spr_ryu, ryu_posx++, ryu_posy );
		SPR_setPosition( spr_sombra, ryu_posx++, ryu_posy + 70 );
		SPR_setAnim( spr_ryu, ANIM_WALK );
		SPR_setHFlip( spr_ryu, TRUE );
	}

	//si pulsamos arriba...
	if( value & BUTTON_UP )
	{
		SPR_setPosition( spr_ryu, ryu_posx, ryu_posy-- );
		SPR_setPosition( spr_sombra, ryu_posx, ryu_posy + 69 );
	}

	//si pulsamos abajo...
	if( value & BUTTON_DOWN )
	{
		SPR_setPosition( spr_ryu, ryu_posx, ryu_posy++ );
		SPR_setPosition( spr_sombra, ryu_posx, ryu_posy + 69 );
	}

	//si pulsamos A
	if( value & BUTTON_A )
		SPR_setPosition( spr_hadoken, hadoken_posx++, hadoken_posy );
	//si pulsamos A
	if( value & BUTTON_B )
		SPR_setPosition( spr_hadoken, hadoken_posx--, hadoken_posy );

	//si no pulsamos
	if( ( !( value & BUTTON_RIGHT ) ) && ( !( value & BUTTON_LEFT ) ) )
	{
		SPR_setAnim( spr_ryu, ANIM_STAND );
	}

}