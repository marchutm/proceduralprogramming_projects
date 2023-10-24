#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "list.h"
#include "global.h"

//*****************************************************************************************************
ListItem* CreateList()																																								 
{
	ListItem* Empty = ( ListItem* )malloc( sizeof( ListItem ) );				// tworzy elelment Empty na górze listy
	if( !Empty )
	{
		return NULL;
	}
	memset( Empty, 0, sizeof( ListItem ) );
	return Empty;					// zwraca wskaŸnik na Empty
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
		return 0;																			// zwaraca zerow gdy nie uda³o siê do³o¿yæ elementu
	}
	memset( p, 0, sizeof( ListItem ) );

	
	p->pInfo = pInfo;												// wskaŸnik na informacje do nowego elementu
	p->pNext = pAfter->pNext;								// wskaŸnik na nastêpny element za nowym elementem bêdzie nastêpny element za pAfter
	pAfter->pNext = p;											// wskaŸnik na nowy elelemnt jest wstawiany za pAfter

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

	ListItem* p = pAfter->pNext;								// wskaŸnik na element który chcemy ususn¹æ
	ListInfo* info = p->pInfo;						// wskaŸnik na informacje zawarta w usuwanym elemencie
	pAfter->pNext = p->pNext;						// wskaŸnik element po elemencie który chcemy usun¹æ
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
	return (  !pList  || !( pList->pNext ) );					// brak wskaŸnika na pierwszy element( wartoœæ NULL ) ( pnext bo pierwsz empty)
}
//*****************************************************************************************************
void ClearList( ListItem* pList, void( __cdecl* freeMem )( const void* ) )
{
	if( !pList )	printf( "Nolist" );
	if( !freeMem )	printf( "freeMem ERROR" );
	while( !IsEmpty( pList ) )												// pêtle wykonuje siê do moment a¿ lista bêdzie pusta
	{
		freeMem( Remove( pList ) );						// wywolac funk zwracajaca wsk na info i zwolnic ja przez wsk do funkcji zwalaniajacej pamiêæ na info
	}

}
//*****************************************************************************************************
void RemoveList( ListItem** pAddress, void( __cdecl* freeMem )( const void* ) )
{
	if( !pAddress || !*pAddress )		printf( "Adress error" );					// sprawdziæ pAdress i *pAdress
	ClearList( *pAddress, freeMem );						// wyczyœciæ
	free( *pAddress );										
	*pAddress = NULL;										// !!!!
}
//*****************************************************************************************************
void SortList( ListItem* pList, int( __cdecl* comp )( const void*, const void*) )
{	
	if( !pList )	printf( "No list" );
	if( !comp )		printf( "comp error" );
	ListItem* pFirst = pList;									// wskaŸnik na element pierwszy
	while( !IsEmpty( pFirst ) )										//  pFirst->pNext
	{
		ListItem* pMin = pFirst;									// wskaŸnik na elelment wczesniejszy niz minimalny
		ListItem* pCurr = pMin->pNext;					// wskaznik na element wczesniejszy niz prownywany

		while( !IsEmpty( pCurr ) )								// 	pCurr->pNext
		{
			if( compare( (const void* )( pMin->pNext->pInfo ),( const void* )( pCurr->pNext->pInfo ) ) == 1 )					// pMin > pCurr ( porównywany pMin->pNext z pCurr->pNext )
			{
				pMin = pCurr;
			}
			pCurr = pCurr->pNext;
		}
		if( pFirst != pMin )					// przywi¹zaæ min na pocz¹tek listy nieposortowanej( po czêœci posortowanej )
		{	
			pCurr = pMin->pNext->pNext;							// 1	
			pMin->pNext->pNext = pFirst->pNext;						// 2	
			pFirst->pNext = pMin->pNext;										// 3	
			pMin->pNext = pCurr;												// 4	
		}
		pFirst = pFirst->pNext;								// przychodzimy do nastêopnego elementu
	}
}
//*****************************************************************************************************
ListItem* Find( ListItem* pList, const void* pInfo, ListItem** pPrev, int( __cdecl* comp )( const void*, const void* ) )
{
	//if( !pList )	return NULL;
	if( !comp )		return *pPrev = NULL;
	//ListItem* p = pList->pNext;									// element pierwszy
	while( !IsEmpty( pList ) )							// przeszukujemy ca³¹ listê do momentu a¿ nie bêdzie wsk¹xnika na nastêpny element ( w pesymistycznym przypadku )
	{
		if( !( compare( ( const void* )( pList->pNext->pInfo ), pInfo ) ) )
		{
			*pPrev = pList;
			return pList->pNext;							// zwraca wskaŸnik na element zawieraj¹cy szukane info
		}
		pList = pList->pNext;
	}
	return *pPrev = NULL;;							// zwraca 0 gdy nie znajdzie poszukiwanego elementu
}
//*****************************************************************************************************