#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "list.h"
#include "global.h"

//*****************************************************************************************************
ListItem* CreateList()																																								 
{
	ListItem* Empty = ( ListItem* )malloc( sizeof( ListItem ) );				// tworzy elelment Empty na g�rze listy
	if( !Empty )
	{
		return NULL;
	}
	memset( Empty, 0, sizeof( ListItem ) );
	return Empty;					// zwraca wska�nik na Empty
}
//*****************************************************************************************************
int InsertFront( ListItem* pList, LISTINFO* pInfo )																										 
{
	//if( !pList )	return NULL;
	return Insert( pList, pInfo );
}
//*****************************************************************************************************
int Insert( ListItem* pAfter, LISTINFO* pInfo )
{
	if( !pAfter ) return NULL;
	ListItem* p = ( ListItem* )malloc( sizeof( ListItem ) );					// tworzy nowy element
	if( !p )
	{
		return 0;																			// zwaraca zerow gdy nie uda�o si� do�o�y� elementu
	}
	memset( p, 0, sizeof( ListItem ) );

	
	p->pInfo = pInfo;												// wska�nik na informacje do nowego elementu
	p->pNext = pAfter->pNext;								// wska�nik na nast�pny element za nowym elementem b�dzie nast�pny element za pAfter
	pAfter->pNext = p;											// wska�nik na nowy elelemnt jest wstawiany za pAfter

	return 1;								// zwraca 1 gdy ok
}
//*****************************************************************************************************
LISTINFO* RemoveFront( ListItem* pList )
{
	//if( !pList )	return NULL;
	return Remove( pList );
}
//*****************************************************************************************************
LISTINFO* Remove( ListItem* pAfter )
{
	//if( !pAfter )		return NULL;
	if( IsEmpty( pAfter ) ) 
	{
		return NULL;							// zwraca NULL gdy lista jest pusta
	}

	ListItem* p = pAfter->pNext;								// wska�nik na element kt�ry chcemy ususn��
	ListInfo* info = p->pInfo;						// wska�nik na informacje zawarta w usuwanym elemencie
	pAfter->pNext = p->pNext;						// wska�nik element po elemencie kt�ry chcemy usun��
	free( p );
	return info;												
}
//*****************************************************************************************************
LISTINFO* Front( ListItem* pList )
{
	//if( !pList ) return NULL;
	if( IsEmpty( pList ) )	return NULL;
	return pList->pNext->pInfo;						// informcja o pierwszym elemencie listy ( pNext bo pierwszy Empty )
}
//*****************************************************************************************************
int IsEmpty( ListItem* pList )
{
	return (  !pList  || !( pList->pNext ) );					// brak wska�nika na pierwszy element( warto�� NULL ) ( pnext bo pierwsz empty)
}
//*****************************************************************************************************
void ClearList( ListItem* pList, void( __cdecl* freeMem )( const void* ) )
{
	if( !pList )	printf( "Nolist" );
	if( !freeMem )	printf( "freeMem ERROR" );
	while( !IsEmpty( pList ) )												// p�tle wykonuje si� do moment a� lista b�dzie pusta
	{
		freeMem( Remove( pList ) );						// wywolac funk zwracajaca wsk na info i zwolnic ja przez wsk do funkcji zwalaniajacej pami�� na info
	}

}
//*****************************************************************************************************
void RemoveList( ListItem** pAddress, void( __cdecl* freeMem )( const void* ) )
{
	if( !pAddress || !*pAddress )		printf( "Adress error" );					// sprawdzi� pAdress i *pAdress
	ClearList( *pAddress, freeMem );						// wyczy�ci�
	free( *pAddress );										
	*pAddress = NULL;										// !!!!
}
//*****************************************************************************************************
void SortList( ListItem* pList, int( __cdecl* comp )( const void*, const void*) )
{	
	if( !pList )	printf( "No list" );
	if( !comp )		printf( "comp error" );
	ListItem* pFirst = pList;									// wska�nik na element pierwszy
	while( !IsEmpty( pFirst ) )										//  pFirst->pNext
	{
		ListItem* pMin = pFirst;									// wska�nik na elelment wczesniejszy niz minimalny
		ListItem* pCurr = pMin->pNext;					// wskaznik na element wczesniejszy niz prownywany

		while( !IsEmpty( pCurr ) )								// 	pCurr->pNext
		{
			if( compare( (const void* )( pMin->pNext->pInfo ),( const void* )( pCurr->pNext->pInfo ) ) == 1 )					// pMin > pCurr ( por�wnywany pMin->pNext z pCurr->pNext )
			{
				pMin = pCurr;
			}
			pCurr = pCurr->pNext;
		}
		if( pFirst != pMin )					// przywi�za� min na pocz�tek listy nieposortowanej( po cz�ci posortowanej )
		{	
			pCurr = pMin->pNext->pNext;							// 1	
			pMin->pNext->pNext = pFirst->pNext;						// 2	
			pFirst->pNext = pMin->pNext;										// 3	
			pMin->pNext = pCurr;												// 4	
		}
		pFirst = pFirst->pNext;								// przychodzimy do nast�opnego elementu
	}
}
//*****************************************************************************************************
ListItem* Find( ListItem* pList, const void* pInfo, ListItem** pPrev, int( __cdecl* comp )( const void*, const void* ) )
{
	//if( !pList )	return NULL;
	if( !comp )		return *pPrev = NULL;
	//ListItem* p = pList->pNext;									// element pierwszy
	while( !IsEmpty( pList ) )							// przeszukujemy ca�� list� do momentu a� nie b�dzie wsk�xnika na nast�pny element ( w pesymistycznym przypadku )
	{
		if( !( compare( ( const void* )( pList->pNext->pInfo ), pInfo ) ) )
		{
			*pPrev = pList;
			return pList->pNext;							// zwraca wska�nik na element zawieraj�cy szukane info
		}
		pList = pList->pNext;
	}
	return *pPrev = NULL;;							// zwraca 0 gdy nie znajdzie poszukiwanego elementu
}
//*****************************************************************************************************