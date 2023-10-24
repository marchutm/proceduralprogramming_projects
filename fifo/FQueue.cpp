#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include "FQueue.h"

void  FQDel( QFIFO* q ); // funkcja PRYWATNA! modulu 

//**************************************************************************************************************************************
QFIFO* FQCreate( int nSize )
{
	//!!!!!!!!!!spr nSize
	if( nSize < 1 )	return NULL;
	QFIFO* p = ( QFIFO* )calloc( 1, sizeof( QFIFO ) );
	if( !p )	return NULL;
	p->pFQItems = ( FQINFO** )calloc( nSize, sizeof( FQINFO* ) );				// tablica wskaŸników do info
	if( !( p->pFQItems ) )	return NULL;
	p->nMaxElem = nSize;																								// maksymalna liczba elem
	return p;
}
//**************************************************************************************************************************************
int FQEmpty( QFIFO* q )
{
	return !q || !( q->nNoElem );											// liczba elementów na liœcie wynosi 0
}
//**************************************************************************************************************************************
int FQEnqueue( QFIFO* q, FQINFO* pItem )
{
	if( !q || q->nMaxElem == q->nNoElem )								// iloœæ elementów jest równa maksymalnej liczbie lemetnów
	{
		//printf( "\nERROR: Queue is overflowed\n" );
		return 0;
	}
	
	q->pFQItems[ q->nTail ] = pItem;						// nowy element przypisany do pierwszego wolengo miejsca														
	q->nTail = ( ( q->nTail ) + 1 ) % q->nMaxElem;									// ogon jest wskaŸnikiem na element za nowo dodanym elementem
	( q->nNoElem )++;														// zwiêkszenie ilosci elementów kolejki
	return 1;
}	
//**************************************************************************************************************************************
FQINFO* FQDequeue( QFIFO* q )
{
	if( FQEmpty( q ) )	return NULL;
	FQINFO* p = q->pFQItems[ q->nHead ];							// pierwszy element
	FQDel( q );
	return p;
}
//**************************************************************************************************************************************
void FQClear( QFIFO* q, void( __cdecl* freeMem )( const void* ) )
{
	if( !q )	printf( "Kolejka nie istnieje\n" );			//!!!komun
	if( !freeMem )	printf( "Blad adresu funkcji zwalniajacej pamiec\n" );//!!!
	while( !( FQEmpty( q ) ) )
	{
		freeMem( FQDequeue( q ) );
	}
}
//**************************************************************************************************************************************
void FQRemove( QFIFO** q, void( __cdecl* freeMem )( const void* ) )
{
	if( !q || !*q )		printf( "Kolejka nie istnieje\n" );//!!!
	FQClear( *q, freeMem );
	free( ( *q )->pFQItems );
	free( *q );
	*q = NULL;
}
//**************************************************************************************************************************************
void FQDel( QFIFO* q )
{
	if( !q )	printf( "Queue not exists or is empty\n" );
	q->pFQItems[ q->nHead ] = NULL;						//  - wstawia NULL do pozycji tablicy, skad pobierany jest element
	q->nHead = ( ( q->nHead ) + 1 ) % q->nMaxElem;							//  - przesuwa cyklinie indeks glowy kolejki
	( q->nNoElem )--;										//  - zmniejsza ilosc elementow w kolejce
}
//**************************************************************************************************************************************