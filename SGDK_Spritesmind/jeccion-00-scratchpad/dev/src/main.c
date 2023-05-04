#include "main.h"

#define ANIM_STAND   0   //animaciones de Sonic
#define ANIM_RUN     3

#define ANIM_NAVE_IDLE 0 //animaciones Nave
#define ANIM_NAVE_MOV  1


#define LIMITE_IZQ  10   //limites pantalla para el sprite
#define LIMITE_DCH  280
#define LIMITE_UP   10
#define LIMITE_DOWN 180

static void handleInput();
static void cargaESTADO();
static void muestraMENSAJES();
static void actualizaCamara();

Sprite *Sonic, *Nave, *Enemigos[ 6 ];

//Para ir pasando por los distintos ejemplos
int estado = 1; //estado inicial
int cerrojo = 0;

//Cuenta de tiles en VRAM
u16 ind;

//Desplazamiento respecto al punto (0,0) de los planos (ejemplo 6)
s16 offsetA = 0;
//Para (ir incrementando) el movimiento de los planos (ejemplo 6)
s16 aceleracionA = 4;

//movimiento de Sonic (ejemplo 6)
int posx = 48;
int posy = 158;

//movimiento de las Naves (ejemplo 7)
//re-usaremos 'posx' y 'posy' para la posicion de la nave del player
int enemigo_posx[ 6 ] = { 0,0,0,0,0,0 };
int enemigo_posy[ 6 ] = { 0,0,0,0,0,0 };

//vectores para los ejemplos de scroll (ejemplos 1 al 7)
s16 vector01[ 6 ] = { 1,2,3,4,5,6 };
s16 vector02[ 6 ] = { 0,10,20,30,40,50 };
s16 vector03[ 10 ] = { 0,0,0,0,0,0,0,0,0,0 };
s16 vector04[ 28 ] = { 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0 };
s16 vector05[ 28 ] = { 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0 };
s16 vector06[ 28 ] = { 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0 };

s16 vector07[ 20 ] = { 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 };

s16 v_aceleracion01[ 6 ] = { 1,2,3,3,2,1 };
s16 v_aceleracion02[ 10 ] = { 1,2,3,4,5,6,7,8,9,10 };
s16 v_aceleracion03[ 28 ] = { 9,9,8,8,7, 6,6,6,5,5, 4,3,2,1,2, 3,4,5,5,6 };
s16 v_aceleracion04[ 20 ] = { 10,9,8,5,6, 5,4,3,2,1, 1,2,3,4,5, 6,7,8,9,10 };

fix16 vector_aux[ 28 ] = { 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, };
fix16 aceleracion04 = FIX16( 0.06 );

u16 *data0;
u16 *data1;
u16 *data2;
u16 *data3;
u16 *data4;
u16 *data5;
u16 *data6;
u16 numTile1;
u16 numTile2;
u16 numTile3;
u16 numTile4;
u16 numTile5;

int main()
{
	data0 = NULL;
	data1 = NULL;
	data2 = NULL;
	data3 = NULL;
	data4 = NULL;
	data5 = NULL;
	data6 = NULL;
	numTile1 = 0;
	numTile2 = 0;
	numTile3 = 0;
	numTile4 = 0;
	numTile5 = 0;
#ifndef _CONSOLE
	data0 = bgb_image.palette->data;
	data1 = bga_image.palette->data;
	data2 = sonic_sprite.palette->data;
	data3 = bgd_image.palette->data;
	data4 = bgc_image.palette->data;
	data5 = nave_sprite.palette->data;
	data6 = bgv_image.palette->data;
	numTile1 = bgb_image.tileset->numTile;
	numTile2 = bga_image.tileset->numTile;
	numTile3 = bgd_image.tileset->numTile;
	numTile4 = bgc_image.tileset->numTile;
	numTile5 = bgv_image.tileset->numTile;
#endif

	VDP_setScreenWidth320();

	VDP_setPalette( PAL0, data0 );
	VDP_setPalette( PAL1, data1 );
	VDP_setPalette( PAL2, data2 );

	SPR_init( 0, 0, 0 );

	ind = TILE_USERINDEX;
	VDP_drawImageEx( BG_B, &bgb_image, TILE_ATTR_FULL( PAL0, FALSE, FALSE, FALSE, ind ), 0, 0, FALSE, TRUE );
	ind += numTile1;
	VDP_drawImageEx( BG_B, &bgb_image, TILE_ATTR_FULL( PAL0, FALSE, FALSE, FALSE, ind ), 0, 0, FALSE, TRUE );
	ind += numTile2;

	VDP_setScrollingMode( HSCROLL_TILE, VSCROLL_PLANE );
	

	while( TRUE )
	{
		//En cada ejemplo llamamos a cargaESTADO() para inicializar cada ejemplo correctamente
		cargaESTADO();

		//bucle secundario, se abre (cerrojo=0) cada vez que cambiamos de ejemplo=estado
		//al iniciarse un ejemplo, se cierra (cerrojo=1)
		while( cerrojo )
		{
			//Controles (sincronos)
			handleInput();

			//muestra Mensajes al usuario
			muestraMENSAJES();

			//actualiza Camara
			actualizaCamara();

			//actualiza VDP
			SPR_update();

			//Espera al barrido vertical TV
			VDP_waitVSync();
		}

		estado++;
	}

	return 0;
}


