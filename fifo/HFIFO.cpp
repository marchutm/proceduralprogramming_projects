#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <cstdlib>
#include <time.h>
#include <memory.h>
#include <string.h>
#include "FQueue.h"


FQINFO* CreateInf( int nKey );
void PrintQueue( QFIFO* queue );

#pragma warning( disable : 4996 )														// problem z funkcj¹ itoa
#define DEBUG
#define TEN 10
#define C

int main()
{
	// dodac do kolejki 4 elementy

	QFIFO* pQueue = FQCreate();
	if( !pQueue )
	{
		printf( "Kolejka nie zostala utworzona\n" );
		return 1;
	}
	srand( ( unsigned int )time( NULL ) );
	for( int i = 0; i < 4; i++ )
	{
		FQINFO* info = CreateInf( rand() % TEN );
		if( !( FQEnqueue( pQueue, info ) ) )		return 0;
	}

#ifdef DEBUG
	printf( "\nPoczatkowa lista po wstawieniu 4 elementow: \n\n" );
	PrintQueue( pQueue );
	//printf( "test" );
#endif

	// usunac 3 elementy (wypisac info)

	printf( "\n" );
	for ( int i = 0; i < 3; i++ )
	{
		FQINFO* p = FQDequeue( pQueue );
#ifdef DEBUG
		printf( "Usuniety element : nKey = %d, sName = %s\n", p->nKey, p->sName );
#endif		
	}
#ifdef DEBUG
	printf( "\nKolejka po usunieciu 3 elementow: \n\n" );
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

	FQClear( pQueue, freeInfo );								// !!!!!!!!


#ifdef DEBUG
	printf( "\nKolejka po wyczyszczeniu: \n\n" );
	PrintQueue( pQueue );
#endif

	// dodac trzy elementy

	for ( int i = 0; i < 3; i++ )
	{
		FQINFO* info = CreateInf( rand() % TEN );
		FQEnqueue( pQueue, info );
	}
#ifdef DEBUG
	printf( "\n\nKolejka po dodaniu 3 elementow: \n\n" );
	PrintQueue( pQueue ); 
#endif

	// usunac jeden (wypisac)

	FQINFO* t = FQDequeue( pQueue );


#ifdef DEBUG
	printf( "\nUsuniety element : nKey = %d, sName = %s", t->nKey, t->sName );
	//printf("XD");
	printf( "\n\nKolejka po usunieciu elementu: \n\n" );
	PrintQueue( pQueue );
#endif

	// usunac CALA kolejke


	FQRemove( &pQueue, freeInfo );


	return 0;

}
//**************************************************************************************************************************************
void freeInfo( const void* info )
{
	free( ( ( FQINFO* )info )->sName );
	free( ( FQINFO* )info );
}
//**************************************************************************************************************************************
FQINFO* CreateInf( int nKey ) 
{
	FQINFO* pInfo = ( FQINFO* )calloc( 1, sizeof( FQINFO ) );											// alokacja info
	if ( !pInfo )	return NULL;
	pInfo->nKey = nKey;
	pInfo->sName = ( char* )calloc( C + 1, TEN * sizeof( char ) );										// cyfra i znak o kodzie '0'
	if ( !pInfo->sName )	return NULL;
	itoa( pInfo->nKey, pInfo->sName, TEN );								// 1- liczba któr¹ konwertujemy 2- miejsce w którym zapisany jest wynik konwersji( wskaŸnik ) 3- system liczbowy wyniku
	return pInfo;
}
//**************************************************************************************************************************************
void PrintQueue( QFIFO* queue )
{
	FQItem* p = queue->pHead->pNext;							// pierwszy element
	if ( !p )	printf( "Queue is empty\n" );								// pusta lista
	int i = 1;																		// indeks elementu 
	while ( p )														// pêtla wyknuje siê do momonetu a¿ bedzie jakikolwik element na niej(nie bêdzie pusta)
	{
		printf( "nKey %d = %d, sName %d = %s\n", i, p->pInfo->nKey, i, p->pInfo->sName );
		p = p->pNext;
		i++;
	}
}
//**************************************************************************************************************************************