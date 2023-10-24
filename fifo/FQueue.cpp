#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include "FQueue.h"

void  FQDel( QFIFO* q );				// funkcja prywatna modulu  - tylko usuniecie elemenu z listy (nie info) 

QFIFO* FQCreate()
{
	return ( QFIFO* )calloc( 1, sizeof( QFIFO) );
}
//**************************************************************************************************************************************
int FQEmpty( QFIFO* q )
{
	/*if( q->pHead = q->pTail )		return 0;									// wska�nik na pierwszy element jest wskaxnikiem na koniec
	else return 1;*/
	return (  !q || !( q->pHead ) );
}
//**************************************************************************************************************************************
int FQEnqueue( QFIFO* q, FQINFO* pItem )
{
	if( !q )	return NULL;
	FQItem* p = ( FQItem* )calloc( 1, sizeof( FQItem ) );
	if ( !p )	return NULL;							// zwraca 0 gdy b��d alokacji
	p->pInfo = pItem;				// przypisanie warto�ci
	if( FQEmpty( q ) )	q->pHead = p;				// jesli kolejka jest pusta nowy element jest g�owa
	// kolejka nie jest pusta ( dodajemy na koniec kolejki )
	else q->pTail->pNext = p;			// element po nowym elemencie jest ostatnim (ogon)
	q->pTail = p;						// nowy element jest w miejscu ogonu

	return 1;						// zwraca 1 gdy udane
}
//**************************************************************************************************************************************
FQINFO* FQDequeue( QFIFO* q )
{
	//if( !q ) return NULL;
	if( FQEmpty( q ) )	return NULL;										// zwaraca NULL gdy kolejka jest pusta
	FQINFO* info = q->pHead->pInfo;							// informacja pierwszego elementu
	FQDel( q );												// wywo�anie funkcji del
	return info;											// zwraca wska�nik do usuni�tego elementu
}
//**************************************************************************************************************************************
void  FQClear( QFIFO* q, void( __cdecl* freeMem )( const void* ) )
{
	if( !q )	printf( "Kolejka nie istnieje\n" );
	if( !freeMem )	printf( "Blad adresu funkcji zwalniajacej pamiec\n" );
	//FQItem* p = q->pHead;						// pierwszy element kolejki
	while( !FQEmpty( q ) )						// czy�cimy do momentu a� kolejka nie jest pusta
	{
		freeMem( FQDequeue( q ) );			// wywolac funk zwracajaca wsk na info i zwolnic ja przez wsk do funkcji zwalaniajacej pami�� na info														
	}
}
//**************************************************************************************************************************************
void  FQRemove( QFIFO** q, void( __cdecl* freeMem )( const void* ) )
{
	if( !q || !*q )		printf( "Kolejka nie istnieje\n" );					// sprawdzi� q i *q
	//if( !freeMem )	printf( "Blad adresu funkcji zwalniajacej pamiec" );
	FQClear( *q, freeMem );			// wyczy�ci�
	free( *q );									// zwolnienie pami�ci kolejki
	*q = NULL;									// !!!
}
//**************************************************************************************************************************************
void  FQDel( QFIFO* q )
{
	//if( !q )	printf( "ERROR5" );
	if( FQEmpty( q ) )	printf( "Queue not exists or is empty\n" );

	FQItem* p = q->pHead;				// pierwszy element kolejki
	q->pHead = p->pNext;					// nowym pierwszym elementem jest element po p
	free( p );									// zwolnienie pami�ci p
}
//**************************************************************************************************************************************