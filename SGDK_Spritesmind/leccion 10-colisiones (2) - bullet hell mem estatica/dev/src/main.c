#include "main.h"

//Constantes

#define NAVE_IDLE                0  //sprites de la nave
#define NAVE_UP                  1
#define NAVE_DOWN                2
#define VELOCIDAD_PLAYER         2  //velocidad desplazamiento nave

#define BLOQUEO_DISPARO          10 //Regula disparos x seg: num ciclos xa desbloquear sig disparo,
#define BLOQUEO_DISPARO_BOSS     5  //valor mas bajo = balas salen con mas frecuencia.

#define MAX_BALAS_PLAYER        15  //max num de balas en pantalla
#define MAX_BALAS_BOSS          40  //max num de balas en pantalla
#define MAX_EXPLOSIONES         10  //max num de explosiones en pantalla

#define VELOCIDAD_BALA_PLAYER    6  //valor mas alto = mas rapido
#define VELOCIDAD_BALA_BOSS      1

#define CAJA_COL_PLAYER_X1       8 //son coordenadas relativas a la posicion
#define CAJA_COL_PLAYER_Y1       8 //del sprite. La caja es de 8x8px
#define CAJA_COL_PLAYER_X2      16 //es decir, 1 tile, est� situada justo en
#define CAJA_COL_PLAYER_Y2      16 //el cuerpo de la nave

#define CAJA_COL_BOSS_X1       230 //son coordenadas absolutas de la pantalla
#define CAJA_COL_BOSS_Y1        35 //ya que el boss es en realidad un fondo
#define CAJA_COL_BOSS_X2       290
#define CAJA_COL_BOSS_Y2       145

#define EXPLOSION_T_VIDA        10 //ciclos de vida de la explosion antes de eliminarse


//Declaracion de funciones

static void inicializa_balas_player();
static void inicializa_explosiones();
static void inicializa_lista_balas_boss();

static void crea_bala_player( int tipo );
static void mantenimiento_balas_player();

static void crea_explosion( int x, int y );
static void mantenimiento_explosiones();

static void crea_bala_boss();
static void mantenimiento_balas_boss();

static void actualiza_caja_colisiones_player();

static void handleInput();
static void MIDEBUG();


//Declaracion de variables

//Nave del Player
struct {
	Sprite *spr_player; //puntero al sprite
	int x, y;           //posici�n
	int x1, y1, x2, y2;    //caja de colision
	int tempo_disparo;  //tempo de repetici�n de disparo
}NAVE;

//BOSS
struct {

	//el boss es un fondo, no necesita Sprite*
	//el boss es un fondo, no necesita x,y
	int x1, y1, x2, y2;        //caja de colision
	int tempo_disparo;

}BOSS;

//BALAS NAVE Y BOSS
struct estructura_bala {
	int a, x, y;        // a=activa, x,y=coordenadas.
	int tipo;           // 0=disparo normal, 1=disparo triple
	Sprite *spr;        // sprite
};

//declaracion de arrays de structs
struct estructura_bala lista_balas_player[ MAX_BALAS_PLAYER ];
struct estructura_bala lista_balas_boss[ MAX_BALAS_BOSS ];

//numero balas del boss (para optimizar el bucle)
int num_balas_boss;


//EXPLOSIONES (tanto player como boss)
struct estructura_explosion {
	int a, x, y;        // a=activo, x,y=coordenadas
	int t_vida;         //lo que dura la explosion (en ciclos)
	Sprite *spr;
};
struct estructura_explosion lista_explosiones[ MAX_EXPLOSIONES ];








//INICIALIZACIONES
static void inicializa_balas_player() {
	for( int cont = 0; cont < MAX_BALAS_PLAYER; cont++ ) {
		lista_balas_player[ cont ].a = 0;
		lista_balas_player[ cont ].x = 0;
		lista_balas_player[ cont ].y = 0;
		lista_balas_player[ cont ].tipo = 0;
		lista_balas_player[ cont ].spr = NULL;
	}
}
static void inicializa_explosiones() {
	for( int cont = 0; cont < MAX_EXPLOSIONES; cont++ ) {
		lista_explosiones[ cont ].x = 0;
		lista_explosiones[ cont ].y = 0;
		lista_explosiones[ cont ].spr = NULL;
	}
}
static void inicializa_lista_balas_boss() {
	for( int cont = 0; cont < MAX_BALAS_BOSS; cont++ ) {
		lista_balas_boss[ cont ].a = 0;
		lista_balas_boss[ cont ].x = 0;
		lista_balas_boss[ cont ].y = 0;
		lista_balas_boss[ cont ].tipo = 0;
		lista_balas_boss[ cont ].spr = NULL;
	}
	num_balas_boss = 0;
}