static void cargaESTADO()
{
	offsetA = 0;

	for( int i = 0; i < 6; i++ ) vector01[ i ] = i + 1;      //del 1 a 6
	for( int i = 0; i < 6; i++ ) vector02[ i ] = i * 10;     //del 0 al 50
	for( int i = 0; i < 6; i++ ) vector03[ i ] = 0;        //0
	for( int i = 0; i < 28; i++ ) vector04[ i ] = 0;        //0
	for( int i = 0; i < 28; i++ ) vector05[ i ] = FIX16( 0 ); //0

	if( estado == 6 ) //a�ade un sprite de Sonic
	{
		Sonic = SPR_addSprite( &sonic_sprite, posx, posy, TILE_ATTR( PAL2, TRUE, FALSE, FALSE ) );
	}

	if( estado == 7 )
	{
		VDP_resetScreen();
		VDP_init();

		//320x224px
		VDP_setScreenWidth320();

		//inicializa motor de sprites
		SPR_init( 0, 0, 0 );

		VDP_setPalette( PAL0, data3 );
		VDP_setPalette( PAL0, data4 );
		VDP_setPalette( PAL0, data5 );

		SPR_init( 0, 0, 0 );

		ind = TILE_USERINDEX;
		VDP_drawImageEx( BG_B, &bgd_image, TILE_ATTR_FULL( PAL0, FALSE, FALSE, FALSE, ind ), 0, 0, FALSE, TRUE );
		ind += numTile2;
		VDP_drawImageEx( BG_A, &bgc_image, TILE_ATTR_FULL( PAL0, FALSE, FALSE, FALSE, ind ), 0, 0, FALSE, TRUE );
		ind += numTile3;

		VDP_setScrollingMode( HSCROLL_TILE, VSCROLL_PLANE );
	
		posx = 50; posy = 120;
		for( int i = 0; i < 6; i++ ) {
			enemigo_posx[ i ] = 100 + i * 50; enemigo_posy[ i ] = 30 + i * 20;
		}

		//crea los sprites
		Nave = SPR_addSprite( &nave_sprite, posx, posy, TILE_ATTR( PAL0, TRUE, FALSE, FALSE ) );

		for( int i = 0; i < 6; i++ )
			Enemigos[ i ] = SPR_addSprite( &enemigo_sprite, enemigo_posx[ i ], enemigo_posy[ i ], TILE_ATTR( PAL0, TRUE, FALSE, FALSE ) );
	}

	if( estado == 8 )
	{
		//resetea el VDP: fondos, vram, etc
		VDP_resetScreen();
		VDP_init();

		//320x224px
		VDP_setScreenWidth320();

		//inicializa motor de sprites
		SPR_init( 0, 0, 0 );

		//paletas
		VDP_setPalette( PAL0, data6 );

		//backgrounds
		ind = TILE_USERINDEX;
		VDP_drawImageEx( BG_A, &bgv_image, TILE_ATTR_FULL( PAL0, FALSE, FALSE, FALSE, ind ), 0, 0, FALSE, TRUE );
		ind += numTile5;

		//Configura el scroll (por TILES vertical, el horizontal no lo uso, lo dejo por defecto)
		VDP_setScrollingMode( HSCROLL_PLANE, VSCROLL_2TILE );
	}



	//finalmente activamos el cerrojo para no salirse del bucle secundario
	cerrojo = 1;
}


