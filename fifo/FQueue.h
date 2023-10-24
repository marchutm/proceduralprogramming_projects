#pragma once
#include "global.h"

typedef struct {
	FQINFO** pFQItems;										// - dynamiczna tablica wskaznikow do informacji
	int nHead;																//  - indeks pierwszego elementu w kolejce
	int nTail;																	// - indeks pierwszego wolnego miejsca w kolejce( po ostatnim zajetym )
	int nNoElem;														// - ilosc elementow kolejki
	int nMaxElem;												// - rozmiar kolejki( rozmiar tablicy pFQItems )
} QFIFO;

QFIFO* FQCreate( int nSize );					// kreowanie dynamiczne kolejki (struktury i tablicy)    nSize  - rozmiar tablicy
int FQEmpty( QFIFO* q );				// zwraca 1 gdy kolejka pusta, w przeciwnym wypadku 0
int FQEnqueue( QFIFO* q, FQINFO* pItem );				// wstawienie elementu do kolejki
FQINFO* FQDequeue( QFIFO* q );							// usuniecie elementu z kolejki i zwrocenie wskaznika do tego elementu
void    FQClear( QFIFO* q, void( __cdecl* freeMem )( const void* ) );						// czyszczenie kolejki, kolejke mozna uzywac
void    FQRemove( QFIFO** q, void( __cdecl* freeMem )( const void* ) );