//CREA BALA PLAYER
//crea una bala en la primera pos libre del array
//tipo: 0=disparo normal, 1=disparo triple
static void crea_bala_player( int tipo )
{
	for( int cont = 0; cont < MAX_BALAS_PLAYER; cont++ )
	{
		if( lista_balas_player[ cont ].a == 0 )
		{
			lista_balas_player[ cont ].a = 1;
			lista_balas_player[ cont ].x = NAVE.x + 30;
			lista_balas_player[ cont ].y = NAVE.y + 15;
			lista_balas_player[ cont ].tipo = tipo;
			lista_balas_player[ cont ].spr = SPR_addSprite( &bala_sprite, lista_balas_player[ cont ].x,
				lista_balas_player[ cont ].y, TILE_ATTR( PAL0, TRUE, FALSE, FALSE ) );
			break;
		}
	}
}


//VIDA DE UNA BALA DEL PLAYER
//- Mueve bala seg�n su tipo (recto o en diagonal)
//- Elimina la bala si se sale de la pantalla
//- Elimina la bala si toca la caja de colision del enemigo
static void mantenimiento_balas_player()
{
	for( int cont = 0; cont < MAX_BALAS_PLAYER; cont++ )
	{
		if( lista_balas_player[ cont ].a != 0 ) //solo las activas
		{
			if( lista_balas_player[ cont ].tipo == 0 )       lista_balas_player[ cont ].x += VELOCIDAD_BALA_PLAYER;
			else if( lista_balas_player[ cont ].tipo == 1 ) { lista_balas_player[ cont ].x += VELOCIDAD_BALA_PLAYER; lista_balas_player[ cont ].y--; }
			else if( lista_balas_player[ cont ].tipo == 2 ) { lista_balas_player[ cont ].x += VELOCIDAD_BALA_PLAYER; lista_balas_player[ cont ].y++; }

			SPR_setPosition( lista_balas_player[ cont ].spr, lista_balas_player[ cont ].x, lista_balas_player[ cont ].y );

			//sale de la pantalla
			if( lista_balas_player[ cont ].x >= 330 || lista_balas_player[ cont ].y <= 0 || lista_balas_player[ cont ].y >= 220 )
			{
				lista_balas_player[ cont ].a = 0;                   //marca como inactivo en el vector
				SPR_releaseSprite( lista_balas_player[ cont ].spr );   //se carga sprite del VDP
			}

			//choca con la caja de colision del boss
			if( lista_balas_player[ cont ].x > BOSS.x1 && lista_balas_player[ cont ].x<BOSS.x2 &&
				lista_balas_player[ cont ].y>BOSS.y1 && lista_balas_player[ cont ].y < BOSS.y2 )
			{
				lista_balas_player[ cont ].a = 0;
				SPR_releaseSprite( lista_balas_player[ cont ].spr );
				crea_explosion( lista_balas_player[ cont ].x, lista_balas_player[ cont ].y );
			}
		}
	}
}

//CREA EXPLOSION en la pos x,y
static void crea_explosion( int x, int y )
{
	for( int cont = 0; cont < MAX_EXPLOSIONES; cont++ )
	{
		if( lista_explosiones[ cont ].a == 0 )
		{
			lista_explosiones[ cont ].a = 1;
			lista_explosiones[ cont ].x = x;
			lista_explosiones[ cont ].y = y;
			lista_explosiones[ cont ].t_vida = EXPLOSION_T_VIDA;
			lista_explosiones[ cont ].spr = SPR_addSprite( &explosion_sprite, lista_explosiones[ cont ].x,
				lista_explosiones[ cont ].y, TILE_ATTR( PAL0, TRUE, FALSE, FALSE ) );
			break;
		}
	}
}