static void actualizaCamara()
{

	if( estado == 1 ) //planoA:Est�tico, planoB:Scroll 6 primeras filas
	{
		VDP_setHorizontalScrollTile( BG_B, 0, vector01, 6, CPU );
		for( int i = 0; i < 6; i++ ) vector01[ i ] = vector01[ i ] + 1;
	}

	if( estado == 2 ) //Idem pero con distinto vector inicial
	{
		VDP_setHorizontalScrollTile( BG_B, 0, vector02, 6, CPU );
		for( int i = 0; i < 6; i++ ) vector02[ i ] = vector02[ i ] + 1;
	}

	if( estado == 3 ) //Idem pero con distinta velocidad por fila
	{
		VDP_setHorizontalScrollTile( BG_B, 0, vector02, 6, CPU );
		for( int i = 0; i < 6; i++ ) vector02[ i ] = vector02[ i ] + i;
	}

	if( estado == 4 ) //Idem usando vector aceleracion ( v_aceleracion01 )
	{
		VDP_setHorizontalScrollTile( BG_B, 0, vector02, 6, CPU );
		for( int i = 0; i < 6; i++ ) vector02[ i ] += v_aceleracion01[ i ];
	}

	if( estado == 5 ) //Scroll por tiles en 2 zonas diferentes de la TV
	{
		//nubes
		VDP_setHorizontalScrollTile( BG_B, 0, vector01, 6, CPU );
		for( int i = 0; i < 6; i++ )  vector01[ i ] += 2;
		//mar
		VDP_setHorizontalScrollTile( BG_B, 18, vector03, 10, CPU );
		for( int i = 0; i < 10; i++ ) vector03[ i ] -= v_aceleracion02[ i ];
	}

	if( estado == 6 ) //scroll por tiles en 2 zonas en plano B y 1 zona en plano A
	{
		//nubes
		VDP_setHorizontalScrollTile( BG_B, 0, vector01, 6, CPU );
		for( int i = 0; i < 6; i++ )  vector01[ i ] -= 2;
		//mar
		VDP_setHorizontalScrollTile( BG_B, 18, vector03, 10, CPU );
		for( int i = 0; i < 10; i++ ) vector03[ i ] -= v_aceleracion02[ i ];
		//plano A
		VDP_setHorizontalScrollTile( BG_A, 0, vector04, 28, CPU );
		for( int i = 0; i < 28; i++ ) vector04[ i ] = offsetA;
	}

	if( estado == 7 ) //scroll por tiles todo plano B y muchas zonas en plano A
	{
		//plano B: scroll hasta que el planeta llega a mitad de pantalla aprox
		if( vector05[ 0 ] >= ( -200 ) )
		{
			VDP_setHorizontalScrollTile( BG_B, 0, vector05, 28, CPU );
			for( int i = 0; i < 28; i++ ) {
				vector_aux[ i ] = fix16Sub( vector_aux[ i ], aceleracion04 );
				vector05[ i ] = fix16ToInt( vector_aux[ i ] );
			}
		}

		//plano A
		VDP_setHorizontalScrollTile( BG_A, 0, vector06, 28, CPU );
		for( int i = 0; i < 28; i++ ) vector06[ i ] -= v_aceleracion03[ i ];

		//metemos aqui el mov de los enemigos (deberia ir en otro lado, pero por simplificar)
		for( int i = 0; i < 6; i++ ) {
			SPR_setPosition( Enemigos[ i ], enemigo_posx[ i ] -= 3, enemigo_posy[ i ] );
			//si se sale por la izq, lo ponemos a la derecha en otra posicion
			if( enemigo_posx[ i ] < -50 ) { enemigo_posx[ i ] = 350; enemigo_posy[ i ] = ( ( ( random() % 200 ) - 1 ) + 1 ); } //200 es el max de la coordenada y
		}
	}

	if( estado == 8 ) //scroll por tiles vertical
	{
		//plano A
		VDP_setVerticalScrollTile( BG_A, 0, vector07, 20, CPU );
		for( int i = 0; i < 20; i++ ) vector07[ i ] -= v_aceleracion04[ i ];
	}

}

