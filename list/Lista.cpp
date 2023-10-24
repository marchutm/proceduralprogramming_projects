#include <stdlib.h> 
#include <stdio.h>
#include <memory.h>
#include <time.h>
#include "list.h" 


#define DEBUG
#define TWO 2
#define MAX 50


void PrintInfo( ListItem* pList );							// funkcja drukuj�ca info
ListInfo* CreateInfo();											// funkcja tworz�ca pamie� na informacj�


int main()
{
	// doda� minimum 20 element�w z kluczami losowymi( < 50 ) ( nKey ) 
	// a do pierwszego elementu dynamicznej tablicy dwuelementowej 
	// wstawia� indeks p�tli( dla indeksu 9 wstawi� klucz 2000 )

	ListItem* pList = CreateList();
	srand( ( unsigned int )time( NULL ) );
	for( int i = 0; i < 20; i++ ) 
	{
		ListInfo* pInfo = CreateInfo();
		pInfo->nKey = rand() % MAX;								//( < 50 )
		pInfo->p[ 0 ] = i;
		if ( i == 9 )		pInfo->nKey = 2000;	
		InsertFront( pList, pInfo );
	}
#ifdef DEBUG
	printf( "\nPoczatkowa lista: \n\n" );
	PrintInfo( pList );

#endif 


	// posortowac
	
	SortList( pList, compare );

#ifdef DEBUG
	printf( "\nLista po posortowaniu: \n\n" );	
	PrintInfo( pList );
#endif

	//wyszukac element z kluczem 2000

	ListInfo* pFindInfo = CreateInfo();
	pFindInfo->nKey = 2000;

	ListItem* pPrev = NULL;					// wska�nik na element przed szukanym ( w tym przypadku 2000 )
	ListItem* pFind2 = Find( pList, pFindInfo, &pPrev, compare );
	

#ifdef DEBUG
	printf( "\nSzukany element = %d\n", pFind2->pInfo->nKey );
#endif

		
	//wstawi� przed znalezionym, element z kluczem 3000
	
	ListInfo* pInsertInfo = CreateInfo();
	pInsertInfo->nKey = 3000;
	Insert( pPrev, pInsertInfo );						// wstawiamy za elementem pPrev( przed 2000 )

#ifdef  DEBUG
	printf( "\nLista po wynaniu wstawiania: \n\n" );
	PrintInfo( pList );
#endif


	//usuna� element z kluczem 2000

	ListInfo* t = Remove( pPrev->pNext );						// usuwamy element po 3000 ( wka�nik na element 3000, bo funkcja usuwa element po tym wska�niku )
	printf( "\nUsuniety element = % d\n", t->nKey );				// wypisa� usuni�ty element

#ifdef DEBUG
	printf( "\nLista po wykonaniu usuwania: \n\n" );
	PrintInfo( pList );
#endif
	
	// zwolnic liste

	ClearList( pList, freeItem );

#ifdef  DEBUG
	printf( "\nLista po wyczyszczeniu: \n\n" );
	PrintInfo( pList );
#endif
	
	// wstawic 2 elementy

	for( int i = 0; i < 2; i++ )
	{
		ListInfo* pInf = CreateInfo();
		pInf->nKey = rand() % MAX;
		pInf->p[ 0 ] = i;
		InsertFront( pList, pInf );
	}

#ifdef DEBUG
	printf( "\nLista po wstawieniu 2 elementow: \n\n" );
	PrintInfo( pList );
#endif
	
	// usunac cala liste

	RemoveList( &pList, freeItem );

	return 0;
}
//*****************************************************************************************************
int compare( const void* p, const void* v )
{
	if( ( ( LISTINFO* ) p )->nKey < ( ( LISTINFO* )v )->nKey )	return -1;							// zwraca -1 jsli p < v
	if( ( ( LISTINFO* ) p )->nKey == ( ( LISTINFO* )v )->nKey )		return 0;								// zwraca 0 jesli p = v
	return 1;								// zwraca 1 gdy p > v
}
//*****************************************************************************************************
void freeItem( const void* Item )
{
	free( ( ( LISTINFO* )Item )->p );
	free( ( LISTINFO* )Item );
}
//*****************************************************************************************************
void PrintInfo( ListItem* pList )
{
	if( IsEmpty( pList ) ) printf( "THERE IS NO LIST!!!\n" );
	//ListItem* p = pList;
	int i = 1;
	while( !IsEmpty( pList ) )
	{
		pList = pList->pNext;
		printf( "Item%d = %d\n", i++,  p->pInfo->nKey );
	}
}
//*****************************************************************************************************
ListInfo* CreateInfo()
{
	ListInfo* pInfo = ( ListInfo* )malloc( sizeof( ListInfo ) );
	if ( !pInfo )
	{
		return NULL;
	}
	memset( pInfo, 0, sizeof( ListInfo ) );
	pInfo->p = ( int* )malloc( TWO * sizeof( int ) );					// 2 elementy ( tablica dwuelelmentowa )
	if ( !( pInfo->p ) )
	{
		return NULL;
	}
	memset( pInfo->p, 0, TWO * sizeof( int ) );					
	return pInfo;							// zwraca informacje
}
//*****************************************************************************************************