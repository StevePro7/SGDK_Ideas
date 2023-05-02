#include "main.h"

#define CIRCULO14   0
#define CIRCULO15   1

static void handleInput();
void myJoyHandler( u16 joy, u16 changed, u16 state );
void pinta_ayuda_en_pantalla();

Sprite* mi_sonic;
Sprite* mi_objetivo;

s16 mi_sonic_posx = 64;
s16 mi_sonic_posy = 155;

s16 mi_objetivo_posx = 120;
s16 mi_objetivo_posy = 96;

int sh_activo = 0;              //S&H activo (1) o no (0)
int sh_paleta = 2;              //cambia entre paleta2 (2) o paleta3 (3)
int sh_priori = 0;              //prioridad para el sprite del circulo (1) o no tenerla (0)
int sh_color = 14;             //cambia entre el sprite del circulo pintado con el color 14 (14) o el color 15 (15)
int sh_fondo_priori = 0;        //prioridad para el fondo (1) o no tenerla (0)

u16 ind;
u16 numTile;

int main()
{
	u16 *data1 = NULL;
	u16 *data2 = NULL;
	u16 *data3 = NULL;
	numTile = 0;

#ifndef _CONSOLE
	data1 = fondo1.palette->data;
	numTile = fondo1.tileset->numTile;
	data2 = sonic_sprite.palette->data;
	data3 = circulo_sprite.palette->data;
#endif

	VDP_setScreenWidth320();

	SPR_init( 0, 0, 0 );

	VDP_setPalette( PAL0, data1 );

	ind = TILE_USERINDEX;
	VDP_drawImageEx( BG_A, &fondo1, TILE_ATTR_FULL( PAL0, FALSE, FALSE, FALSE, ind ), 0, 0, FALSE, TRUE );
	ind += numTile;

	VDP_setPalette( PAL1, data2 );
	VDP_setPalette( PAL2, data3 );
	VDP_setPalette( PAL3, data3 );

	mi_objetivo = SPR_addSprite( &circulo_sprite, mi_sonic_posx, mi_objetivo_posy, TILE_ATTR( PAL2, FALSE, FALSE, FALSE ) );
	SPR_setAnim( mi_objetivo, CIRCULO14 );

	mi_sonic = SPR_addSprite( &sonic_sprite, mi_sonic_posx, mi_sonic_posy, TILE_ATTR( PAL1, TRUE, FALSE, FALSE ) );

	JOY_init();
	JOY_setEventHandler( &myJoyHandler );

	VDP_drawText( "S&H: OFF                                ", 0, 0 );
	VDP_drawText( "PALETA CIRCULO: PAL2                    ", 0, 1 );
	VDP_drawText( "Prioridad: NO                           ", 0, 2 );
	VDP_drawText( "Color circulo: 14                       ", 0, 3 );
	VDP_drawText( "Fondo PRIORIDAD: OFF                    ", 0, 4 );
	VDP_drawText( "A:SH on/off, B:Paleta, C:Prioridad Circ.", 0, 26 );
	VDP_drawText( "X: color14/15, Y: Prioridad Fondo       ", 0, 27 );

	while( 1 )
	{
		handleInput();
		SPR_update();
		VDP_waitVSync();
	}

	return 0;
}

// MANDO DETECCION SINCRONA
static void handleInput()
{
	//variable donde se guarda la entrada del mando
	u16 value = JOY_readJoypad( JOY_1 );
	//si pulsamos izquierda...
	if( value & BUTTON_LEFT )
		SPR_setPosition( mi_objetivo, mi_objetivo_posx--, mi_objetivo_posy );
	//si pulsamos derecha...
	if( value & BUTTON_RIGHT )
		SPR_setPosition( mi_objetivo, mi_objetivo_posx++, mi_objetivo_posy );
	//si pulsamos arriba...
	if( value & BUTTON_UP )
		SPR_setPosition( mi_objetivo, mi_objetivo_posx, mi_objetivo_posy-- );
	//si pulsamos abajo...
	if( value & BUTTON_DOWN )
		SPR_setPosition( mi_objetivo, mi_objetivo_posx, mi_objetivo_posy++ );
}

void myJoyHandler( u16 joy, u16 changed, u16 state )
{
	if( joy == JOY_1 )
	{
		if( state & BUTTON_A )
		{
			if( sh_activo )   sh_activo = 0;
			else            sh_activo = 1;

			VDP_setHilightShadow( sh_activo );
		}

		if( state & BUTTON_B )
		{
			if( sh_paleta == 3 )
			{
				sh_paleta = 2;
				SPR_setPalette( mi_objetivo, PAL2 );
			}
			else
			{
				sh_paleta = 3;
				SPR_setPalette( mi_objetivo, PAL3 );
			}
		}

		if( state & BUTTON_C )
		{
			if( sh_priori )
			{
				sh_priori = 0;
				SPR_setPriorityAttribut( mi_objetivo, FALSE );
			}
			else
			{
				sh_priori = 1;
				SPR_setPriorityAttribut( mi_objetivo, TRUE );
			}
		}

		if( state & BUTTON_X )
		{
			if( sh_color == 14 )
			{
				sh_color = 15;
				SPR_setAnim( mi_objetivo, CIRCULO15 );
			}
			else
			{
				sh_color = 14;
				SPR_setAnim( mi_objetivo, CIRCULO14 );
			}
		}

		if( state & BUTTON_Y )
		{
			if( sh_fondo_priori )
			{
				sh_fondo_priori = 0;
				ind = TILE_USERINDEX;
				VDP_drawImageEx( BG_A, &fondo1, TILE_ATTR_FULL( PAL0, FALSE, FALSE, FALSE, ind ), 0, 0, FALSE, TRUE );
				ind += numTile;
			}
			else
			{
				sh_fondo_priori = 1;
				ind = TILE_USERINDEX;
				VDP_drawImageEx( BG_A, &fondo1, TILE_ATTR_FULL( PAL0, TRUE, FALSE, FALSE, ind ), 0, 0, FALSE, TRUE );
				ind += numTile;
			}
		}
	}

	pinta_ayuda_en_pantalla();
}

void pinta_ayuda_en_pantalla()
{

	if( sh_activo )       VDP_drawText( "S&H: OFF                                ", 0, 0 );
	else                VDP_drawText( "S&H: ON                                 ", 0, 0 );

	if( sh_paleta == 3 )    VDP_drawText( "PALETA CIRCULO: PAL2                    ", 0, 1 );
	else                VDP_drawText( "PALETA CIRCULO: PAL3                    ", 0, 1 );

	if( sh_priori )       VDP_drawText( "Prioridad: NO                           ", 0, 2 );
	else                VDP_drawText( "Prioridad: SI                           ", 0, 2 );

	if( sh_color == 14 )    VDP_drawText( "Color circulo: 15                       ", 0, 3 );
	else                VDP_drawText( "Color circulo: 14                       ", 0, 3 );

	if( sh_fondo_priori ) VDP_drawText( "Fondo PRIORIDAD: OFF                    ", 0, 4 );
	else                VDP_drawText( "Fondo PRIORIDAD:  ON                    ", 0, 4 );

	VDP_drawText( "A:SH on/off, B:Paleta, C:Prioridad Circ.", 0, 26 );
	VDP_drawText( "X: color14/15, Y: Prioridad Fondo       ", 0, 27 );
}