static void handleInput()
{
	u16 value = JOY_readJoypad( JOY_1 );

	if( estado == 1 ) //abre el cerrojo para salir del bucle secundario
	{
		if( value & BUTTON_A ) cerrojo = 0;
	}

	if( estado == 2 )
	{
		if( value & BUTTON_B ) cerrojo = 0;
	}

	if( estado == 3 )
	{
		if( value & BUTTON_C ) cerrojo = 0;
	}

	if( estado == 4 )
	{

		if( value & BUTTON_A ) cerrojo = 0;
	}

	if( estado == 5 )
	{
		if( value & BUTTON_B ) cerrojo = 0;
	}

	if( estado == 6 ) //PAD: Mueve scroll Y sprite
	{
		if( value & BUTTON_LEFT )
		{   //plano
			offsetA += aceleracionA;
			//sprite
			SPR_setAnim( Sonic, ANIM_RUN ); SPR_setHFlip( Sonic, TRUE );
		}
		if( value & BUTTON_RIGHT )
		{
			offsetA -= aceleracionA;
			SPR_setAnim( Sonic, ANIM_RUN ); SPR_setHFlip( Sonic, FALSE );
		}

		//si no pulsamos, Sonic animacion idle
		if( ( !( value & BUTTON_RIGHT ) ) && ( !( value & BUTTON_LEFT ) ) ) SPR_setAnim( Sonic, ANIM_STAND );

		//abre el cerrojo para salir del bucle secundario
		if( value & BUTTON_C ) cerrojo = 0;
	}

	if( estado == 7 ) //pad: mueve nave, con limites | tecla START: reiniciar
	{
		if( value & BUTTON_LEFT )
		{
			//sprite (limites para que no se salga de la pantalla)
			posx -= 2; if( posx <= LIMITE_IZQ ) posx = LIMITE_IZQ;
			SPR_setAnim( Nave, ANIM_NAVE_MOV );
		}
		if( value & BUTTON_RIGHT )
		{
			posx += 2; if( posx >= LIMITE_DCH ) posx = LIMITE_DCH;
			SPR_setAnim( Nave, ANIM_NAVE_MOV );
		}

		if( value & BUTTON_UP )
		{
			posy -= 2; if( posy <= LIMITE_UP ) posy = LIMITE_UP;
			SPR_setAnim( Nave, ANIM_NAVE_MOV );
		}
		if( value & BUTTON_DOWN )
		{
			posy += 2; if( posy >= LIMITE_DOWN ) posy = LIMITE_DOWN;
			SPR_setAnim( Nave, ANIM_NAVE_MOV );
		}

		//si no pulsamos, animacion idle
		if( ( !( value & BUTTON_RIGHT ) ) && ( !( value & BUTTON_LEFT ) ) &&
			( !( value & BUTTON_UP ) ) && ( !( value & BUTTON_DOWN ) ) )
			SPR_setAnim( Nave, ANIM_NAVE_IDLE );

		//abre el cerrojo para salir del bucle secundario
		if( value & BUTTON_A ) cerrojo = 0;

		//actualiza posicion del sprite
		SPR_setPosition( Nave, posx, posy );
	}

	if( estado == 8 ) //scroll tiles vertical | tecla START: reiniciar
	{
		//reinicia la ROM
		if( value & BUTTON_START ) SYS_hardReset();  //hay que a�adir #include "sys.h" en la cabecera
	}
}
static void muestraMENSAJES()
{
	if( estado == 1 ) //estado inicial al empezar el programa
	{
		VDP_drawText( "Ejemplo 01", 4, 12 );
		VDP_drawText( "Pulsa -A- para continuar", 4, 13 );
	}

	if( estado == 2 )
	{
		VDP_drawText( "Ejemplo 02", 4, 12 );
		VDP_drawText( "Pulsa -B- para continuar", 4, 13 );
	}

	if( estado == 3 )
	{
		VDP_drawText( "Ejemplo 03", 4, 12 );
		VDP_drawText( "Pulsa -C- para continuar", 4, 13 );
	}

	if( estado == 4 )
	{
		VDP_drawText( "Ejemplo 04", 4, 12 );
		VDP_drawText( "Pulsa -A- para continuar", 4, 13 );
	}

	if( estado == 5 )
	{
		VDP_drawText( "Ejemplo 05", 4, 12 );
		VDP_drawText( "Pulsa -B- para continuar", 4, 13 );
	}

	if( estado == 6 )
	{
		VDP_drawText( "Ejemplo 06", 4, 12 );
		VDP_drawText( "Pulsa -C- para continuar", 4, 13 );
	}

	if( estado == 7 )
	{
		VDP_drawTextBG( BG_B, "Ejemplo 07", 14, 24 );
		VDP_drawTextBG( BG_B, "Pulsa -A- para continuar", 14, 25 );
	}

	if( estado == 8 )
	{
		VDP_drawTextBG( BG_B, "Ejemplo 08", 7, 24 );
		VDP_drawTextBG( BG_B, "Pulsa -START- para REINICIAR", 7, 25 );
	}

}