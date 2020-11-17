#include "main.h"

// Reference
// https://www.geeksforgeeks.org/bubble-sort
//https://www.geeksforgeeks.org/search-insert-and-delete-in-a-sorted-array
char str_score[ 3 ] = "0";

void updateScoreDisplay(u16 value, u16 x, u16 y)
{
	//sprintf( str_score, "%d", score );
	sprintf( str_score, "%3d", value );
	VDP_clearText( x, y, 3 );
	VDP_drawText( str_score, x, y );
}

int insertSorted( int arr[], int key, int capacity )
{
	// Cannot insert more elements if n is already 
	// more than or equal to capcity 

	int i;
	for( i = capacity- 1; ( i >= 0 && arr[ i ] >= key ); i-- )
		arr[ i + 1 ] = arr[ i ];

	arr[ i + 1 ] = key;

	return ( i + 1 );
}

int main()
{
	int arr[ 6 ] = { 12, 16, 20, 40, 50, 70 };
	int capacity = sizeof( arr ) / sizeof( arr[ 0 ] );
	int n = 0;
	int key = 69;

	//u16 arr[ 3 ] = { 60, 120, 180 };
	//updateScoreDisplay( arr[ 0 ], 10, 10 );
	//updateScoreDisplay( arr[ 1 ], 10, 11 );
	//updateScoreDisplay( arr[ 2 ], 10, 12 );

	n = insertSorted( arr, key, capacity );
	//u16 capacity = 3;
	//u16 key = 150;

	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}