//VIDA DE UNA EXPLOSION
// Cada ciclo disminuye su t_vida, al llegar a cero se elimina
static void mantenimiento_explosiones()
{
	for( int cont = 0; cont < MAX_EXPLOSIONES; cont++ )
	{
		if( lista_explosiones[ cont ].a != 0 ) //solo las activas
		{
			lista_explosiones[ cont ].t_vida--;
			if( lista_explosiones[ cont ].t_vida <= 0 )
			{
				lista_explosiones[ cont ].a = 0;                   //marca como inactivo en el vector
				SPR_releaseSprite( lista_explosiones[ cont ].spr );   //se carga sprite del VDP
			}
		}
	}
}




//CREA BALA DEL BOSS
//crea una bala en la primera pos libre del array
//cada bala se crea en una posici�n vertical aleatoria
static void crea_bala_boss()
{
	for( int cont = 0; cont < MAX_BALAS_BOSS; cont++ )
	{
		if( lista_balas_boss[ cont ].a == 0 )
		{
			lista_balas_boss[ cont ].a = 1;
			lista_balas_boss[ cont ].tipo = ( ( ( random() % 3 ) - 1 ) + 1 ); // da 0,1 y 2
			lista_balas_boss[ cont ].x = 220;
			lista_balas_boss[ cont ].y = ( ( ( random() % 200 ) - 1 ) + 1 );  //200 es el max de la coordenada y
			lista_balas_boss[ cont ].spr = SPR_addSprite( &bala_sprite, lista_balas_boss[ cont ].x,
				lista_balas_boss[ cont ].y, TILE_ATTR( PAL0, TRUE, FALSE, FALSE ) );
			num_balas_boss++;
			break;
		}
	}
}


//VIDA DE UNA BALA DEL BOSS
//- Mueve bala seg�n su tipo: 0,1,2: recto, diagonal-izq-arriba, diagonal-izq-abajo
//- Elimina la bala si se sale de la pantalla o si toca la caja de colision del player
//- Cuando dentro del bucle tratamos tantas balas como balas activas, salimos del bucle
static void mantenimiento_balas_boss()
{
	for( int cont = 0, i = 0; cont < MAX_BALAS_BOSS; cont++ )
	{
		if( lista_balas_boss[ cont ].a == 1 )    //solo las activas
		{
			i++; if( i > num_balas_boss ) break; //no vamos a hacer m�s ciclos del bucle que los necesarios

			if( lista_balas_boss[ cont ].tipo == 0 )  lista_balas_boss[ cont ].x -= VELOCIDAD_BALA_BOSS;
			if( lista_balas_boss[ cont ].tipo == 1 ) { lista_balas_boss[ cont ].x -= VELOCIDAD_BALA_BOSS; lista_balas_boss[ cont ].y--; }
			if( lista_balas_boss[ cont ].tipo == 2 ) { lista_balas_boss[ cont ].x -= VELOCIDAD_BALA_BOSS; lista_balas_boss[ cont ].y++; }

			SPR_setPosition( lista_balas_boss[ cont ].spr, lista_balas_boss[ cont ].x, lista_balas_boss[ cont ].y );

			//sale de la pantalla
			if( lista_balas_boss[ cont ].x <= 0 || lista_balas_boss[ cont ].y <= 0 || lista_balas_boss[ cont ].y >= 220 )
			{
				lista_balas_boss[ cont ].a = NULL;                 //marca como inactivo en el vector
				SPR_releaseSprite( lista_balas_boss[ cont ].spr );   //se carga sprite del VDP
				num_balas_boss--;
			}
			//choca con la caja de colision del player
			else if( lista_balas_boss[ cont ].x > NAVE.x1 && lista_balas_boss[ cont ].x<NAVE.x2 &&
				lista_balas_boss[ cont ].y>NAVE.y1 && lista_balas_boss[ cont ].y < NAVE.y2 )
			{
				lista_balas_boss[ cont ].a = 0;
				SPR_releaseSprite( lista_balas_boss[ cont ].spr );
				crea_explosion( lista_balas_boss[ cont ].x, lista_balas_boss[ cont ].y );
				num_balas_boss--;
			}
		}
	}
}


