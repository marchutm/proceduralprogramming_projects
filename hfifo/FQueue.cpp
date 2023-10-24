#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "FQueue.h"

void  FQDel( QFIFO* q );				// funkcja prywatna modulu  - tylko usuniecie elemenu z listy ( nie info ) 

QFIFO* FQCreate()
{
	QFIFO* p = ( QFIFO* )calloc( 1, sizeof( QFIFO ) );
	if( !p )	return NULL;
	FQItem* t =( FQItem* )calloc( 1, sizeof( FQItem ) );
	if( !t )	return NULL;
	
	p->pHead = p->pTail = t;
	
	return p;
}
//**************************************************************************************************************************************
int FQEmpty( QFIFO* q )
{
	/*if( q->pHead->pNext != q->pTail )		return 0;							// wska�nik na pierwszy element jest wska�nikiem na koniec kolejki
	else return 1;*/
	return !q || !( q->pHead->pNext );
}
//**************************************************************************************************************************************
int FQEnqueue( QFIFO* q, FQINFO* pItem )
{
	if( !q )	return NULL;
	FQItem* p = ( FQItem* )calloc( 1, sizeof( FQItem ) );
	if( !p )	return 0;
	// kolejka nie mo�e by� pusta zawsze ma element g�owa tworzony przy tworzeniu kolejki
	p->pInfo = pItem;									// przypisanie warto�ci
	q->pTail->pNext = p;									// nowy element jest nowym ogonem
	q->pTail = p;							// nowe pierwsze wolne miejsce w kolejce
	return 1;
}
//**************************************************************************************************************************************
FQINFO* FQDequeue( QFIFO* q )
{
	//if( !q )	return NULL;
	if ( FQEmpty ( q ) )	return NULL;										// zwaraca NULL gdy kolejka jest pusta
	FQINFO* info = q->pHead->pNext->pInfo;						// informacja pierwszego elementu
	FQDel( q );									// wywo�anie funkcji del
	return info;								// zwraca wska�nik do usuni�tego elementu
}	
//**************************************************************************************************************************************
void  FQClear( QFIFO* q, void( __cdecl* freeMem )( const void* ) )
{
	if( !q )	printf( "Kolejka nie istnieje\n" );
	if( !freeMem )	printf( "Blad adresu funkcji zwalniajacej pamiec\n" );
	while( !FQEmpty( q ) )
	{
		freeMem( ( const void* )FQDequeue( q ) );			// wywolac funk zwracajaca wsk na info i zwolnic ja przez wsk do funkcji zwalaniajacej pami�� na info
	}
}
//**************************************************************************************************************************************
void  FQRemove( QFIFO** q, void( __cdecl* freeMem )( const void* ) )
{
	if( !q || !*q )	printf( "Kolejka nie istnieje\n" );
	//if( !freeMem )	printf( "ERROR4" );
	FQClear( *q, freeMem );						// mnjapier wyczyscic
	free( ( *q )->pHead );
	free( *q );
	*q = NULL;
}
//**************************************************************************************************************************************
void  FQDel( QFIFO* q )
{
	if( !q )	printf( "Queue not exists or is empty\n" );
	//if( FQEmpty( q ) )	printf( "Queue is empty" );

	FQItem* p = q->pHead->pNext;										// pierwszy element kolejki( element do usuni�cia )
	q->pHead->pNext = p->pNext;												// nowy pierwszy element kolejki
	free( p );															// zwolnienie poami�ci wcze�nijszego pierwszego elementu
	if( FQEmpty( q ) )	q->pTail = q->pHead;
}
//**************************************************************************************************************************************	