#ifndef _GLOBAL_INCLUDE_FILE_
#define _GLOBAL_INCLUDE_FILE_

typedef struct ListElement
{
	int nKey;
	int* p;								// dynamiczna tablica dwuelementowa
}	 ListInfo;

#define LISTINFO ListInfo

int compare( const void*, const void* );				// funkcja por�wnuje dwa elementy z listy
void freeItem( const void* );								// funkcja zwalniaj�ca pami��												

#endif _GLOBAL_INCLUDE_FILE_