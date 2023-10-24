#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <cstdlib>
#include <time.h>
#include <memory.h>
#include <string.h>
#include "FQueue.h"

#pragma warning( disable : 4996 )														// problem z funkcj¹ itoa
#define DEBUG
#define MAXSIZE 4																							// rozmiar tablicy
#define TEN 10

FQINFO* CreateInf( int nKey );
void PrintQueue( QFIFO* queue );

int main()
{
	// dodac do kolejki 4 elementy
	
	
	QFIFO* pQueue = FQCreate( MAXSIZE );
	if( !pQueue )
	{
		printf( "Kolejka nie zostala utworzona\n" );
		return 1;
	}
	srand( ( unsigned int )time( NULL ) );
	for( int i = 0; i < 4; i++ )
	{
		FQINFO* info = CreateInf( rand() % TEN );
		FQEnqueue( pQueue, info );
	}

#ifdef DEBUG
	printf( "\nPoczatkowa kolejka po wstawieniu 4 elementow: \n\n" );
	PrintQueue( pQueue );
#endif

	// dodac jeden element - ma byc blad!!

	FQINFO* info = CreateInf( rand() % TEN );
	FQEnqueue( pQueue, info );

	// usunac 3 elementy (wypisac info )

	for( int i = 0; i < 3; i++ )
	{
		FQINFO* p = FQDequeue( pQueue );
		printf( "\nUsuniety: nKey = %d, sName = %s", p->nKey, p->sName );
	}
#ifdef DEBUG
	printf( "\n\nKolejka po usnieciu 3 elementow: \n\n" );
	PrintQueue( pQueue );
#endif

	// dodac dwa elementy

	for ( int i = 0; i < 2; i++ )
	{
		FQINFO* info = CreateInf( rand() % TEN );
		FQEnqueue( pQueue, info );
	}

#ifdef DEBUG
	printf( "\nKolejka po dodaniu 2 elementow: \n\n" );
	PrintQueue( pQueue );
#endif

	// wyczyscic kolejke

	FQClear( pQueue, freeInfo );
#ifdef  DEBUG
	printf( "\nKolejka po wyczyszczeniu:\n\n" );
	PrintQueue( pQueue );
#endif

	// dodac trzy elementy

	for ( int i = 0; i < 3; i++ )
	{
		FQINFO* info = CreateInf( rand() % TEN );
		FQEnqueue( pQueue, info );
	}
#ifdef DEBUG
	printf( "\nKolejka po dodaniu 3 elementow: \n\n" );
	PrintQueue( pQueue );
#endif

	// usunac jeden (wypisac)

	FQINFO* t = FQDequeue( pQueue );
	printf( "\nUsuniety: nKey = %d, sName = %s\n", t->nKey, t->sName );

#ifdef DEBUG
	printf( "\nKolejka po usunieciu elementu: \n\n" );
	PrintQueue( pQueue );
#endif

	// usunac CALA kolejke


	FQRemove( &pQueue, freeInfo );

	return 0;
}
//**************************************************************************************************************************************
FQINFO* CreateInf( int nKey )
{

	FQINFO* pInfo = ( FQINFO* )calloc( 1, sizeof( FQINFO ) );											// alokacja info
	if ( !pInfo )
	{
		return NULL;
	}
	pInfo->nKey = nKey;
	pInfo->sName = ( char* )calloc( 2, sizeof( char ) );										// cyfra i znak o kodzie '0'
	if ( !pInfo->sName )
	{
		return NULL;
	}
	itoa( pInfo->nKey, pInfo->sName, TEN );								// 1- liczba któr¹ konwertujemy 2- miejsce w którym zapisany jest wynik konwersji( wskaŸnik ) 3- system liczbowy wyniku
	return pInfo;
}
//**************************************************************************************************************************************
void PrintQueue( QFIFO* queue )
{
	//if( !queue )	printf( "ErRoR" );
	QFIFO* p = queue;												// pierwszy element
	if( FQEmpty( queue ) )		printf( "Queue is empty\n" );
	for( int i = 0; i < p->nNoElem; i++ )										// pêtla wykonuje siê tyle razy ile jest elementów
	{
		int temp = ( p->nHead + i ) % p->nMaxElem;
		printf( "nKey %d = %d  sName %d = %s \n", i + 1 , p->pFQItems[ temp ]->nKey, i + 1, p->pFQItems[ temp ]->sName  );
	}
	return;
}
//**************************************************************************************************************************************
void freeInfo( const void* info )
{
	free( ( ( FQINFO* )info )->sName );
	free( ( FQINFO* )info );
}
//**************************************************************************************************************************************