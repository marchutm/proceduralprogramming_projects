#include <iostream>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <memory.h>
#include "sortowania.h"


#define _DEBUG_
#define MAX 50
#define MAXPRINT 10

int createTab( int** pTab, int nSize );													// malloc + memset + if (gdy blad to zwraca NULL )
void freeTab( int** pTab );																			// free + podst NULL
void randInit( int* pTab, int nSize );													// losowa tablica
void copyTab( int* pTabTo, int* pTabFrom, int nSize );					// kopiowanie tablicy
void printTab( int* pTab, int nSize );													// wypisywanie tablicy

typedef void( *funSort )( int*, int );
typedef const char* funName[];

int main( int argc, char* argv[] )
{

	if ( argc != 2 )
	{
		printf( "Usage %s <tab_size>\n", argv[ 0 ] );
		return -1;
	}

	int nSize = atoi( argv[ 1 ] );															// atoi pobiera liczbê w postaci ci¹gu znaków ASCII i zwraca wartoœæ w int

	funSort pSort[] = { simpleInsertion, simpleSelectionSort, bubbleSort, mixedBubbleSort, halfSort, heapSort, quickSort };				// tablica z adresami funkcji sortuj¹cych
	funName pNames = { "Proste wstawianie", "Proste wybieranie", "Bablekowe", "Mieszane", "Polowkowe", "Stogowe", "Szybkie" };		// tablica nazw sortowañ

	int* pTab = NULL;																						// pusty wskaŸnik do tablicy
	if ( !createTab( &pTab, nSize ) )
	{
		perror ( "Error create TAB1" );
		return -2;
	}
	int* pSortTime = NULL;																			// pusty wskaŸnik do tablicy (tablica do której kpjujemy)
	if ( !createTab( &pSortTime, nSize ) )
	{
		perror ( "Error create TAB2" );
		return -3;
	}

	randInit( pTab, nSize );																		

#ifdef _DEBUG_
	printf( "Losowa tablica\n " );
	printTab( pTab, MAX );
#endif

	const int n = sizeof( pSort ) / sizeof( funSort );					// liczba sortowañ

	for( int i = 0; i < n; i++ )
	{
		copyTab( pSortTime, pTab, nSize );
		clock_t start = clock();																	// mierzymy czas przed wykonaniem sortowañ ( clock zwraca liczbê tykniêc zegara )
		pSort[ i ]( pSortTime, nSize );														// po kolei wykonuje sortowania z tablicy adresów sortowañ
		printf( "\n Sortowanie przy pomocy %s zajmie: \n %f\n" , pNames[ i ], ( double )( clock() - start ) / CLOCKS_PER_SEC );			// aby uzyskañ czas w sekundach trzeba podzielic przez CLOCKS_PER_SEC

#ifdef _DEBUG_
		printf( "Posortowana tablica\n" );
		printTab( pSortTime, MAX );
#endif
	}

	freeTab( &pTab );
	freeTab( &pSortTime );

	return 0;
}


//*************************************************************************
int createTab( int** pTab, int nSize )
{
	*pTab = ( int* )malloc( sizeof( int ) * nSize );
	if ( !*pTab )																															// sprawdzanie czy alokacja siê powiod³a
	{
		return 0;
	}
	memset( *pTab, 0, sizeof( int ) * nSize );
	return 1;
}
//*************************************************************************
void randInit( int* pTab, int nSize )
{
	srand( (int )time( NULL ) );																						
	for ( int i = 0; i < nSize; i++ )
	{
		*pTab++ = rand() % nSize;
	}
}
//*************************************************************************
void copyTab( int* pTabTo, int* pTabFrom, int nSize )
{
	memcpy( pTabTo, pTabFrom, nSize * sizeof( pTabFrom ) );											// 1-tablica do której kopjujemy, 2-tablica z której kopjujemy
}
//*************************************************************************
void printTab( int* pTab, int nSize ) 
{
	for ( int i = 0; i < nSize; i++ ) 
	{
		printf( "%d ", *pTab++ );
		if ( ( i + 1 ) % MAXPRINT == 0 ) printf( "\n" );
	}
}
//*************************************************************************
void freeTab( int** pTab )
{
	free( *pTab );
	*pTab = NULL;																															// ustawiæ wskaŸnik na zero po free (na wypadek ponownego u¿ycia)
}
//*************************************************************************