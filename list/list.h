#ifndef _LIST_H_
#define _LIST_H_

#include "global.h"

typedef struct tagListItem
{
	LISTINFO* pInfo;							// przechowuje dane
	tagListItem* pNext;							// wskaŸnik na nastêpny element
} ListItem;

ListItem* CreateList();				// tworzy pust¹ listê( element Empty na górze listy )
int InsertFront( ListItem* pList, LISTINFO* pInfo );			// umieszcza nowy element na pocz¹tku listy ( zwraca 0 przy niepowodzeniu, 1 gdy ok )
int Insert( ListItem* pAfter, LISTINFO* pInfo );				// umieszcza nowy element do listy po wskaŸniku pAfter ( zwraca 0 przy niepowodzeniu, 1 gdy ok )
LISTINFO* RemoveFront( ListItem* pList );				// usuwa pierwszy element z listy i zwraca informacje ( zwraca NULL gdy lista jest pusta )
LISTINFO* Remove( ListItem* pAfter );					// usuwa z listy element po wskaŸniku pAfter i zwraca informacje ( zwraca NULL gdy lista jest pusta )
LISTINFO* Front( ListItem* pList);					// zwraca informacje o pierwszym elemencie listy
int IsEmpty( ListItem* pList );						// zwraca 1 gdy lista jest pusta, w przeciwnym wypadku zwraca 0
void ClearList( ListItem* pList, void( __cdecl* freeMem )( const void* ) );				// czyœci listê ( lista jest gotowa do dalszego u¿ycia )
void RemoveList( ListItem** pList, void( __cdecl* freeMem )( const void* ) );				// czyœci listê ( ustawia na NULL )
void SortList( ListItem* pList, int( __cdecl* comp )( const void*, const void* ) );					// sortuje listê
ListItem* Find( ListItem* pList, const void* pInfo, ListItem** pPrev, int( __cdecl *comp )( const void*, const void* ) );			// przeszukuje listê


#endif