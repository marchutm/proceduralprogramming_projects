#pragma once
#include "global.h"

typedef struct tagFIFOItem
{
  FQINFO* pInfo;
  tagFIFOItem* pNext;
} FQItem;

typedef struct
{
  FQItem* pHead;                // g³owa kolejki (pierwszy elelment w kolejce)
  FQItem* pTail;                // ogon kolejki (pierwsze wolne miejsce w kolejce)
} QFIFO;

QFIFO* FQCreate();      // kreowanie dynamiczne kolejki
int FQEmpty( QFIFO* q );        // zwraca 1 gdy kolejka pusta, w przeciwnym wypadku 0
int FQEnqueue( QFIFO* q, FQINFO* pItem );         // wstawienie elementu do kolejki i zwrocenie 1 gdy OK i 0 gdy blad alokacji
FQINFO* FQDequeue( QFIFO* q );  // usuniecie elementu z kolejki i zwrocenie wskaznika do tego elementu (NULL - kolejka pusta) ma wywolac FQDel() 
void FQClear( QFIFO* q, void( __cdecl* freeMem )( const void* ) );        // czyszczenie kolejki, kolejke mozna uzywac dalej
void FQRemove( QFIFO** q, void( __cdecl* freeMem )( const void* ) );          // czyszczenie kolejki i usuniecie wszystkich struktur danych, wyzerowanie kolejki   