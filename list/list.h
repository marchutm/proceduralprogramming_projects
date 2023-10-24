#ifndef _LIST_H_
#define _LIST_H_

#include "global.h"

typedef struct tagListItem
{
	LISTINFO* pInfo;							// przechowuje dane
	tagListItem* pNext;							// wska�nik na nast�pny element
} ListItem;

ListItem* CreateList();				// tworzy pust� list�( element Empty na g�rze listy )
int InsertFront( ListItem* pList, LISTINFO* pInfo );			// umieszcza nowy element na pocz�tku listy ( zwraca 0 przy niepowodzeniu, 1 gdy ok )
int Insert( ListItem* pAfter, LISTINFO* pInfo );				// umieszcza nowy element do listy po wska�niku pAfter ( zwraca 0 przy niepowodzeniu, 1 gdy ok )
LISTINFO* RemoveFront( ListItem* pList );				// usuwa pierwszy element z listy i zwraca informacje ( zwraca NULL gdy lista jest pusta )
LISTINFO* Remove( ListItem* pAfter );					// usuwa z listy element po wska�niku pAfter i zwraca informacje ( zwraca NULL gdy lista jest pusta )
LISTINFO* Front( ListItem* pList);					// zwraca informacje o pierwszym elemencie listy
int IsEmpty( ListItem* pList );						// zwraca 1 gdy lista jest pusta, w przeciwnym wypadku zwraca 0
void ClearList( ListItem* pList, void( __cdecl* freeMem )( const void* ) );				// czy�ci list� ( lista jest gotowa do dalszego u�ycia )
void RemoveList( ListItem** pList, void( __cdecl* freeMem )( const void* ) );				// czy�ci list� ( ustawia na NULL )
void SortList( ListItem* pList, int( __cdecl* comp )( const void*, const void* ) );					// sortuje list�
ListItem* Find( ListItem* pList, const void* pInfo, ListItem** pPrev, int( __cdecl *comp )( const void*, const void* ) );			// przeszukuje list�


#endif