//CAJA COLISION PLAYER
static void actualiza_caja_colisiones_player()
{
	NAVE.x1 = NAVE.x + CAJA_COL_PLAYER_X1;
	NAVE.y1 = NAVE.y + CAJA_COL_PLAYER_Y1;
	NAVE.x2 = NAVE.x + CAJA_COL_PLAYER_X2;
	NAVE.y2 = NAVE.y + CAJA_COL_PLAYER_Y2;
}



//Recoge la entrada del mando y actualiza la posicion de la nave
static void handleInput()
{
	//variable donde se guarda la entrada del mando
	u16 value = JOY_readJoypad( JOY_1 );
	//si pulsamos izquierda...
	if( value & BUTTON_LEFT )
		SPR_setPosition( NAVE.spr_player, NAVE.x -= VELOCIDAD_PLAYER, NAVE.y );
	//si pulsamos derecha...
	if( value & BUTTON_RIGHT )
		SPR_setPosition( NAVE.spr_player, NAVE.x += VELOCIDAD_PLAYER, NAVE.y );
	//si pulsamos arriba...
	if( value & BUTTON_UP )
	{
		SPR_setPosition( NAVE.spr_player, NAVE.x, NAVE.y -= VELOCIDAD_PLAYER ); SPR_setAnim( NAVE.spr_player, NAVE_UP );
	}
	//si pulsamos abajo...
	if( value & BUTTON_DOWN )
	{
		SPR_setPosition( NAVE.spr_player, NAVE.x, NAVE.y += VELOCIDAD_PLAYER ); SPR_setAnim( NAVE.spr_player, NAVE_DOWN );
	}
	//si no pulsamos
	if( ( !( value & BUTTON_UP ) ) && ( !( value & BUTTON_DOWN ) ) )             SPR_setAnim( NAVE.spr_player, NAVE_IDLE );

	//limites
	if( NAVE.x <= 0 )      NAVE.x = 2;
	if( NAVE.x >= 320 - 32 ) NAVE.x = 320 - 32 - 2;
	if( NAVE.y <= 0 )      NAVE.y = 2;
	if( NAVE.y >= 224 - 24 ) NAVE.y = 224 - 24 - 2;

	//si pulsamos A: PLAYER disparo normal
	if( value & BUTTON_A && NAVE.tempo_disparo == 0 ) {
		crea_bala_player( 0 );
		NAVE.tempo_disparo = 1; //para bloquear el disparo durante un tiempo limitado (y que no salgan 60disparos/seg)
	}
	//para liberar el disparo despues de pulsar A
	if( NAVE.tempo_disparo > 0 ) NAVE.tempo_disparo++;
	if( NAVE.tempo_disparo > BLOQUEO_DISPARO ) NAVE.tempo_disparo = 0;


	//si pulsamos B: PLAYER disparo triple
	if( value & BUTTON_B && NAVE.tempo_disparo == 0 ) {
		crea_bala_player( 0 );
		crea_bala_player( 1 );
		crea_bala_player( 2 );
		NAVE.tempo_disparo = 1; //para bloquear el disparo durante un tiempo limitado (y que no salgan 60disparos/seg)
	}

	//si pulsamos C
	if( value & BUTTON_C && ( BOSS.tempo_disparo == 0 || BOSS.tempo_disparo == 1 ) ) {
		crea_bala_boss();

		BOSS.tempo_disparo++;
	}
	//para liberar el disparo despues de pulsar C
	if( BOSS.tempo_disparo > 0 ) BOSS.tempo_disparo++;
	if( BOSS.tempo_disparo > BLOQUEO_DISPARO_BOSS ) BOSS.tempo_disparo = 0;

}



