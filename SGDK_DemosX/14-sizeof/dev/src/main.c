#include "main.h"

// SMS equivalent
// ~\Steven\INSTALLATIONSEGA\sdcc3\Test2015_sizeof\dev
int main()
{
	unsigned char i = 8;

	i = sizeof( unsigned char );		// 1 byte
	//i = sizeof( unsigned short );		// 2 bytes
	//i = sizeof( unsigned int );		// 4 bytes
	//i = sizeof( unsigned long );		// 4 bytes


	//i = sizeof( char );		// 1 byte
	//i = sizeof( short );		// 2 bytes
	//i = sizeof( int );		// 4 bytes
	//i = sizeof( long );		// 4 bytes
	//i = sizeof( float );		// 4 bytes
	//i = sizeof( double );		// 8 bytes

	engine_font_manager_data( i, 10, 10 );

	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}