//MIDEBUG: Muestra num de sprites en pantalla
static void MIDEBUG()
{

	//balas del player
	int contador_balas = 0;

	for( int cont = 0; cont < MAX_BALAS_PLAYER; cont++ )
		if( lista_balas_player[ cont ].a != 0 )
			contador_balas++;

	char x1_string[ 32 ];
	sprintf( x1_string, "%4d", contador_balas );
	VDP_drawText( "Balas Nave:", 1, 21 );
	VDP_drawText( x1_string, 15, 21 );

	//balas del boss
	int contador_balas_boss = 0;

	for( int cont = 0; cont < MAX_BALAS_BOSS; cont++ )
		if( lista_balas_boss[ cont ].a != 0 )
			contador_balas_boss++;
	char y1_string[ 32 ];
	sprintf( y1_string, "%4d", contador_balas_boss );
	VDP_drawText( "Balas Boss:", 1, 22 );
	VDP_drawText( y1_string, 15, 22 );

	//explosiones
	int contador_explosiones = 0;

	for( int cont = 0; cont < MAX_EXPLOSIONES; cont++ )
		if( lista_explosiones[ cont ].a != 0 )
			contador_explosiones++;

	char z1_string[ 32 ];
	sprintf( z1_string, "%4d", contador_explosiones );
	VDP_drawText( "Explosiones:", 1, 23 );
	VDP_drawText( z1_string, 15, 23 );

	//sprites totales
	int total = contador_balas + contador_balas_boss + contador_explosiones;

	char z2_string[ 32 ];
	sprintf( z2_string, "%4d", total );
	VDP_drawText( "Total sprites:", 1, 24 );
	VDP_drawText( z2_string, 15, 24 );

	//fps
	VDP_showFPS( FALSE );
}




int main()
{

	//Inicializa estructuras a CERO
	inicializa_balas_player();
	inicializa_explosiones();
	inicializa_lista_balas_boss();

	//Inicializa variables
	NAVE.x = 64;
	NAVE.y = 145;
	NAVE.tempo_disparo = 0;

	BOSS.tempo_disparo = 0;
	BOSS.x1 = CAJA_COL_BOSS_X1; //al ser fijas, no es necesario
	BOSS.y1 = CAJA_COL_BOSS_Y1; //recalcular cada frame como con
	BOSS.x2 = CAJA_COL_BOSS_X2; //la nave
	BOSS.y2 = CAJA_COL_BOSS_Y2;

	//variable para llevar el control de tiles
	u16 ind;

	//pone la pantalla a 320x224
	VDP_setScreenWidth320();

	//inicializa motor de sprites
	SPR_init( 0, 0, 0 );

	//recoge la paleta de bala, player y fondo (compartida)
	VDP_setPalette( PAL0, nave_sprite.palette->data );

	//fondos
	ind = TILE_USERINDEX;
	VDP_drawImageEx( BG_B, &fondo2, TILE_ATTR_FULL( PAL0, FALSE, FALSE, FALSE, ind ), 0, 0, FALSE, TRUE );
	ind += fondo2.tileset->numTile;
	VDP_drawImageEx( BG_A, &fondo1, TILE_ATTR_FULL( PAL0, TRUE, FALSE, FALSE, ind ), 0, 0, FALSE, TRUE );
	ind += fondo1.tileset->numTile;

	//configura el scroll
	VDP_setScrollingMode( HSCROLL_PLANE, VSCROLL_PLANE );
	int scrollValueVariable = 0;

	//crea la nave del player
	NAVE.spr_player = SPR_addSprite( &nave_sprite, NAVE.x, NAVE.y, TILE_ATTR( PAL0, TRUE, FALSE, FALSE ) );

	//AYUDA en pantalla
	VDP_drawText( "      BULLET HELL HELP    ", 1, 1 );
	VDP_drawText( "PAD - Controles, A/B: Fire", 2, 2 );
	VDP_drawText( "C: Boss Bullet Hell       ", 2, 3 );

	//Bucle principal
	while( TRUE )
	{
		//muestra cuantos sprites hay en pantalla
		MIDEBUG();

		//recoge la entrada de los mandos
		handleInput();

		//para las colisiones
		actualiza_caja_colisiones_player();

		//turno balas player: mueve, colisiona...
		mantenimiento_balas_player();

		//turno balas boss
		mantenimiento_balas_boss();

		//turno explosiones
		mantenimiento_explosiones();

		//mueve el plano B (fondo de estrellas)
		scrollValueVariable -= 3;
		VDP_setHorizontalScroll( BG_B, scrollValueVariable );

		//actualiza el VDP
		SPR_update();

		//sincroniza la Megadrive con la TV
		VDP_waitVSync();
	}

	return 0;
}
